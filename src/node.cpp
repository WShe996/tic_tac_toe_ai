#include "node.h"
#include <iostream>
#include <sstream>

Node::Node(ActivatorType type, double bias, std::vector<double> weights)
    : weights_(std::move(weights)), bias_(bias), type_(type) {}

double Node::compute_weighted_sum(const std::vector<double>& inputs) {
    double sum = 0.0;
    for (std::size_t i = 0; i < inputs.size(); ++i) {
        sum += inputs[i] * weights_[i];
    }
    sum += bias_;
    z_ = sum;
    return sum;
}

double Node::activate(double z) const {
    switch (type_) {
        case ActivatorType::None:       throw std::invalid_argument("No activation function selected");
        case ActivatorType::Identity:   return z;
        case ActivatorType::BinaryStep: return (z >= 0.0) ? 1.0 : 0.0;
        case ActivatorType::Sigmoid:    return 1.0 / (1.0 + std::exp(-z));
        case ActivatorType::TanH:       return std::tanh(z);
        case ActivatorType::ReLU:       return std::max(0.0, z);
        case ActivatorType::GELU:       return 0.5 * z * (1.0 + std::erf(z / std::sqrt(2.0)));
        case ActivatorType::Softplus:   return std::log(1.0 + std::exp(z));
        case ActivatorType::LeakyReLU:  return (z >= 0.0) ? z : 0.01 * z;
        case ActivatorType::SiLU:       return z / (1.0 + std::exp(-z));
        case ActivatorType::Mish:       return z * std::tanh(std::log(1.0 + std::exp(z)));
        case ActivatorType::Gaussian:   return std::exp(-z * z);
        case ActivatorType::GCU:        return z * std::cos(z);
        case ActivatorType::SQU:        return z * z + z;
        case ActivatorType::NCU:        return z - z * z * z;
    }
    return 0.0;
}

double Node::activate_derv(double z) const {
    switch (type_) {
        case ActivatorType::None:       throw std::invalid_argument("No activation function selected");
        case ActivatorType::Identity:   return 1.0;
        case ActivatorType::BinaryStep:
            if (z == 0.0) throw std::invalid_argument("Binary step derivative undefined at 0");
            return 0.0;
        case ActivatorType::Sigmoid: {
            double s = 1.0 / (1.0 + std::exp(-z));
            return s * (1.0 - s);
        }
        case ActivatorType::TanH: {
            double t = std::tanh(z);
            return 1.0 - t * t;
        }
        case ActivatorType::ReLU:
            if (z == 0.0) throw std::invalid_argument("ReLU derivative undefined at 0");
            return (z > 0.0) ? 1.0 : 0.0;
        case ActivatorType::GELU:       throw std::invalid_argument("GELU derivative not implemented");
        case ActivatorType::Softplus:   return 1.0 / (1.0 + std::exp(-z));
        case ActivatorType::LeakyReLU:  return (z >= 0.0) ? 1.0 : 0.01;
        case ActivatorType::SiLU: {
            double ex = std::exp(-z);
            double d = (1.0 + ex);
            return (1.0 + ex + z * ex) / (d * d);
        }
        case ActivatorType::Mish: {
            double ex  = std::exp(z);
            double num = ex * (4.0*std::exp(2.0*z) + std::exp(3.0*z)
                         + 4.0*(1.0+z) + ex*(6.0+4.0*z));
            double den = (2.0 + 2.0*ex + std::exp(2.0*z));
            return num / (den * den);
        }
        case ActivatorType::Gaussian:   return -2.0 * z * std::exp(-z * z);
        case ActivatorType::GCU:        return std::cos(z) - z * std::sin(z);
        case ActivatorType::SQU:        return 2.0 * z + 1.0;
        case ActivatorType::NCU:        return 1.0 - 3.0 * z * z;
    }
    return 0.0;
}

double Node::get_activation(const std::vector<double>& inputs) {
    inputs_ = inputs;
    double z = compute_weighted_sum(inputs);
    a_ = activate(z);
    return a_;
}

double Node::get_activation_derv(double a) const { return activate_derv(a); }

std::string Node::get_activation_name() const {
    switch (type_) {
        case ActivatorType::None:       return "No activation";
        case ActivatorType::Identity:   return "identity";
        case ActivatorType::BinaryStep: return "binary step";
        case ActivatorType::Sigmoid:    return "sigmoid";
        case ActivatorType::TanH:       return "tan hyperbolic";
        case ActivatorType::ReLU:       return "ReLU";
        case ActivatorType::GELU:       return "GELU";
        case ActivatorType::Softplus:   return "softplus";
        case ActivatorType::LeakyReLU:  return "leakyReLU";
        case ActivatorType::SiLU:       return "SiLU";
        case ActivatorType::Mish:       return "mish";
        case ActivatorType::Gaussian:   return "gaussian";
        case ActivatorType::GCU:        return "GCU";
        case ActivatorType::SQU:        return "SQU";
        case ActivatorType::NCU:        return "NCU";
    }
    return "unknown";
}

int Node::get_weight_count() const { return static_cast<int>(weights_.size()); }

void Node::set_weights(const std::vector<double>& w) {
    if (w.size() != weights_.size()) throw std::invalid_argument("Weight vector size mismatch");
    weights_ = w;
}

void Node::set_bias(double b) { bias_ = b; }

std::vector<double> Node::back_propagate(double error_signal, double learn_rate, bool trace) {
    if (trace) {
        std::cout << "**Weights\n";
        for (auto w : weights_) std::cout << w << "\n";
        std::cout << "**Bias\n" << bias_ << "\n";
    }

    double dC_dA = error_signal;
    double dA_dZ = get_activation_derv(a_);

    std::vector<double> new_weights(weights_.size());
    for (std::size_t i = 0; i < inputs_.size(); ++i) {
        double grad = dC_dA * dA_dZ * inputs_[i];
        if (trace) std::cout << "**Weight Change\n" << learn_rate * grad << "\n";
        new_weights[i] = weights_[i] - learn_rate * grad;
    }

    old_weights_ = weights_;
    set_weights(new_weights);

    if (trace) std::cout << "**Bias Change\n" << learn_rate * dC_dA * dA_dZ << "\n";
    set_bias(bias_ - learn_rate * dC_dA * dA_dZ);

    std::vector<double> next_errors(old_weights_.size());
    for (std::size_t i = 0; i < old_weights_.size(); ++i) {
        next_errors[i] = dC_dA * dA_dZ * old_weights_[i];
    }
    return next_errors;
}

std::string Node::serialize() const {
    std::ostringstream oss;
    oss << ":{";
    for (std::size_t i = 0; i < weights_.size(); ++i) {
        oss << weights_[i];
        if (i + 1 < weights_.size()) oss << ",";
    }
    oss << "}" << bias_;
    return oss.str();
}
