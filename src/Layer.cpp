// Neural networks defined by its layers; input, hidden, and
// output layers

#include "Layer.hpp"

// when we call the layer we initialize it with the number
// of neurons we want each layer to have
Layer::Layer(int size){
    this->size= size;

    for(int i{}; i < size; i++){
        Neuron *n= new Neuron(0.00);
        this->neurons.push_back(n);
    }
}

/* set the value of neuron in layer given the index of the
neuron and the value*/
void Layer::set_val_layer(int i, double val){
    this->neurons.at(i)->set_val_neuron(val);
}

Matrix *Layer::matrixifyVals(){
    Matrix *m= new Matrix(1, this->neurons.size(), false);
 
    for (int i= 0; i < this->neurons.size(); i++){
        m->set_val_matrix(
            0,
            i,
            this->neurons.at(i)->get_val_neuron()
        );
    };
    return m;
}

Matrix *Layer::matrixifyActivatedVals(){
    Matrix *m= new Matrix(1, this->neurons.size(), false);
    for (int i= 0; i < this->neurons.size(); i++){
        m->set_val_matrix(
            0,
            i,
            this->neurons.at(i)->get_activatedval()
        );
    };
    return m;
}

Matrix *Layer::matrixifyDrivedVals(){
    Matrix *m= new Matrix(1, this->neurons.size(), false);
    for (int i= 0; i < this->neurons.size(); i++){
        m->set_val_matrix(
            0,
            i,
            this->neurons.at(i)->get_derivedval()
        );
    };
    return m;
}