#include "../../include/utils/MatrixMultiply.hpp"
#include "../../include/utils/cuda_error_check.hpp"

namespace utils {

__global__ void matMulKernel(double *a, double *b, double *c, int aRows, int aCols, int bCols) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < aRows && col < bCols) {
        double sum = 0.0;
        for (int k = 0; k < aCols; ++k) {
            sum += a[row * aCols + k] * b[k * bCols + col];
        }
        c[row * bCols + col] = sum;
    }
}

Matrix *MatMul::executeGPU() {
    std::cout << "Using GPU" << std::endl;
    
    int aRows = a->getNumRows();
    int aCols = a->getNumCols();
    int bCols = b->getNumCols();
    
    // Create arrays for CUDA
    double *host_a = new double[aRows * aCols];
    double *host_b = new double[aCols * bCols];
    double *host_c = new double[aRows * bCols];
    
    // Copy matrix data to arrays
    for(int i = 0; i < aRows; i++) {
        for(int j = 0; j < aCols; j++) {
            host_a[i * aCols + j] = a->get_val_matrix(i, j);
        }
    }
    
    for(int i = 0; i < aCols; i++) {
        for(int j = 0; j < bCols; j++) {
            host_b[i * bCols + j] = b->get_val_matrix(i, j);
        }
    }
    
    // Perform CUDA multiplication
    matrixMultiplyCUDA(host_a, host_b, host_c, aRows, aCols, bCols);
    
    // Copy results back to matrix
    for(int i = 0; i < aRows; i++) {
        for(int j = 0; j < bCols; j++) {
            c->set_val_matrix(i, j, host_c[i * bCols + j]);
        }
    }
    
    // Cleanup
    delete[] host_a;
    delete[] host_b;
    delete[] host_c;
    
    return c;
}

void MatMul::matrixMultiplyCUDA(double *a, double *b, double *c, int aRows, int aCols, int bCols) {
    double *devA, *devB, *devC;
    
    // Allocate device memory
    cuda_check(cudaMalloc((void**)&devA, aRows * aCols * sizeof(double)));
    cuda_check(cudaMalloc((void**)&devB, aCols * bCols * sizeof(double)));
    cuda_check(cudaMalloc((void**)&devC, aRows * bCols * sizeof(double)));
    
    // Copy data from host to device
    cuda_check(cudaMemcpy(devA, a, aRows * aCols * sizeof(double), cudaMemcpyHostToDevice));
    cuda_check(cudaMemcpy(devB, b, aCols * bCols * sizeof(double), cudaMemcpyHostToDevice));
    
    // Define block and grid dimensions
    dim3 block(16, 16);
    dim3 grid((bCols + 15) / 16, (aRows + 15) / 16);
    
    // Launch kernel
    matMulKernel<<<grid, block>>>(devA, devB, devC, aRows, aCols, bCols);
    
    // Copy result back to host
    cuda_check(cudaMemcpy(c, devC, aRows * bCols * sizeof(double), cudaMemcpyDeviceToHost));
    
    // Free device memory
    cudaFree(devA);
    cudaFree(devB);
    cudaFree(devC);
}

} // namespace utils