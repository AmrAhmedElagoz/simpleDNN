#ifndef NN_HPP
#define NN_HPP

#include <iostream>
#include <vector>
#include "Matrix.hpp"
#include "Layer.hpp"

class NeuralNet{
    public:
        NeuralNet(std::vector<int> topology);
        void setInputs(std::vector<double> input);

        void NNprintToConcole();

    private:
        int topologySize;
        std::vector<double> input;
        std::vector<int> topology;
        std::vector<Layer *> layers;
        std::vector<Matrix *> matrixWeights;
};


#endif