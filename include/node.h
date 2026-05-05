#pragma once

#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>

enum class ActivatorType {
    None = 0, Identity, BinaryStep, Sigmoid, TanH, ReLU,
    GELU, Softplus, LeakyReLU, SiLU, Mish, Gaussian,
    GCU, SQU, NCU,
};

class Node {
public:
    Node(ActivatorType type, double bias, std::vector<double> weights);

    std::string get_activation_name() const;
    double      get_activation(const std::vector<double>& inputs);
    double      get_activation_derv(double a) const;
    int         get_weight_count() const;

    void set_weights(const std::vector<double>& new_weights);
    void set_bias(double new_bias);

    std::vector<double> back_propagate(double error_signal, double learn_rate, bool trace);
    std::string         serialize() const;

private:
    double compute_weighted_sum(const std::vector<double>& inputs);
    double activate(double z) const;
    double activate_derv(double z) const;

    std::vector<double> weights_;
    std::vector<double> old_weights_;
    std::vector<double> inputs_;
    double              bias_  = 0.0;
    double              z_     = 0.0;
    double              a_     = 0.0;
    ActivatorType       type_  = ActivatorType::None;
};
