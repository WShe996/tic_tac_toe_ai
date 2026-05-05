#pragma once

#include "node.h"
#include <string>
#include <utility>
#include <vector>

class HiddenLayer {
public:
    HiddenLayer(ActivatorType type, int size, int prev_layer_size);

    std::vector<double> solve(const std::vector<double>& inputs);
    std::vector<double> back_propagate(const std::vector<double>& error_vector,
                                       double learn_rate, bool trace);

    int         get_size() const;
    std::string get_activation_name() const;
    std::string serialize() const;
    void        load(const std::vector<std::pair<std::vector<double>, double>>& node_data);

private:
    int               size_  = 0;
    ActivatorType     type_  = ActivatorType::None;
    std::vector<Node> nodes_;
};
