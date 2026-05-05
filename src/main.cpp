#include "neural_network.h"
#include "game_board.h"
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

void generate_training_data(const std::string& path, int num_games) {
    std::ofstream file(path, std::ios::app);
    if (!file) throw std::runtime_error("Cannot open: " + path);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 2);

    for (int i = 0; i < num_games; ++i) {
        std::vector<std::vector<int>> snapshots;
        GameBoard board;
        while (!board.is_game_over()) {
            if (board.try_move(dist(gen), dist(gen)))
                snapshots.push_back(board.to_vector());
        }
        int result = board.score();
        for (const auto& snap : snapshots) {
            for (int v : snap) file << v << ",";
            file << result << ",\n";
        }
    }
}

void parse_csv(const std::string& path,
               std::vector<std::vector<double>>& x, std::vector<std::vector<double>>& y) {
    std::ifstream file(path);
    if (!file) throw std::runtime_error("Cannot open: " + path);
    std::string line;
    while (std::getline(file, line)) {
        std::vector<double> row;
        std::size_t pos;
        while ((pos = line.find(',')) != std::string::npos) {
            auto tok = line.substr(0, pos);
            if (!tok.empty()) row.push_back(std::stod(tok));
            line.erase(0, pos+1);
        }
        if (row.size() < 2) continue;
        y.push_back({row.back()});
        row.pop_back();
        x.push_back(std::move(row));
    }
}

void train_model(const std::string& data_path, const std::string& model_path) {
    std::vector<std::vector<double>> x, y;
    parse_csv(data_path, x, y);

    Model model(9, ErrorFunction::MSE, 0.02);
    model.add_hidden_layer(ActivatorType::TanH, 9);
    model.add_hidden_layer(ActivatorType::TanH, 16);
    model.add_hidden_layer(ActivatorType::TanH, 9);
    model.add_hidden_layer(ActivatorType::TanH, 1);
    model.train(x, y, 50, false);
    model.save(model_path);

    auto s1 = model.predict({1,1,0,0,0,-1,0,0,-1});
    auto s2 = model.predict({1,1,-1,0,0,0,0,0,-1});
    std::cout << "Sample 1: " << s1[0] << "\nSample 2: " << s2[0] << "\n";
}

int main() {
    generate_training_data("data.csv", 10000);
    train_model("data.csv", "model2");
    return 0;
}
