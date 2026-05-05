#include "hidden_layer.h"
#include <iostream>
#include <random>
#include <sstream>

HiddenLayer::HiddenLayer(ActivatorType type, int size, int prev_layer_size)
    : size_(size), type_(type)
{
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    for (int i = 0; i < size; ++i) {
        std::vector<double> weights(prev_layer_size);
        for (auto& w : weights) w = dist(rng);
        nodes_.emplace_back(type, dist(rng), std::move(weights));
    }
}

std::vector<double> HiddenLayer::solve(const std::vector<double>& inputs) {
    std::vector<double> outputs;
    outputs.reserve(nodes_.size());
    for (auto& node : nodes_) outputs.push_back(node.get_activation(inputs));
    return outputs;
}

std::vector<double> HiddenLayer::back_propagate(
    const std::vector<double>& error_vector, double learn_rate, bool trace)
{
    std::vector<std::vector<double>> incoming;
    incoming.reserve(nodes_.size());
    for (std::size_t i = 0; i < nodes_.size(); ++i) {
        incoming.push_back(nodes_[i].back_propagate(error_vector[i], learn_rate, trace));
    }

    std::vector<double> summed(incoming[0].size(), 0.0);
    for (const auto& d : incoming)
        for (std::size_t i = 0; i < d.size(); ++i) summed[i] += d[i];
    return summed;
}

int HiddenLayer::get_size() const { return size_; }

std::string HiddenLayer::get_activation_name() const {
    return nodes_.empty() ? "empty" : nodes_[0].get_activation_name();
}

std::string HiddenLayer::serialize() const {
    std::ostringstream oss;
    oss << "> " << get_activation_name() << "\n";
    for (int i = 0; i < size_; ++i) oss << nodes_[i].serialize() << "\n";
    return oss.str();
}

void HiddenLayer::load(const std::vector<std::pair<std::vector<double>, double>>& node_data) {
    for (const auto& [weights, bias] : node_data) {
        nodes_.emplace_back(type_, bias, weights);
    }
}
