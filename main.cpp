#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>
#include "neural_network.h"
#include "game_board.h"
using namespace std;

/*
int test()
{
	model my_model = model();
	my_model.load("model2.txt");
	vector<double> number = my_model.solve_model({1,1,0,0,0,-1,0,0,-1});
	cout << number[0] << endl;
	cin.get();
	return(0);
}
*/


void parse_data(vector<vector<double>>& x_dat, vector<vector<double>>& y_dat)
{
	fstream _file("data.csv", std::fstream::in);
	string str = "";
	vector<double> temp;
	while (getline(_file, str))
	{
		while (str.find(",") != string::npos)
		{
			int num = stod(str.substr(0, str.find(",")));
			temp.push_back(num);
			str.erase(0, str.find(",") + 1);
			if (str == ",") { break; }
		}
		y_dat.push_back({ temp[temp.size() - 1] });
		temp.pop_back();
		x_dat.push_back(temp);
		temp.clear();
	}
}

int create_data()
{
	fstream file("data.csv", std::fstream::in | std::fstream::app);
	int num = 10000; //change for amount of data points needed
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0,2);

	for(int i=0;i<num;i++) {
		vector<vector<int>> gen_data;
		game_board my_game = game_board();

		while(!my_game.check_win())
		{
			int a = dis(gen);
			int b = dis(gen);
			if(my_game.can_move(a,b))
			{
				gen_data.push_back(my_game.get_game_vector());
			} 
		}

		int score = my_game.calc_end_game();

		for(int j=0;j<gen_data.size();j++)
		{
			gen_data[j].push_back(score);
		}

		for(int j=0;j<gen_data.size();j++)
		{
			for(int k=0;k<gen_data[0].size();k++)
			{
				file << gen_data[j][k];
				file << ",";
			}
			file << "\n";
		}
	}
	file.close();
	return(0);
}

int train_data() {
	vector<vector<double>> x_data;
	vector<vector<double>> y_data;
	parse_data(x_data, y_data);
	
	model my_model(9, MSE, 0.02);
	my_model.add_hidden_layer(tanH, 9);
	my_model.add_hidden_layer(tanH, 16);
	my_model.add_hidden_layer(tanH, 9);
	my_model.add_hidden_layer(tanH, 1);
	
	my_model.train(x_data, y_data, 50, false);
	my_model.save("model2.txt");
	
	vector<double> solution1 = my_model.solve_model({1,1,0,0,0,-1,0,0,-1});
	vector<double> solution2 = my_model.solve_model({1,1,-1,0,0,0,0,0,-1});
	
	cout << solution1[0] << endl;
	cout << solution2[0] << endl; 
	
	return 0;
}

int main()
{
	create_data();
	train_data();
}
