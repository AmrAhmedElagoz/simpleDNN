#ifndef _MATRIX_MULTIPLY_HPP_
#define _MATRIX_MULTIPLY_HPP_

#include <iostream>
#include <assert.h>
#include "../Matrix.hpp"

#ifdef __CUDACC__
#include <cuda_runtime.h>  // CUDA runtime API
#endif
namespace utils{
    class MatMul
    {
    public:
        MatMul(Matrix *a, Matrix *b);
        Matrix *execut();
    
    private:
        Matrix *a;
        Matrix *b;
        Matrix *c;
    };
    #ifdef __CUDACC__
    // CUDA matrix multiplication function declaration
    void matrixMultiplyCUDA(double *a, double *b, double *c, int aRows, int aCols, int bCols);
    #endif   
}
#endif