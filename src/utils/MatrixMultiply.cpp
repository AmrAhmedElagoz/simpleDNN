#include "../../include/utils/MatrixMultiply.hpp"

utils::MatrixMultiply::MatrixMultiply(Matrix *, Matrix *b){
    this->a= a;
    this->b= b;

    if (a->getNumCols() != b->getNumRows()){
        std::cerr << "A rows: " << a->getNumRows() << " != B cols" << b->getNumCols() << std::endl;
        assert(false);
    }

    this->c= new Matrix(a->getNumRows(), b->getNumCols(), false);
}

/*a brute force ijk algorithm for matrix multiplication*/
Matrix *utils::MatrixMultiply::execut(){
    for(int i= 0; i < a->getNumRows(); i++){
        for(int j= 0; j < b->getNumCols(); j++){
            for(int k= 0; k < b->getNumRows(); k++){
                double p= this->a->get_val_matrix(i, k) * b->get_val_matrix(k, j);
                double newVal= this->c->get_val_matrix(i, j) + p; /*accumulate the result given that it's zeros*/
                this->c->set_val_matrix(i, j, newVal);
            }
        }
    }
}