#pragma once

#include "hidden_layer.h"
#include <string>
#include <vector>

enum class ErrorFunction { None = 0, MSE = 1, MAE = 2, MBE = 3, CEL = 4 };

class Model {
public:
    Model(int input_size, ErrorFunction error_fn, double learning_rate);
    Model() = default;

    void add_hidden_layer(ActivatorType type, int num_nodes);

    std::vector<double> predict(const std::vector<double>& inputs);
    std::vector<double> compute_error(const std::vector<double>& expected) const;
    std::vector<double> compute_error_derv(const std::vector<double>& expected) const;

    void back_propagate(const std::vector<double>& expected, bool trace);
    void train(const std::vector<std::vector<double>>& x_data,
               const std::vector<std::vector<double>>& y_data,
               int epochs, bool trace);

    void save(const std::string& filename) const;
    void load(const std::string& filename);

private:
    static ActivatorType parse_activator(const std::string& name);
    std::vector<double>  mse(const std::vector<double>& expected) const;
    std::vector<double>  mse_derv(const std::vector<double>& expected) const;
    static void          print_vector(const std::vector<double>& v);

    double                   learning_rate_ = 0.0;
    ErrorFunction            error_fn_      = ErrorFunction::None;
    std::vector<HiddenLayer> layers_;
    std::vector<double>      outputs_;
    int                      input_size_    = 0;
};
