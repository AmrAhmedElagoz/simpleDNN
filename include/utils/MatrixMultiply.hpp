#ifndef MATRIX_MULTIPLY_HPP_
#define MATRIX_MULTIPLY_HPP_

#include <iostream>
#include <assert.h>
#include <string>
#include "../Matrix.hpp"

namespace utils {

class MatMul {
public:
    // Constructor with type selection, defaults to "gpu"
    MatMul(Matrix *a, Matrix *b, const std::string& type = "gpu");
    Matrix *execute();

private:
    Matrix *a;
    Matrix *b;
    Matrix *c;
    std::string computeType;
    
    // Private methods for CPU and GPU computation
    Matrix *executeCPU();
    #ifdef USE_CUDA
    Matrix *executeGPU();
    void matrixMultiplyCUDA(double *a, double *b, double *c, int aRows, int aCols, int bCols);
    #endif
};

} // namespace utils
#endif