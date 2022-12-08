//Written by William D. Shepelak
//P.S I am awesome btw
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "node.h"
using namespace std;


class hidden_layer
{
	public:
		hidden_layer(activator_type, int, int);
		void activator_info();
		vector<double> solve_layer(vector<double>);
		int get_layer_size();
		vector<double> back_prop_layer(vector<double>, double, bool);
		string save_layer();
		void load_layer(string &);
	private:
		string get_activation_type();
		vector<double> dE_dZ;
		int node_size;
		activator_type node_type;
		vector<node> layer;
};

hidden_layer::hidden_layer(activator_type type, int size, int prev_layer_size)
{
	srand(0);
	this->node_size = size;
	this->node_type = type;
	vector<node> proto_layer;
	vector<double> proto_weights;
	for(int i=0;i<prev_layer_size;i++)
	{
		double n=((double)rand()/(double)RAND_MAX)*2.0-1.0;
		proto_weights.push_back(n);
	}
	for(int i=0;i<size;i++)
	{
		double j=((double)rand()/(double)RAND_MAX)*2.0-1.0;
		node new_node =  node(type, j, proto_weights);
		proto_layer.push_back(new_node);
	}
	this->layer=proto_layer;
}

vector<double> hidden_layer::back_prop_layer(vector<double> er_vector, double ln, bool trace)
{	
	vector<double> dE_dZ;
	vector<vector<double>> incoming_dervs;
	for(int i=0;i<this->layer.size();i++)
	{
		incoming_dervs.insert(incoming_dervs.begin(), this->layer[i].back_prop_node(er_vector[i], ln, trace));
		
	}
	for(int i=0;i<incoming_dervs[0].size();i++)
	{
		double sum=0;
		for(int j=0;j<incoming_dervs.size();j++)
		{
			sum+=incoming_dervs[j][i];
		}
		dE_dZ.push_back(sum);
	}
	return dE_dZ;
}

void hidden_layer::activator_info()
{
	cout << "this layer has " << this->node_size << " nurons\n";
	cout << "This layers activation function is " << this->layer[0].get_activation_function() << endl;
}
	
vector<double> hidden_layer::solve_layer(vector<double> inputs)
{
	vector<double> outputs;
	for(int i=0;i<layer.size();i++)
	{
		outputs.push_back(layer[i].get_activation(inputs));
	}
	return outputs;
}

int hidden_layer::get_layer_size()
{
	return this->node_size;
}

string hidden_layer::get_activation_type()
{
	switch(this->node_type)
	{
		case ND: return "No activation"; break;
		case identity: return "identity"; break;
		case binary_step: return "binary step"; break;
		case sigmoid: return "sigmoid"; break;
		case tanH: return "tan hyperbolic"; break;
		case ReLU: return "ReLU"; break;
		case GELU: return "GELU"; break;
		case softplus: return "softplus"; break;
		case leakyReLU: return "leakyReLU"; break;
		case SiLU: return "SiLU"; break;
		case mish: return "mish"; break;
		case gaussian: return "gaussian"; break;
		case GCU: return "GCU"; break;
		case SQU: return "SQU"; break;
		case NCU: return "NCU"; break;
	}
}

string hidden_layer::save_layer()
{
	string str = "";
	str += "> ";
	str += get_activation_type();
	str += "\n";
	for(int i=0;i<this->node_size;i++)
	{
		str += this->layer[i].save_node();
		if(i!=this->node_size)
		{
			str += "\n";
		}
	}
	return str;

}

void hidden_layer::load_layer(string & str)
{
	activator_type load_type;
	str.erase(0,str.find(" "));
	
}