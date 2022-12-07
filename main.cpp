#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>
#include "neural_network.h"
#include "game_board.h"
using namespace std;

int main()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0,2);
	while(true) {
	game_board my_game = game_board();
	while(!my_game.check_win())
	{
		int a, b;
		a = dis(gen);
		b = dis(gen);
		if(my_game.play_move(a,b))
		{
			my_game.print_board();
			cin.get();
		} 
	}
	cout << "the score is " << my_game.calc_end_game() << endl;
	cin.get();
	}
	return(0);
}

/*
model my_model(9, MSE, 0.02);
	my_model.add_hidden_layer(tanH, 9);
	my_model.add_hidden_layer(tanH, 81);
	my_model.add_hidden_layer(tanH, 9);
	my_model.add_hidden_layer(tanH, 1);
	return 0;

*/

