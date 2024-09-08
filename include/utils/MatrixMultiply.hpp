#ifndef _MATRIX_MULTIPLY_HPP_
#define _MATRIX_MULTIPLY_HPP_

#include <iostream>
#include <assert.h>
#include "../Matrix.hpp"

namespace utils{
    class MatrixMultiply
    {
    private:
        Matrix *a;
        Matrix *b;
        Matrix *c;

    public:
        MatrixMultiply(Matrix *a, Matrix *b);
        ~MatrixMultiply();

        Matrix *execut();
    };
    
}




#endif