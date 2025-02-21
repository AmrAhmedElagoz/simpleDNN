#include "Matrix.hpp"
#include <random>
#include <vector>

double Matrix::getRandomNumber(){
    // provide random device/seed
    std::random_device rd;
    // Mersenne Twister generator for random numbers based on the device/seed
    std::mt19937 gen(rd());
    // distributes random numbers uniformly between 0 and 1
    std::uniform_real_distribution<> dis(0, 1);
    // returns a reandom number between 0 and 1
    return dis(gen);
}

Matrix::Matrix(int numRows, int numCols, bool isRandom){
    // seting the numRows and numCols values
    this->numRows= numRows;
    this->numCols= numCols;

    // for each row in Rows
    // this is a row-major implementation for Matrix: elements[row][col]
    for (int i{}; i < numRows; i++){
        // initialize a new colValues
        std::vector<double> colValues{};

        // for each column in Columns
        for (int j{}; j < numCols; j++){
            // init r to 0
            double r{};
            if (isRandom){
                // if isRandom is true then set r to that value
                r= this->getRandomNumber();
            }
            // push back that value to complete the column values for each row
            colValues.push_back(r);
        }
        this->elements.push_back(colValues);
    }
}

Matrix *Matrix::transpose(){

    // making a new Matrix with transposed axis
    Matrix *m= new Matrix(this->numCols, this->numRows, false);
    // getting the elements for each position in the old Matrix
    for (int i=0; i < numRows; i++){
        for (int j= 0; j < numCols; j++){
            // setting the value on the ij's position to ji's new Matrix position
            m->set_val_matrix(j, i, this->get_val_matrix(j, i));
        }
    }

    // returns a pointer to the transposed Matrix
    return m;
}

void Matrix::set_val_matrix(int r, int c, double val){
    
    this->elements.at(r).at(c) = val;
}

double Matrix::get_val_matrix(int r, int c){
    
    return this->elements.at(r).at(c);
}

void Matrix::printToConsole(){
    for (int i{}; i < numRows; i++){
        for (int j{}; j < numCols; j++){
            std::cout << this->get_val_matrix(i, j) << "\t";
        }
        std::cout << std::endl;
    }
}