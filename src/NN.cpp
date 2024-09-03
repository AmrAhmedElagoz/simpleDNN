#include <NN.hpp>

NeuralNet::NeuralNet(std::vector<int> topology){
    this->topologySize= topology.size();
    this->topology= topology;

    // initializing the layers
    for (int i= 0; i < topologySize; i++){
        Layer *l= new Layer(topology.at(i));
        this->layers.push_back(l);
    }

    // initializing the weight matrices
    /* the weight matrices are always = number of layers - 1, 
    the number of rows are going to be the number of neurons to the
    left and the number of columns are the number of neurons to the 
    right and we can get them both from topology*/
    for (int i= 0; i < (topologySize - 1); i++){
        Matrix *m= new Matrix(topology.at(i), topology.at(i+1), true);
        this->matrixWeights.push_back(m);
    }
}

void NeuralNet::setInputs(std::vector<double> input){
    this->input = input;

    for (int i= 0; i < input.size(); i++){
        this->layers.at(0)->set_val_layer(i, input.at(i));
    }
}

void NeuralNet::NNprintToConcole(){
    
    for (int i= 0; i < this->layers.size(); i++){
        std::cout << "Layer: " << i << '\n';
        if (i == 0){
            Matrix *m= this->layers.at(i)->matrixifyVals();
            m->printToConcole();
        }
        else {
            Matrix *m= this->layers.at(i)->matrixifyActivatedVals();
            m->printToConcole();
        }
    }
}