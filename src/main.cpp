#include <iostream>
#include <vector>
#include "NN.hpp"

int main(int argc, char **argv){

    std::vector<int> topology;
    topology.push_back(6); 
    topology.push_back(4); 
    topology.push_back(3); 
    topology.push_back(2);

    std::vector<double> input;
    input.push_back(0.8); 
    input.push_back(1.3); 
    input.push_back(-12.0);
    input.push_back(5.02);

    NeuralNet *nn= new NeuralNet(topology);
    nn->setInputs(input);
    nn->feedForward();
    nn->NNprintToConcole(); 

    return 0;
}
