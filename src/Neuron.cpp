// This is the main building block for modern deep learning
// architectures, the neuron defines a value, the derivative
// and the activation of itself

#include "Neuron.hpp"
#include <math.h>

// the constructor takes an input value and calculate the
// derivative and activation of it
Neuron::Neuron(double val){
    this->val= val;
    activate();
    derive();
}

// activation here is basically a sigmoid
void Neuron::activate(){
    this->activatedval= this->val / (1 + abs(this->val));
}

// the derivative of sigmoid
void Neuron::derive(){
    this->derivedval= this->activatedval * (1 + this->activatedval);
}

void Neuron::set_val_neuron(double val){
    this->val= val;
    activate();
    derive();
}