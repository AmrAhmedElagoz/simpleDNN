#ifndef NN_HPP
#define NN_HPP

#include <iostream>
#include <vector>
#include <cassert>
#include "Matrix.hpp"
#include "Layer.hpp"
#include "loss.hpp"
#include <memory>

class NeuralNet{
    public:
        NeuralNet(std::vector<int> topology);
        void setInputs(std::vector<double> input);
        void setTarget(std::vector<double> target);
        void NNprintToConcole();
        void feedForward();
        void setError(std::string& loss);

        Matrix *getNeuronMatrix(int index){ return this->layers.at(index)->matrixifyVals(); }
        Matrix *getActivatedNeuronMatrix(int index) { return this->layers.at(index)->matrixifyActivatedVals(); }
        Matrix *getDerivedNeuronMatrix(int index) { return this->layers.at(index)->matrixifyDrivedVals(); }
        Matrix *getWeightMatrix(int index) { return this->matrixWeights.at(index); }
        void setNeuronVal(int indexLayer, int indexNeuron, double val) { this->layers.at(indexLayer)->set_val_layer(indexNeuron, val); }
        double getTotalError() { return this->error; }
        std::vector<double> getErrors() { return this->errors; }


    private:
        std::unique_ptr<BaseLoss> loss_fn;
        int topologySize;
        std::vector<double> input;
        std::vector<int> topology;
        std::vector<Layer *> layers;
        std::vector<Matrix *> matrixWeights;
        std::vector<double> target;
        double error{};
        std::vector<double> errors;
        std::vector<double> internalErrors;
};


#endif