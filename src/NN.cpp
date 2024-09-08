#include "NN.hpp"
#include "utils/MatrixMultiply.hpp"

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

void NeuralNet::feedForward(){
    // loop from the input to the output excluding the output itself (hence the -1)
    // the output will be the result, there is no operation to be done.
    for(int i= 0; i < (this->layers.size() - 1); i++){
        // input
        Matrix *a= this->getNeuronMatrix(i);
        // if the layer is not input, get the activated matrix
        if(i != 0){
            a= this->getActivatedNeuronMatrix(i);
        }

        Matrix *b= this->getWeightMatrix(i);
        Matrix *c= (new utils::MatrixMultiply(a, b))->execut();

        std::vector<double> vals;
        for(int c_index= 0; c_index < c->getNumCols(); c_index++){
            vals.push_back(c->get_val_matrix(0, c_index));
        }
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