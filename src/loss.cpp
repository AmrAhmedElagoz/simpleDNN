#include "loss.hpp"

#include <cmath>
#include <stdexcept>
#include <numeric>

// Mean Squared Error: Compute the loss
double MSE::computeLoss(const std::vector<double>& y_true, const std::vector<double>& y_pred) const {
    if (y_true.size() != y_pred.size()) {
        throw std::invalid_argument("Vectors y_true and y_pred must have the same length.");
    }

    double mse = 0.0;
    for (size_t i = 0; i < y_true.size(); ++i) {
        mse += std::pow(y_pred[i] - y_true[i], 2);
    }
    return mse / static_cast<double>(y_true.size());
}

// Mean Squared Error: Compute the gradient
std::vector<double> MSE::computeGradient(const std::vector<double>& y_true, const std::vector<double>& y_pred) const {
    if (y_true.size() != y_pred.size()) {
        throw std::invalid_argument("Vectors y_true and y_pred must have the same length.");
    }

    std::vector<double> gradients(y_true.size());
    for (size_t i = 0; i < y_true.size(); ++i) {
        gradients[i] = 2.0 * (y_pred[i] - y_true[i]) / static_cast<double>(y_true.size());
    }
    return gradients;
}

// Mean Absolute Error (MAE): Compute the loss
double MAE::computeLoss(const std::vector<double>& y_true, const std::vector<double>& y_pred) const {
    if (y_true.size() != y_pred.size()) {
        throw std::invalid_argument("Vectors y_true and y_pred must have the same length.");
    }

    double mae = 0.0;
    for (size_t i = 0; i < y_true.size(); ++i) {
        mae += std::abs(y_pred[i] - y_true[i]);
    }
    return mae / static_cast<double>(y_true.size());
}

// Mean Absolute Error (MAE): Compute the gradient
std::vector<double> MAE::computeGradient(const std::vector<double>& y_true, const std::vector<double>& y_pred) const {
    if (y_true.size() != y_pred.size()) {
        throw std::invalid_argument("Vectors y_true and y_pred must have the same length.");
    }

    std::vector<double> gradients(y_true.size());
    for (size_t i = 0; i < y_true.size(); ++i) {
        gradients[i] = (y_pred[i] > y_true[i] ? 1.0 : -1.0) / static_cast<double>(y_true.size());
    }
    return gradients;
}

// Cross Entropy Loss (Binary): Compute the loss
double CrossEntropy::computeLoss(const std::vector<double>& y_true, const std::vector<double>& y_pred) const {
    if (y_true.size() != y_pred.size()) {
        throw std::invalid_argument("Vectors y_true and y_pred must have the same length.");
    }

    double cross_entropy = 0.0;
    for (size_t i = 0; i < y_true.size(); ++i) {
        cross_entropy += -y_true[i] * std::log(y_pred[i]) - (1.0 - y_true[i]) * std::log(1.0 - y_pred[i]);
    }
    return cross_entropy / static_cast<double>(y_true.size());
}

// Cross Entropy Loss (Binary): Compute the gradient
std::vector<double> CrossEntropy::computeGradient(const std::vector<double>& y_true, const std::vector<double>& y_pred) const {
    if (y_true.size() != y_pred.size()) {
        throw std::invalid_argument("Vectors y_true and y_pred must have the same length.");
    }

    std::vector<double> gradients(y_true.size());
    for (size_t i = 0; i < y_true.size(); ++i) {
        gradients[i] = (y_pred[i] - y_true[i]) / (y_pred[i] * (1.0 - y_pred[i]));
    }
    return gradients;
}