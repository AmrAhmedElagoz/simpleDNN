#include "../../include/utils/MatrixMultiply.hpp"

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

void utils::matrixMultiplyCUDA(double *a, double *b, double *c, int aRows, int aCols, int bCols) {
    // Allocate device memory
    std::cout << "Using GPU" << std::endl;
    double *devA, *devB, *devC;
    cudaMalloc((void**)&devA, aRows * aCols * sizeof(double));
    cudaMalloc((void**)&devB, aCols * bCols * sizeof(double));
    cudaMalloc((void**)&devC, aRows * bCols * sizeof(double));

    // Copy data from host to device
    cudaMemcpy(devA, a, aRows * aCols * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(devB, b, aCols * bCols * sizeof(double), cudaMemcpyHostToDevice);

    // Define block and grid dimensions
    dim3 block(16, 16); // Block size: 16x16 threads
    dim3 grid((bCols + 15) / 16, (aRows + 15) / 16);

    // Launch kernel
    matMulKernel<<<grid, block>>>(devA, devB, devC, aRows, aCols, bCols);

    // Copy result back to host
    cudaMemcpy(c, devC, aRows * bCols * sizeof(double), cudaMemcpyDeviceToHost);

    // Free device memory
    cudaFree(devA);
    cudaFree(devB);
    cudaFree(devC);
}
