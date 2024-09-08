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
        void feedForward();

        Matrix *getNeuronMatrix(int index){ return this->layers.at(index)->matrixifyVals(); }
        Matrix *getActivatedNeuronMatrix(int index) { return this->layers.at(index)->matrixifyActivatedVals(); }
        Matrix *getDerivedNeuronMatrix(int index) { return this->layers.at(index)->matrixifyDrivedVals(); }
        Matrix *getWeightMatrix(int index) { return this->matrixWeights.at(index); }


    private:
        int topologySize;
        std::vector<double> input;
        std::vector<int> topology;
        std::vector<Layer *> layers;
        std::vector<Matrix *> matrixWeights;
};


#endif