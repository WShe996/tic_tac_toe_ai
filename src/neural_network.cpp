#include "neural_network.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

Model::Model(int input_size, ErrorFunction error_fn, double learning_rate)
    : learning_rate_(learning_rate), error_fn_(error_fn), input_size_(input_size) {}

void Model::add_hidden_layer(ActivatorType type, int num_nodes) {
    int prev = layers_.empty() ? input_size_ : layers_.back().get_size();
    layers_.emplace_back(type, num_nodes, prev);
}

std::vector<double> Model::predict(const std::vector<double>& inputs) {
    if (static_cast<int>(inputs.size()) != input_size_)
        throw std::invalid_argument("Input vector size mismatch");

    auto current = layers_[0].solve(inputs);
    for (std::size_t i = 1; i < layers_.size(); ++i)
        current = layers_[i].solve(current);
    outputs_ = current;
    return current;
}

std::vector<double> Model::compute_error(const std::vector<double>& expected) const {
    if (expected.size() != static_cast<std::size_t>(layers_.back().get_size()))
        throw std::invalid_argument("Expected vector size mismatch");
    switch (error_fn_) {
        case ErrorFunction::None: throw std::invalid_argument("No error function selected");
        case ErrorFunction::MSE:  return mse(expected);
        default: throw std::invalid_argument("Error function not yet implemented");
    }
}

std::vector<double> Model::compute_error_derv(const std::vector<double>& expected) const {
    switch (error_fn_) {
        case ErrorFunction::None: throw std::invalid_argument("No error function selected");
        case ErrorFunction::MSE:  return mse_derv(expected);
        default: throw std::invalid_argument("Error function derivative not yet implemented");
    }
}

std::vector<double> Model::mse(const std::vector<double>& expected) const {
    std::vector<double> r;
    r.reserve(expected.size());
    for (std::size_t i = 0; i < expected.size(); ++i) {
        double d = outputs_[i] - expected[i];
        r.push_back(0.5 * d * d);
    }
    return r;
}

std::vector<double> Model::mse_derv(const std::vector<double>& expected) const {
    std::vector<double> r;
    r.reserve(expected.size());
    for (std::size_t i = 0; i < expected.size(); ++i)
        r.push_back(-(expected[i] - outputs_[i]));
    return r;
}

void Model::back_propagate(const std::vector<double>& expected, bool trace) {
    auto dervs = compute_error_derv(expected);
    for (int i = static_cast<int>(layers_.size()) - 1; i >= 0; --i)
        dervs = layers_[i].back_propagate(dervs, learning_rate_, trace);
}

void Model::train(const std::vector<std::vector<double>>& x_data,
                  const std::vector<std::vector<double>>& y_data,
                  int epochs, bool trace) {
    for (int epoch = 0; epoch < epochs; ++epoch) {
        std::cout << "Epoch " << (epoch+1) << " of " << epochs << "\n";
        for (std::size_t i = 0; i < x_data.size(); ++i) {
            predict(x_data[i]);
            auto errors = compute_error(y_data[i]);
            if (trace) {
                std::cout << "Inputs\n";   print_vector(x_data[i]);
                std::cout << "Actual\n";   print_vector(y_data[i]);
                std::cout << "Estimate\n"; print_vector(outputs_);
                std::cout << "Error\n";    print_vector(errors);
                back_propagate(y_data[i], true);
                std::cout << "==================\n";
            } else {
                back_propagate(y_data[i], false);
            }
        }
    }
    predict(x_data[0]);
    auto errors = compute_error(y_data[0]);
    std::cout << "Inputs\n";   print_vector(x_data[0]);
    std::cout << "Actual\n";   print_vector(y_data[0]);
    std::cout << "Estimate\n"; print_vector(outputs_);
    std::cout << "Error\n";    print_vector(errors);
    std::cout << "==================\n";
}

void Model::save(const std::string& filename) const {
    std::ofstream file(filename + ".txt", std::ios::trunc);
    if (!file) throw std::runtime_error("Cannot open file: " + filename);
    file << static_cast<int>(error_fn_) << "\n"
         << input_size_ << "\n" << learning_rate_ << "\n";
    for (const auto& layer : layers_) file << layer.serialize() << "\n";
}

void Model::load(const std::string& filename) {
    std::ifstream file(filename + ".txt");
    if (!file) throw std::runtime_error("Cannot open file: " + filename);
    std::string content((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());

    auto next_line = [&]() -> std::string {
        auto pos = content.find('\n');
        if (pos == std::string::npos) { auto l = content; content.clear(); return l; }
        auto l = content.substr(0, pos); content.erase(0, pos+1); return l;
    };

    error_fn_      = static_cast<ErrorFunction>(std::stoi(next_line()));
    input_size_    = std::stoi(next_line());
    learning_rate_ = std::stod(next_line());
    layers_.clear();
    int idx = 0;

    while (!content.empty()) {
        if (content.size() < 2 || content[0] != '>') break;
        content.erase(0, 2);
        std::string act_name = content.substr(0, content.find('\n'));
        content.erase(0, content.find('\n')+1);
        auto a_type = parse_activator(act_name);

        std::vector<std::pair<std::vector<double>, double>> node_data;
        while (!content.empty() && content[0] == ':') {
            content.erase(0, 2);
            auto cb = content.find('}');
            std::istringstream wss(content.substr(0, cb));
            content.erase(0, cb+1);
            std::vector<double> weights;
            std::string tok;
            while (std::getline(wss, tok, ','))
                if (!tok.empty()) weights.push_back(std::stod(tok));
            auto nl = content.find('\n');
            double bias = std::stod(content.substr(0, nl));
            content.erase(0, nl != std::string::npos ? nl+1 : content.size());
            node_data.emplace_back(std::move(weights), bias);
        }
        add_hidden_layer(a_type, static_cast<int>(node_data.size()));
        layers_[idx++].load(node_data);
    }
}

ActivatorType Model::parse_activator(const std::string& name) {
    if (name == "No activation")  return ActivatorType::None;
    if (name == "identity")       return ActivatorType::Identity;
    if (name == "binary step")    return ActivatorType::BinaryStep;
    if (name == "sigmoid")        return ActivatorType::Sigmoid;
    if (name == "tan hyperbolic") return ActivatorType::TanH;
    if (name == "ReLU")           return ActivatorType::ReLU;
    if (name == "GELU")           return ActivatorType::GELU;
    if (name == "softplus")       return ActivatorType::Softplus;
    if (name == "leakyReLU")      return ActivatorType::LeakyReLU;
    if (name == "SiLU")           return ActivatorType::SiLU;
    if (name == "mish")           return ActivatorType::Mish;
    if (name == "gaussian")       return ActivatorType::Gaussian;
    if (name == "GCU")            return ActivatorType::GCU;
    if (name == "SQU")            return ActivatorType::SQU;
    if (name == "NCU")            return ActivatorType::NCU;
    throw std::invalid_argument("Unknown activation type: " + name);
}

void Model::print_vector(const std::vector<double>& v) {
    for (double val : v) std::cout << val << "\n";
}
