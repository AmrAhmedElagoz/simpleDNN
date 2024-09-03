#include "Matrix.hpp"
#include <random>
#include <vector>

double Matrix::getRandomNumber(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    return dis(gen);
}

Matrix::Matrix(int numRows, int numCols, bool isRandom){
    this->numRows= numRows;
    this->numCols= numCols;

    for (int i{}; i < numRows; i++){
        std::vector<double> colValues{};

        for (int j{}; j < numCols; j++){
            double r{};
            if (isRandom){
                r= this->getRandomNumber();
            }
            colValues.push_back(r);
        }
        this->elements.push_back(colValues);
    }
}

Matrix *Matrix::transpose(){

    Matrix *m= new Matrix(this->numCols, this->numRows, false);
    for (int i=0; i < numRows; i++){
        for (int j= 0; j < numCols; j++){
            m->set_val_matrix(j, i, this->get_val_matrix(j, i));
        }
    }

    return m;
}

void Matrix::set_val_matrix(int r, int c, double val){
    
    this->elements.at(r).at(c) = val;
}

double Matrix::get_val_matrix(int r, int c){
    
    return this->elements.at(r).at(c);
}

void Matrix::printToConcole(){
    for (int i{}; i < numRows; i++){
        for (int j{}; j < numCols; j++){
            std::cout << this->elements.at(i).at(j) << "\t";
        }
        std::cout << std::endl;
    }
}