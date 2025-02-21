#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>

class Matrix{


    public:
        Matrix(int numRows, int numCols, bool isRandom);
        
        // a pointer to a new Matrix that is the transpose of the current Matrix
        Matrix *transpose();
        void printToConsole();
        void set_val_matrix(int r, int c, double val);
        double get_val_matrix(int r, int c);

        double getRandomNumber();

        int getNumRows() { return this->numRows; }
        int getNumCols() { return this->numCols; }

    private:
        int numRows;
        int numCols;

        // 2D vector to store the Matrix elements
        std::vector<std::vector<double>> elements;
};



#endif