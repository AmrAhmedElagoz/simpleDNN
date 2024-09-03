#ifndef NEURON_HPP
#define NEURON_HPP

#include <iostream>

class Neuron{

    public:
        Neuron(double val);

        void activate();
        void derive();

        double get_val_neuron() { return this-> val; }
        double get_activatedval() { return this-> activatedval; }
        double get_derivedval() { return this-> derivedval; }
        void set_val_neuron(double val);

    private:
        double val;
        double activatedval;
        double derivedval;
};


#endif