#include <iostream>
#include <vector>
#include "NN.hpp"

int main(int argc, char **argv){

    std::vector<int> topology = {6, 4, 4, 6};

    std::vector<double> input= {2.3, 5.1, -0.8, 1.12, 5.6, 0.7};
    // std::vector<double> target = {2.3, 5.1, -0.8, 1.12, 5.6, 0.7};

    NeuralNet *nn= new NeuralNet(topology);
    std::string loss= "mse";
    nn->setInputs(input);
    nn->setTarget(input);
    
    nn->setError(loss);
    nn->feedForward();
    nn->NNprintToConcole(); 

    return 0;
}
