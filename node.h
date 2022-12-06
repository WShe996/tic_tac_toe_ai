//Written by William D. Shepelak
//P.S I am awesome btw
//started december of 2021
//fist working multilayer network jan 11 2022  XOR model
#pragma once
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
using namespace std;

enum activator_type
{
	ND = 0,
	identity=1,
	binary_step=2,
	sigmoid=3,
	tanH=4,
	ReLU=5,
	GELU=6,
	softplus=7,
	leakyReLU=8,
	SiLU=9,
	mish=10,
	gaussian=11,
	GCU=12,
	SQU=13,
	NCU=14,
	Nineteen_Eighty_Seven=15,
};

//Don't look at this
string funny_egg = "@#@@@@@@@@@@@@@@@@@@@@@@@#+@;##+'++####@@@@@@@@+#'+'+##+'+';;;+@@@@@@@@@@@@@@@@@@@@@@@@@@@\n++####@@@@@@@@@@@@@@@@@@#+@+@##++#+###@#@@@##@@@@#####@+@#+''+@@@@@@@@@@@@@@@@@@@@@@@####\n++#+++###@@@@@@@@@@@@@@@@@@@@@##@###@@@#@@@@@@@###@##@#@@+@#@@@+@@@@@@@@@@@@@@@@@@###+####\n+++#'++++#@@@@@@@@@@@@@@#####@@@@@@@@@@@#@@#@#####################@@@@@@@@@@@@@@@##+#++#++\n+###++++++#@@@@@@@@@@@@#+#####++++++#+#+##+####+####################@@@@@@@@@@@@####+++###\n++##+++++++#@@@@@@@@@###+####+++++#++++++++#+++#++###################@@@@@@@@@@@###+######\n######+++++#@@@@@@@@###+####+#+++++++++++++++'+++++##############@####@@@@@@@@@###+####@##\n@@@@@@@@++++##@@@@@##++####+++++++'+++++''+++++#++######+##############@@@@@@@#++###@@@@@@\n#@#@###@@#+++#@@@@###++##++'##++'++'+++++'++'''++#+#####++##############@@@@@@#+##@@@####@\n#########@#+++@@@@@##++###++#+##++'''+##'+++'+'+++#+#+##+++#++###########@@@@#++#@@#######\n##########@+++@@@@###+++++++++++++'+++##++++'''''+++++++++++++++#########@@@@++#@@########\n###########@+#@@@####''++'''++##+++++#+#+++'''''+''+++++++++++++##########@@@#+#@#########\n###+#++####@++@@@###+''++'+'+++#++++###++++++''+''+++++++++'+'+++#+##+####@@@#+@@#########\n#++++++#####+#@@###+'##+++++++#++++++#+++++++'+'+''''+'+++++''+++++#+######@@##@@#########\n++++++++###++#@@####'++###++++++++++++++'+++++''''''++++++'+++++++++++#####@@@+#@#########\n#+++++++##@++@#@+#+#++++##+'''+'++++++++++++++'+++''++++++'++++++++++#++###@@@#+@#########\n#+++++++###++@@###+#+'++##++''+++++++++++++++++++''''++++++++++++++++++#####@@#+@@########\n##++++++#@'+@@@++++''++#+++++++++#++++++++++++++++++''+++++++++++++++'+#####@@@++@########\n++++++++##+#@;@+#++;''++++++++++###++++++++++++++++#++'+'++++++#+++++'+++###;#@#+@@#######\n#+#+++###++#@@#++++'''+++#++++++####+##++++++'++++++'++++'+++++++++++++#####@@@@+#@#######\n####++##@++@@@##+++'';'+++@@@@@@@@@#+++#+++#+++++'++++++#@@@@@@@@#+++++++####@@@#+@@######\n###+####++#@@@+++++;;'''@@@@@@@@@@@@@@@#+##+#####+++#@@@@@@@@@@@@@@@+++++####@@@#+#@######\n#######@'#@@@##+++'''''+@@@@@@@@@@@@@@@@@+++++#+++#@@@@@@@@@@@@@@@@@+''+++###@@@@++@@#####\n#@@@@@##+#@@@#+#++';'';'@@@@@@@@@@@@@@@@#+++++++++#@@@@@@@@@@@@@@@@@'+++++++##@@@#+#@@@@#@\n######+++@@@@++++#'''''+@@@@@@@@@@@@@@@#+'+++++++++#@@@@@@@@@@@@@@@++++'+++++#@@@@#++#####\n#++#++++#@@@#++++''''+'+@@@@@##+'+'+++++'++++++++++++++####+##@@@@@+++++++'+###@@@@#++####\n+++##++#@@@##++++;''+''+#@@#+++++++++++++++++#++++++++##+++++++#@@@+++++'++++###@@@####+++\n##+##@@@@@@###++'''''''++++++++++##+'+++++++##+++++++++####++++++++++++++'''+###@@@@@@####\n@@@@@@@@@@@####+'''''+++++++#@@@@@@@#++'+'++++++++++++@@@@@@@##+++++'+++++++++##@@@@@@@@@@\n@@@@@@@@@@@####''''''''++###@@@@#@@@@@@'++++++++++++#@@#@@@@@@@#++''+++++++'++##@@@@@@@@@@\n@@@@@@@@@@@####''';'''+'+##@@@@@@@@@@@@#+++++++++++#@@@@@@@@@@#@#+'++'++++++++##@@@@@@@@@@\n@@@@@@@@@@####'''';;''+++##@@@@@@@@@@@@@++++++++++#@@@@@@@@###@@@#+++++#++++++##@@@@@@@@@@\n@@@@@@@@@@###+';;'''''''+@@@@@@@;:,@@@@@#+++#+++++#@@:     :@@@#@@+++++++++#+++#@@@@@@@@@@\n@@@@@@@@@@###';;';++''++#@@#:.`.:,:'@@@@@+++++++++;,``,:,:   `@@@@++++#+++++'#+#@@@@@@@@@@\n@@@@@@@@@@##+';''''+++++#@@':.; ...,@@@@@###+++++#:,`; ...`   @@@@#++++#++++++##@@@@@@@@@@\n@@@@@@@@@@+#''''''+'++++@@@':.;:@@@,@@@@@##++++++#:,``'@@.    @@@@@+++##+++++####@@@@@@@@@\n@@@@@@@@@#+++''+'''+++++@@@#:,''@@@,@@@@@++#++#++#;,,'#@@;:   @@@@@#++#++++++####@@@@@@@@@\n@@@@@@@@@++'++'''';'''++@@@@:,++@@':+@@@@##+++##+#;,.++@@;;   @@@@@#+++++++++#####@@@@@@@@\n@@@@@@@#+++'+'+''''''''+#@@@;,.@@#+++@@@@##+++##+#::,'@##'    @@#@@#'+#+++++#+#+###@@@@@@@\n@@@@@@#+#+'';';'''';'''+#@@@+:,``,  @@@@@@@@@@@@@@@+,.`';     @@@@@#++++++++#+#+####@@@@@@\n@@@@@@+++''';';;';;;''+'+@@@@;:.`` `@@@@@@@@@@@@@@@@@@@`     @@@@@#++'#+#+##++++#####@@@@@\n@@@@@#+'+'';'';;'';;'''++#@@@@@#@@@@@@@@@@@@@@@@@@@@@@@@`  :@@@@@#++++++++++'+##+####@@@@@\n@@@@@+''+'''';;::;;;';''+++@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@##++''+++++++++#+#####@@@@\n@@@@#+'''+'+';;;;;;;;''+++#@@@#@@@@@#@@@@@@@@@@@@@@@@@@@@#@@@@@####+++++#+++++++++####@@@@\n@@@@#+''++'+'';';;'''++###+++##+##@@.@@@@@@@@@@@@@@@@@@'@@@#########++#++##++++++++###@@@@\n@@@@#+'''''++''';;''++##+++++++++##@@@@@@@@@@@@@@@@@@@@@@###+###########+#++++++#++####@@@\n@@@@#+'''''+'';';';'##+''++'+++++++#@+#@@@@@@@@@+'::+@@@####++#++###+####+#++#++##++###@@@\n@@@@#+''+'''';;';;#++';''++'+'+'++++#@@@@@@@@@@@#@@@@@@##++#+++'+'+++++##++#+++++#++###@@@\n@@@@##+'''';;;;;;#'';';''++'+'''''''''+@@@@@@@@@@@@@@###+++++++++++#+'++###++++##++++##@@@\n@@@@#+'''''';;'';+'';'';''''''''+''''';+++#@@@@@@#++#++#+++++++++++++++++#++++++#+++##@@@@\n@@@@##'''''';;;;#';;;;';''';'''''+';;''+'++++++++++++++++++++'+++++''+''++#++#+++#++##@@@@\n@@@@@#+++';''';'';;;;@#;'''';'';;';';;;''''''+#''''++++'+++++'+'+''''@''++++++++##+###@@@@\n@@@@@#'+++''';''';:;:@#;''@@';;;';;'';;;''''''#''''''''+''''++++@@'''@+'''+#++++##+###@@@@\n@@@@@##+++;:';'+';::;;;;;;;'';;';'';'''';'''''+'''''+''''';'+'++''''''''++'+++++#++##@@@@@\n@@@@@@##+;;;;'+';::;::::;;:';;''''''';''';'''''';'''''''''''''''''''''''#'''+#+##+###@@@@@\n@@@@@@##+'''''''::::;;':;::;''''''''''''''''''''''+''''';'''''''''''+'''''''###+####@@@@@@\n@@@@@@@##++'+'+':;';;:@@:;:;'''''''''''''''''''''''''''';;''''''''''@@'''''+#######@@@@@@@\n@@@@@@@@##+++++';';;;;''':;;;''''''''''';;''''''''''''''''''''''''''''''''''######@@@@@@@@\n@@@@@@@@@+#++##+'':';;;;;;';';''''+''''''''''''''+'''''''''''''''''''''''''+#####@@@@@@@@@\n@@@@@@@@@@#+#+##+';'''';';;';'''''''''''''''''''''''''''''''''''''+'+''''+'####@@@@@@@@@@@\n@@@@@@@@@@@#####+'''''+';';'''''''''''''''''+''+''+'''''''''''''+'+++++'''++###@@@@@@@@@@@\n@@@@@@@@@@@@####+++++'';'++'+'''++'+'''''''''+''++++'+'''''''+++++++++'''+###@@@@@@@@@@@@@\n@@@@@@@@@@@@@@+##++''+'''+++++'++++++++'''''++'+++'+'''''''++++++++'++++++#@#@@@@@@@@@@@@@\n@@@@@@@@@@@@@@+'#++++'+++''+'++++++++++++'''++''++++''+++'''++++++++++#++####@@@@@@@@@@@@@\n@@@@@@@@@@@@@@++#@++++++'++++++++++++++++++'+++++++++++'++++++++++++#+##+####@@@@@@@@@@@@@\n@@@@@@@@@@@@@@+++@@#++++++++++++++++++++++++++++++'++++++++++++#++#####@#####@@@@@@@@@@@@@\n@@@@@@@@@@@@@@+'#@@@###+###+++++#+#++++++++++++++++++++++++++###+######@#####@@@@@@@@@@@@@\n@@@@@@@@@@@@@@+'+#@@@@##@########++++++++++++++++++++++############@#@@#@##++@@@@@@@@@@@@@\n@@@@@@@@@@@@@@++##@@@@@@@@+#@@@@###############+#+########@@##@+'###@##@##+#+@@@@@@@@@@@@@\n@@@@@@@@@@@@@@+++##@@@@@@@'#@@@@@@@@@@@@@@@@@@@@@@@@@@@#:`@@@#@#'@@@@@@@##++#@@@@@@@@@@@@@\n@@@@@@@@@@@@@@+#+###@@@@@@'#@++'+'+'@@@@@@@@@@@@#+'';##'+#''''@''+@@@@@#####+@@@@@@@@@@@@@\n@@@@@@@@@@@@@@++#+####@@@@:@@,:;;;;;##+'''#''';:'''''+@';;;;;:@;;+@@@@########@@@@@@@@@@@@\n@@@@@@@@@@@@@@##++++++##@@;@@.:::::,;':;;;;;@@'@;::;;;:;,::::,@:,'@@##########@@@@@@@@@@@@\n@@@@@@@@@@@@@@+#++'''+######@.:::,,,@+::::,,@@@@::,:,:@#,,,,,.@@@######++#####@@@@@@@@@@@@\n@@@@@@@@@@@@@@+'+''++'''+########;.`@',,,.,.@@@@;,,,..@@,:'@@@##########++++#@@@@@@@@@@@@@\n@@@@@@@##@@@@@++'+++;'''++++###########@@#@#####@#@@@##@########+#+++++++##+#@@@@@@@@@@@@@\n@@@#########@@#++'++'';'++++++###############+#@##@#@##+##++#+++++++'+++++#+###########@@@\n@#+##########@+++''+''++'++++'++++++###+###++########+++##+++++++++++++##+#+##############\n###++######@@@#++''++''''+#'+#+++###+'+++#++++#++++++++#++'++++++++++++##+################\n+++#####+##@@@@#+''++'''+'+#+++#++++++++++++++#++++++++++#++'++++++++###+#################\n+++#########@@@#+'++++++''+'#++++'++++++'+++++#++++++++'+++++++#+++#+#######@#############\n+#++####@#@#@@@@#++'+++''+'+'+'++'++++++'+++++++''+++++++++++++###+##+#####@@########+####\n+++++#+####@@@@@@#++#+++#++++++++''+++++++++++++'''+++++++++++###++########@@########++##+\n;#++#+#####@@@@@@@##+++++++++++++++++++++++##+++'+'+++++++++##+###########@@@@#########++#\n++'+++#####@@@@@@@@#+##+#+++#++#+++++++++#+##+++++++++++++#+#############@@@@@#######+++++\n'''++#++##@@@@@@@@@@###+#+###+##+++++++++++###++++++#++++################@@@@@######++++''\n;''+++++###@@@@@@@@@#############+###+++#+###++++##+++++#################@@@@@#####++++++'\n;''++++#####@@@@@@@###.############++++#######+++++#+#####################@+@@@#+#++'+++'+\n+;''+'+####@@@@@@@####+@+###########+##########+++############@@###@###+##@@@@@###++++++''\n@#'''+++###@@@@@@+###++.#@@###########++################@#@##@@@@@'@######\n\nHey Gregory! It's me Freddy, I have gotten into your code!!\nNice neural network, Superstar!\n";
//Don't look at this

/*

i1--|
    w1--|
i2--w2-||
      ---- a1 + b1 = z1
i3--w3-||
    w4--|
i4--|

*/

class node
{
	public:
		node(activator_type, double, vector<double>);
		string get_activation_function();
		void get_bias();
		double get_activation(vector<double>);
		double get_activation_derv(double);
		int get_weight_size();
		void set_weights(vector<double>);
		void set_bias(double);
		vector<double> back_prop_node(double, double, bool);
		string save_node();
	private:
		double NCU_func(vector<double>);
		double NCU_derv(double);
		double SQU_func(vector<double>);
		double SQU_derv(double);
		double GCU_func(vector<double>);
		double GCU_derv(double);
		double gaussian_func(vector<double>);
		double gaussian_derv(double);
		double mish_func(vector<double>);
		double mish_derv(double);
		double SiLU_func(vector<double>);
		double SiLU_derv(double);
		double leakyReLU_func(vector<double>);
		double leakyReLU_derv(double);
		double softplus_func(vector<double>);
		double softplus_derv(double);
		double GELU_func(vector<double>);
		double GELU_derv(double);
		double ReLU_func(vector<double>);
		double ReLU_derv(double);
		double tanH_func(vector<double>);
		double tanH_derv(double);
		double sigmoid_func(vector<double>);
		double sigmoid_derv(double);
		double binary_step_func(vector<double>);
		double binary_step_derv(double num);
		double identity_func(vector<double>);
		double identity_derv(double num);
		void print_vector(vector<double>);
		vector<double> z_derivative;
		vector<double> old_weights;
		vector<double> weights;
		vector<double> inputs;
		double bias;
		double z;
		double a;
		activator_type type;
};



node::node(activator_type type, double bias, vector<double> weights)
{
	this->bias=bias;
	this->weights=weights;
	this->type = type;
	if(type==Nineteen_Eighty_Seven)
	{
		cout << funny_egg;
		exit(0);
	}
}

void node::print_vector(vector<double> nums)
{
	for(int i=0;i<nums.size();i++)
	{
		cout << nums[i] << "\n";
	}
}

vector<double> node::back_prop_node(double num, double ln, bool trace)
{
	if(trace)
	{
		cout << "**Weights\n";
		print_vector(this->weights);
		cout << "**Bias\n";
		cout << this->bias << "\n";
	}
	double dC_dA = num;
	double dA_dZ = get_activation_derv(this->a);
	vector<double> weight_dervs;
	vector<double> next_dervs;
	for(int i=0;i<this->inputs.size();i++)
	{
		double num1 = dC_dA*dA_dZ*this->inputs[i];
		weight_dervs.push_back(num1);
	}
	this->old_weights=this->weights;
	for(int i=0;i<this->weights.size();i++)
	{
		double newnum = this->weights[i] - ln*weight_dervs[i];
		if(trace)
		{
			cout << "**Weight Change\n" << ln*weight_dervs[i] << "\n"; //info output
		}
		weight_dervs[i]=newnum;
	}
	set_weights(weight_dervs);
	if(trace)
	{
		cout << "**Bais Change\n" << ln*dC_dA*dA_dZ << "\n"; //info output
	}
	set_bias(this->bias-ln*dC_dA*dA_dZ);
	for(int i=0;i<this->old_weights.size();i++)
	{
		next_dervs.push_back(dC_dA*dA_dZ*this->old_weights[i]);
	}
	return next_dervs;
}

void node::get_bias()
{
	cout << this->bias << endl;
}

int node::get_weight_size()
{
	return this->weights.size();
}

void node::set_weights(vector<double> nums)
{
	if(nums.size()!=this->weights.size())
	{
		throw std::invalid_argument("vectors do not match!!");
	}
	else{for(int i=0;i<nums.size();i++){this->weights[i]=nums[i];}}
}

void node::set_bias(double num)
{
	this->bias=num;
}

double node::get_activation(vector<double> nums)
{
	this->inputs = nums;
	switch(this->type)
	{
		case ND:
			std::invalid_argument("ERROR no selected activation function");
			return(0.0);
			break;
		case identity:
			return identity_func(nums);
			break;
		case binary_step:
			return binary_step_func(nums);
			break;
		case sigmoid:
			return sigmoid_func(nums);
			break;
		case tanH:
			return tanH_func(nums);
			break;
		case ReLU:
			return ReLU_func(nums);
			break;
		case GELU:
			return GELU_func(nums);
			break;
		case softplus:
			return softplus_func(nums);
			break;
		case leakyReLU:
			return leakyReLU_func(nums);
			break;
		case SiLU:
			return SiLU_func(nums);
			break;
		case mish:
			return mish_func(nums);
			break;
		case gaussian:
			return gaussian_func(nums);
			break;
		case GCU:
			return GCU_func(nums);
			break;
		case SQU:
			return SQU_func(nums);
			break;
		case NCU:
			return NCU_func(nums);
			break;
		case Nineteen_Eighty_Seven:
			cout << funny_egg;
			return 1987.0;
			break;
	}
}

double node::get_activation_derv(double num)
{
	switch(this->type)
	{
		case ND:
			std::invalid_argument("ERROR no selected activation function");
			return(0.0);
			break;
		case identity:
			return identity_derv(num);
			break;
		case binary_step:
			return binary_step_derv(num);
			break;
		case sigmoid:
			return sigmoid_derv(num);
			break;
		case tanH:
			return tanH_derv(num);
			break;
		case ReLU:
			return ReLU_derv(num);
			break;
		case GELU:
			return GELU_derv(num);
			break;
		case softplus:
			return softplus_derv(num);
			break;
		case leakyReLU:
			return leakyReLU_derv(num);
			break;
		case SiLU:
			return SiLU_derv(num);
			break;
		case mish:
			return mish_derv(num);
			break;
		case gaussian:
			return gaussian_derv(num);
			break;
		case GCU:
			return GCU_derv(num);
			break;
		case SQU:
			return SQU_derv(num);
			break;
		case NCU:
			return NCU_derv(num);
			break;
		case Nineteen_Eighty_Seven:
			cout << funny_egg;
			return 1987.0;
			break;
	}
}

double node::NCU_func(vector<double> nums)
{
	double sum;
	for(int i=0;i<nums.size();i++)
	{
		double num = nums[i];
		double w = this->weights[i];
		num = num*w;
		
		sum+=num;
	}
	sum+=this->bias;
	this->z=sum;
	sum=sum-sum*sum*sum;
	this->a=sum;
	return sum;
}

double node::NCU_derv(double num)
{
	return 1.0-3.0*num*num*num;
}

double node::SQU_func(vector<double> nums)
{
	double sum;
	for(int i=0;i<nums.size();i++)
	{
		double num = nums[i];
		double w = this->weights[i];
		num = num*w;
		
		sum+=num;
	}
	sum+=this->bias;
	this->z=sum;
	sum=sum*sum+sum;
	this->a=sum;
	return sum;
}

double node::SQU_derv(double num)
{
	return 2.0*num+1.0;
}

double node::GCU_func(vector<double> nums)
{
	double sum;
	for(int i=0;i<nums.size();i++)
	{
		double num = nums[i];
		double w = this->weights[i];
		num = num*w;
		
		sum+=num;
	}
	sum+=this->bias;
	this->z=sum;
	sum=sum*cos(sum);
	this->a=sum;
	return sum;
}

double node::GCU_derv(double num)
{
	return cos(num)-num*sin(num);
}

double node::gaussian_func(vector<double> nums)
{
	double sum;
	for(int i=0;i<nums.size();i++)
	{
		double num = nums[i];
		double w = this->weights[i];
		num = num*w;
		
		sum+=num;
	}
	sum+=this->bias;
	this->z=sum;
	sum=exp(-1.0*pow(sum,2.0));
	this->a=sum;
	return sum;
}

double node::gaussian_derv(double num)
{
	return -2.0*num*exp(-1.0*pow(num,2.0));
}

double node::mish_func(vector<double> nums)
{
	double sum;
	for(int i=0;i<nums.size();i++)
	{
		double num = nums[i];
		double w = this->weights[i];
		num = num*w;
		
		sum+=num;
	}
	sum+=this->bias;
	this->z=sum;
	sum=sum*tanh(log(1.0+exp(sum)));
	this->a=sum;
	return sum;
}

double node::mish_derv(double num)
{
	double numer = exp(num)*(4.0*exp(2.0*num)+exp(3.0*num)+4.0*(1.0+num)+exp(num)*(6.0+4.0*num));
	double bottom = (2.0+2.0*exp(num)+exp(2.0*num))*(2.0+2.0*exp(num)+exp(2.0*num));
	return numer/bottom;
}

double node::SiLU_func(vector<double> nums)
{
	double sum;
	for(int i=0;i<nums.size();i++)
	{
		double num = nums[i];
		double w = this->weights[i];
		num = num*w;
		
		sum+=num;
	}
	sum+=this->bias;
	this->z=sum;
	sum=sum/(1.0+exp(-1.0*sum));
	this->a=sum;
	return sum;
}

double node::SiLU_derv(double num)
{
	return (1.0+exp(-1.0*num)+num*exp(-1.0*num))/((1.0+exp(-1.0*num))*(1.0+exp(-1.0*num)));
}

double node::leakyReLU_func(vector<double> nums)
{
	double sum;
	for(int i=0;i<nums.size();i++)
	{
		double num = nums[i];
		double w = this->weights[i];
		num = num*w;
		
		sum+=num;
	}
	sum+=this->bias;
	this->z=sum;
	if(sum >= 0){sum=sum;}
	else{sum=sum*0.01;}
	this->a=sum;
	return sum;
}

double node::leakyReLU_derv(double num)
{
	if(num>=0.0){return 1.0;}
	else{return 0.01;}
}

double node::softplus_func(vector<double> nums)
{
	double sum;
	for(int i=0;i<nums.size();i++)
	{
		double num = nums[i];
		double w = this->weights[i];
		num = num*w;
		sum+=num;
	}
	sum+=this->bias;
	this->z=sum;
	sum=log (1 + exp(sum));
	this->a=sum;
	return sum;
}

double node::softplus_derv(double num)
{
	return 1.0/(1.0+exp(-1.0*num));
}

double node::GELU_func(vector<double> nums)
{
	double sum;
	for(int i=0;i<nums.size();i++)
	{
		double num = nums[i];
		double w = this->weights[i];
		num = num*w;		
		sum+=num;
	}
	sum+=this->bias;
	this->z=sum;
	sum = 0.5*sum*(1+erf(sum/sqrt(2.0)));
	this->a=sum;
	return sum;
}

double node::GELU_derv(double num)
{
	throw std::invalid_argument("I have no idea what this is!");
	return 0.0;
}

double node::ReLU_func(vector<double> nums)
{
	double sum;
	for(int i=0;i<nums.size();i++)
	{
		double num = nums[i];
		double w = this->weights[i];
		num = num*w;
		sum+=num;
	}
	sum+=this->bias;
	this->z=sum;
	if(sum<=0){sum=0;}
	else{sum=sum;}
	this->a=sum;
	return sum;
}

double node::ReLU_derv(double num)
{
	if(num < 0.0){return 0.0;}
	else if(num > 0.0){return 1.0;}
	else{
		throw std::invalid_argument("recived 0 value for ReLU derv!");
	}
}

double node::tanH_func(vector<double> nums)
{
	double sum;
	for(int i=0;i<nums.size();i++)
	{
		double num = nums[i];
		double w = this->weights[i];
		num = num*w;
		sum+=num;
	}
	sum+=this->bias;
	this->z=sum;
	sum = (exp(sum)-exp(-1.0*sum))/(exp(sum)+exp(-1.0*sum));
	this->a=sum;
	return sum;
}

double node::tanH_derv(double num)
{
	return 1-(exp(num)-exp(-1.0*num))/(exp(num)+exp(-1.0*num))*(exp(num)-exp(-1.0*num))/(exp(num)+exp(-1.0*num));
}

double node::sigmoid_func(vector<double> nums)
{
	double sum;
	for(int i=0;i<nums.size();i++)
	{
		double num = nums[i];
		double w = this->weights[i];
		num = num*w;
		sum+=num;
	}
	sum+=this->bias;
	this->z=sum;
	sum = 1.0/(1.0+exp(-1.0*sum));
	this->a=sum;
	return sum;
}

double node::sigmoid_derv(double num)
{
	return (1.0/(1.0+exp(-1.0*num)))*(1.0-(1.0/(1.0+exp(-1.0*num))));
}

double node::binary_step_func(vector<double> nums)
{
	double sum;
	for(int i=0;i<nums.size();i++)
	{
		double num = nums[i];
		double w = this->weights[i];
		num = num*w;
		sum+=num;
	}
	sum+=this->bias;
	this->z=sum;
	if(sum>=0){sum=1;}
	else{sum=0;}
	this->a=sum;
	return sum;
}

double node::binary_step_derv(double num)
{
	if(num!=0.0)
	{
		return 0.0;
	}
	else
	{
		throw std::invalid_argument("recived 0 value for binary step derv!");
	}
}

double node::identity_func(vector<double> nums)
{
	double sum;
	for(int i=0;i<nums.size();i++)
	{
		double num = nums[i];
		double w = this->weights[i];
		num = num*w;
		
		sum+=num;
	}
	sum+=this->bias;
	this->z=sum;
	this->a=sum;
	return sum;
}

double node::identity_derv(double num)
{
	return 1.0;
}

string node::get_activation_function() //this works
{
	switch(this->type)
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
		case Nineteen_Eighty_Seven: return funny_egg; break;
	}	
}

string node::save_node()
{
	string str="";
	str+= ":{";
	for(int i=0;i<this->weights.size();i++)
	{
		str+=to_string(this->weights[i]);
		if(i!=this->weights.size()-1)
		{
			str+= ",";
		}
	}
	str += "}";
	str += to_string(this->bias);
	return str;
}

