#include <iostream>
#include <fstream>
#include <string>
#include "neural_network.h"
using namespace std;

void print_vector(vector<double> nums)
{
	for(int i=0;i<nums.size();i++)
	{
		cout << nums[i] << "\n";
	}
}

vector<vector<vector<double>>> get_data()
{
	vector<vector<double>> inputs;
	vector<vector<double>> outputs;
	fstream _file("data.csv", std::fstream::in);
	string str;
	bool is_inputs = true;
	while(getline(_file, str))
	{
		if((str == "") || (str.find(",")==str.length()-1)){break;}
		vector<string> parced_string = {};
		vector<double> numbers = {};
		while(str.find(",")!=str.length()-1)
		{
			parced_string.push_back(str.substr(0,str.find(",")));
			str.erase(0,str.find(",")+1);
		}
		parced_string.push_back(str.substr(0,str.find(",")));
		for(int i=0;i<parced_string.size();i++)
		{
			numbers.push_back(stod(parced_string[i]));
		}
		if(is_inputs)
		{
			inputs.push_back(numbers);
		}
		else
		{
			outputs.push_back(numbers);
		}
		is_inputs = !is_inputs;
	}
	return {inputs,outputs};
}


/*
int main()
{
	vector<vector<double>> x_data = {{0.00,0.00,0.08,0.04,0.09},{0.00,0.09,0.04,0.03,0.08},{0.00,0.03,0.09,0.04,0.08}};
	vector<vector<double>> y_data = {{1,-1,-1,-1},{-1,1,-1,-1},{-1,-1,1,-1}};
	model my_network(5, MSE, 0.01);
	my_network.add_hidden_layer(tanH, 5);
	my_network.add_hidden_layer(tanH, 25);
	my_network.add_hidden_layer(tanH, 16);
	my_network.add_hidden_layer(tanH, 4);
	my_network.train(x_data, y_data, 20000, false);
	my_network.save("Sentince_test");
	vector<double> results = my_network.solve_model({0.00,0.09,0.04,0.03,0.08});
	print_vector(results);
	cout << "====================\n";
	results = my_network.solve_model({0.03,0.08,0.04,0.03,0.09});
	print_vector(results);
	cin.get();
	return 0;
}
*/


int main()
{
	vector<vector<vector<double>>> data = get_data();
	vector<vector<double>> x_data = data[0];
	vector<vector<double>> y_data =  data[1];
	int b = x_data[0].size();
	cout << b << endl;
	int a = y_data[0].size();
	cout << a << endl;
	model my_model(15, MSE, 0.02);
	my_model.add_hidden_layer(tanH, 15);
	my_model.add_hidden_layer(tanH, 225);
	my_model.add_hidden_layer(tanH, 128);
	my_model.add_hidden_layer(tanH, 64);
	my_model.train(x_data, y_data, 100, false);
	vector<double> results_of = my_model.solve_model({0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.09,0.05,0.08});
	for(int i=0;i<results_of.size();i++)
	{
		cout << results_of[i] << ",";
	}
	my_model.save("Complex_Sentince_Model");
	return 0;
}


/*

To Solve networks just use matrix multiplication

A*B= input for next neurons

A = weights
B = outputs of last neuron layer

*/