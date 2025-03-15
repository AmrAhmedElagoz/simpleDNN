#ifndef LOSS_HPP
#define LOSS_HPP

#include <vector>
#include "Neuron.hpp"

class BaseLoss {
public:

    virtual double computeLoss(const std::vector<double>& y_true, const std::vector<double>& y_pred) const = 0;
    virtual std::vector<double> computeGradient(const std::vector<double>& y_true, const std::vector<double>& y_pred) const = 0;
    virtual ~BaseLoss() = default;
};

// MSE
class MSE : public BaseLoss {
public:

    double computeLoss(const std::vector<double>& y_true, const std::vector<double>& y_pred) const override;
    std::vector<double> computeGradient(const std::vector<double>& y_true, const std::vector<double>& y_pred) const override;
};


// MAE
class MAE : public BaseLoss {
    public:
        double computeLoss(const std::vector<double>& y_true, const std::vector<double>& y_pred) const override;
        std::vector<double> computeGradient(const std::vector<double>& y_true, const std::vector<double>& y_pred) const override;
    };
    

    // CE
class CrossEntropy : public BaseLoss {
    public:
        double computeLoss(const std::vector<double>& y_true, const std::vector<double>& y_pred) const override;
        std::vector<double> computeGradient(const std::vector<double>& y_true, const std::vector<double>& y_pred) const override;
    };


#endif 
