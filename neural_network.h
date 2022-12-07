//Written by William D. Shepelak
//P.S I am awesome btw
#pragma once
#include "hidden_layer.h"
#include "node.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;

enum error_function
{
	NDF = 0,
	MSE = 1,
	MAE = 2,
	MBE = 3,
	CEL = 4,
};


class model
{
	public:
		model(int, error_function, double);
		void add_hidden_layer(activator_type, int);
		vector<double> solve_model(vector<double>);
		vector<double> get_error_vector(vector<double>);
		void back_prop(vector<double>, bool);
		vector<double> get_error_derv(vector<double>);
		void train(vector<vector<double>>, vector<vector<double>>, int, bool);
		void save(string);
		void load(string);
	private:
		vector<double> MSE_func(vector<double>);
		vector<double> MSE_derv(vector<double>);
		void print_vector_n(vector<double>);
		double lrn_rate;
		error_function er_func;
		vector<hidden_layer> network;
		vector<double> inputs;
		vector<double> outputs;
		int start_nodes;
};

model::model(int start, error_function error, double ln_rate)
{
	this->start_nodes = start;
	this->er_func = error;
	this->lrn_rate = ln_rate;
}

void model::train(vector<vector<double>> x, vector<vector<double>> y, int epochs, bool trace)
{
	vector<double> results;
	vector<double> errors;
	for(int j=0;j<epochs;j++)
	{
		cout << "Epoch " << j+1 << " of " << epochs << "\n";
		for(int i=0;i<x.size();i++)
		{
			results=solve_model(x[i]);
			errors = get_error_vector(y[i]);
			if(trace)
			{
				cout << "Inputs\n";
				print_vector_n(x[i]);
				cout << "Actual\n";
				print_vector_n(y[i]);
				cout << "Estimate\n";
				print_vector_n(results);
				cout << "Error\n";
				print_vector_n(errors);
				back_prop(y[i], true);
				cout << "==================\n";	
			}
			else
			{
				back_prop(y[i], false);
			}
		}
	}
	results=solve_model(x[0]);
	errors = get_error_vector(y[0]);
	cout << "Inputs\n";
	print_vector_n(x[0]);
	cout << "Actual\n";
	print_vector_n(y[0]);
	cout << "Estimate\n";
	print_vector_n(results);
	cout << "Error\n";
	print_vector_n(errors);
	cout << "==================\n";	
}

void model::back_prop(vector<double> y_exact, bool trace)
{
	vector<double> derv_values;
	
	for(int i=this->network.size()-1;i>=0;i--)
	{
		
		if(i==this->network.size()-1)
		{
			derv_values = get_error_derv(y_exact);
		}
		derv_values = this->network[i].back_prop_layer(derv_values, this->lrn_rate, trace);
	}
}

vector<double> model::get_error_vector(vector<double> y_exact)
{
	if(y_exact.size()!=this->network[this->network.size()-1].get_layer_size()){
		std::invalid_argument("wrong vector size!!");
		}
	else{
		switch(this->er_func)
		{
			case NDF:
				std::invalid_argument("ERROR no selected error function!!");
				return {};
				break;
			case MSE:
				return MSE_func(y_exact);
				break;
			/*
			case MAE:
				return MAE_func(y_exact);
				break;
			case MBE:
				return MBE_func(y_exact);
				break;
			case CEL:
				return CEL_func(y_exact);
				break;
			*/
		}
	}
}

vector<double> model::get_error_derv(vector<double> acts)
{
		switch(this->er_func)
		{
			case NDF:
				std::invalid_argument("ERROR no selected error function!!");
				return {};
				break;
			case MSE:
				return MSE_derv(acts);
				break;
			/*
			case MAE:
				return MAE_func(y_exact);
				break;
			case MBE:
				return MBE_func(y_exact);
				break;
			case CEL:
				return CEL_func(y_exact);
				break;
			*/
		}
}

vector<double> model::MSE_func(vector<double> y_exact)
{
	vector<double> results;
	for(int i=0;i<y_exact.size();i++)
	{
		double n = 0.5*((this->outputs[i]-y_exact[i])*(this->outputs[i]-y_exact[i]));
		results.push_back(n);
	}
	return results;
}

vector<double> model::MSE_derv(vector<double> acts)
{
	vector<double> results;
	for(int i=0;i<acts.size();i++)
	{
		results.push_back(-1.0*(acts[i]-this->outputs[i]));
	}
	return results;
}

void model::add_hidden_layer(activator_type type, int num)
{
	int size_priv;
	if(network.size()==0){size_priv=this->start_nodes;}
	else{size_priv=this->network[network.size()-1].get_layer_size();}
	hidden_layer layer = hidden_layer(type, num, size_priv);
	this->network.push_back(layer);
}


vector<double> model::solve_model(vector<double> inputs)
{
	if(inputs.size()!=this->start_nodes){throw std::invalid_argument("wrong vector size!!"); return {};}
	else{
	vector<double> current = this->network[0].solve_layer(inputs);
	for(int i=1;i<this->network.size();i++)
	{
		current = this->network[i].solve_layer(current);
	}
	this->outputs=current;
	return current;
	}
}

void model::print_vector_n(vector<double> nums)
{
	for(int i=0;i<nums.size();i++)
	{
		cout << nums[i] << "\n";
	}
}

void model::save(string fname)
{
	fname += ".txt";
	fstream _file (fname.c_str(), std::fstream::out | std::fstream::trunc);
	string data = "";
	switch(this->er_func)
	{
		case NDF:
			data += "0";
			break;
		case MSE:
			data += "1";
			break;
		case MAE:
			data += "2";
			break;
		case MBE:
			data += "3";
			break;
		case CEL:
			data += "4";
			break;
	}
	data += "\n";
	data += to_string(this->network.size());
	data += "\n";
	for(int i=0;i<this->network.size();i++)
	{
		data += this->network[i].save_layer();
		data += "\n";
	}
	_file << data;
	_file.close();

}

void model::load(string fname)
{
	fname += ".txt";
	fstream _file (fname.c_str(), std::fstream::in);
	string data = "";
	while(!_file.eof())
	{
		getline(_file, data);
		data += "\n";
	}
	_file.close();
	string error_val = data.substr(0, data.find("\n"));
	int data_error = stoi(error_val);
	data.erase(0,data.find("\n")+1);
	string layer_val = data.substr(0, data.find("\n"));
	int data_layer = stoi(layer_val);
	data.erase(0,data.find("\n")+1);
	for(int i=0;i<this->network.size();i++)
	{
		this->network[i].load_layer(data);
	}
}