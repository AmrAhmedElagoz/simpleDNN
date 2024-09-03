#ifndef LAYER_HPP
#define LAYER_HPP

#include <iostream>
#include "Neuron.hpp"
#include "Matrix.hpp"


class Layer{
    /*the size refers to how many neurons contained in the layer*/

    public:
        Layer(int size);
        void set_val_layer(int i, double val);
        Matrix *matrixifyVals();
        Matrix *matrixifyActivatedVals();
        Matrix *matrixifyDrivedVals();
        
    private:
        int size;

        std::vector<Neuron *> neurons;
};


#endif