// To compile this file, use
//          g++ <filename>.cpp -o <output_name> -g -O2 -std=c++11 -pthread -march=native -lntl -lgmp -lm
#include <iostream>
#include <fstream>
#include <sstream>

#include "ProbabilitiesDataset.h"

using namespace std;


void ProbabilitiesDataset::read_probabilities_from_file(string filename, int c){

	ifstream infile(filename);

	string line;
	getline(infile, line); // must be log(Pr[class == c])
	this->prob_class[c] = stoi(line);

	number_attributes = 0;

	while (std::getline(infile, line))
	{
		vector<int> logs_line;
		istringstream reader(line);
		int log_prob;
		while (reader >> log_prob){
			logs_line.push_back(log_prob);
		}
		this->prob_per_attri[c].push_back(logs_line);
		number_attributes++;
	}
}

ProbabilitiesDataset::ProbabilitiesDataset(vector<string> filenames)
: prob_class(filenames.size()), prob_per_attri(filenames.size()), 
  number_classes(filenames.size()){

	for (int i = 0; i < filenames.size(); i++){
		read_probabilities_from_file(filenames[i], i);
	}
}

void ProbabilitiesDataset::print(){
	for (int c = 0; c < prob_class.size(); c++){
		cout << "log(P(class = " << c << ")) = " << prob_class[c] << endl;
		for (int i = 0; i < prob_per_attri[c].size(); i++){
			for (int j = 0; j < prob_per_attri[c][i].size(); j++){
				cout << "log(P(x_" << i << " = " << j << " | class = "
					 << c << ")) = " << prob_per_attri[c][i][j] << endl;
			}
		}
	}
}
