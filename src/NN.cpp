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
        Matrix *c= (new utils::MatMul(a, b))->execute();

        // std::vector<double> vals;
        for(int c_index= 0; c_index < c->getNumCols(); c_index++){
            // vals.push_back(c->get_val_matrix(0, c_index));
            this->setNeuronVal(i + 1, c_index, c->get_val_matrix(0, c_index));
        }
    }

    if (!target.empty() && loss_fn) {
        // Get output values from the last layer (output layer)
        std::vector<Neuron *>  outNeurons= this->layers.at(this->layers.size() - 1)->getNeurons();
        std::vector<double> output;
        for (int i = 0; i < target.size(); i++) {
            output.push_back(outNeurons.at(i)->get_activatedval());
        }

        // Compute total error using the selected loss function
        this->error = loss_fn->computeLoss(target, output);
        
        // Compute individual errors for each output neuron
        this->errors = loss_fn->computeGradient(target, output);
    } else {
        std::cerr << "Error: No target set or loss function selected!" << std::endl;
    }
}

void NeuralNet::setError(std::string& loss){
    if (this->target.size() == 0){
        std::cerr << "Target must be greater than 0" << std::endl;
        assert(false);
    }

    if (this->target.size() != this->layers.at(this->topologySize - 1)->layerSize()){
        std::cerr << "The Size of the Target: " << this->target.size() << " is not equal to the Output: "
        << this->layers.at(this->topologySize - 1)->layerSize() << std::endl;
        assert(false);
    }

    
    if (loss == "mse"){
        loss_fn= std::make_unique<MSE>();
    }
    else if (loss == "mae"){
        loss_fn= std::make_unique<MAE>();
    }
    else if (loss == "ce"){
        loss_fn= std::make_unique<CrossEntropy>();
    }
    else {
        throw std::invalid_argument("Invalid loss type. Expected 'mse', 'mae', or 'ce'.");
    }

}

void NeuralNet::setInputs(std::vector<double> input){
    this->input = input;

    for (int i= 0; i < input.size(); i++){
        this->layers.at(0)->set_val_layer(i, input.at(i));
    }
}

void NeuralNet::setTarget(std::vector<double> target){

    if (target.size() != topology.back()) {
        std::cerr << "Target size does not match the output layer size!" << std::endl;
        return;
    }
    // targets are not fed into the network; they are only used for loss comparison.
    this->target = target;

}

void NeuralNet::NNprintToConcole(){
    
    for (int i= 0; i < this->layers.size(); i++){
        std::cout << "Layer: " << i << '\n';
        if (i == 0){
            Matrix *m= this->layers.at(i)->matrixifyVals();
            m->printToConsole();
        }
        else {
            Matrix *m= this->layers.at(i)->matrixifyActivatedVals();
            m->printToConsole();
        }
    }
}