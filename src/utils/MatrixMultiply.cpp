#include "../../include/utils/MatrixMultiply.hpp"
#include <omp.h>

utils::MatMul::MatMul(Matrix *a, Matrix *b, const std::string& type) {
    this->a = a;
    this->b = b;
    this->computeType = type;

    if (a->getNumCols() != b->getNumRows()) {
        std::cerr << "A cols: " << a->getNumCols() << " != B rows: " << b->getNumRows() << std::endl;
        assert(false);
    }
    this->c = new Matrix(a->getNumRows(), b->getNumCols(), false);
}

Matrix *utils::MatMul::execute() {
    #ifdef USE_CUDA
    if (computeType == "gpu") {
        return executeGPU();
    }
    #endif
    return executeCPU();
}

Matrix *utils::MatMul::executeCPU() {
    std::cout << "Using CPU" << std::endl;
    #pragma omp parallel for
    for(int i = 0; i < a->getNumRows(); i++) {
        for(int j = 0; j < b->getNumCols(); j++) {
            for(int k = 0; k < b->getNumRows(); k++) {
                double p = this->a->get_val_matrix(i, k) * b->get_val_matrix(k, j);
                double newVal = this->c->get_val_matrix(i, j) + p;
                this->c->set_val_matrix(i, j, newVal);
            }
        }
    }
    return this->c;
}