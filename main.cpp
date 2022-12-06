#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "neural_network.h"
#include "game_board.h"
using namespace std;

int main()
{
	model my_model(9, MSE, 0.02);
	my_model.add_hidden_layer(tanH, 9);
	my_model.add_hidden_layer(tanH, 81);
	my_model.add_hidden_layer(tanH, 9);
	my_model.add_hidden_layer(tanH, 1);
	return 0;
}


