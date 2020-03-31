#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <NTL/mat_ZZ_p.h>
#include <NTL/mat_ZZ.h>

using namespace std;
using namespace NTL;

class ProbabilitiesDataset{

public:

	// prob_class[c] = log(Pr[class = c])
	vector<int> prob_class;
	// prob_per_attri[c][i][j] = log(Pr[x_i = j | class = c])
	vector<vector<vector<int> > > prob_per_attri;

	void read_probabilities_from_file(string filename, int c){

		ifstream infile(filename);

		string line;
		getline(infile, line); // must be log(Pr[class == c])
		this->prob_class[c] = stoi(line);
		while (std::getline(infile, line))
		{
			vector<int> logs_line;
			istringstream reader(line);
			int log_prob;
			while (reader >> log_prob){
				logs_line.push_back(log_prob);
			}
			this->prob_per_attri[c].push_back(logs_line);
		}
	}
	
	ProbabilitiesDataset(vector<string> filenames)
	: prob_class(filenames.size()), prob_per_attri(filenames.size()) {
	
		for (int i = 0; i < filenames.size(); i++){
			read_probabilities_from_file(filenames[i], i);
		}
	}

	void print(){
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
};

// Each column of A will correspond to an attribute.
// A[i-1][j] = 1 if, and only if, attributes[j] = i
// Assume that A already has the correct dimensions (i.e., # attributes x max_value)
void attribute_vector_to_matrix(const vector<int>& attributes,
								mat_ZZ& A, 
								int max_value = 10){

	int i, j;
	for (j = 0; j < attributes.size(); j++){
		for (i = 0; i < max_value; i++){
			A[i][j] = 0;
		}
		i = attributes[j];
		A[i-1][j] = 1;
	}
}

void read_and_classify_test_set(string filename, ProbabilitiesDataset probs,
		unordered_map<string, int> class_labels, int max_atr_val = 10){
		
	mat_ZZ A;
	A.SetDims(max_atr_val, max_atr_val);
	ifstream infile(filename);
	string line;
	while (std::getline(infile, line)){
		vector<int> attributes;
		istringstream reader(line);
		string tmp;
		// reads the class
		reader >> tmp;
		int expected_class = class_labels[tmp];
		cout << "class: " << expected_class << endl;

		int atr_tmp;
		// read the attributes
		while(reader >> atr_tmp){
			attributes.push_back(atr_tmp);
			cout << attributes[attributes.size()-1] << ", ";
		}
		cout << endl;
		attribute_vector_to_matrix(attributes, A, max_atr_val);
	}
}


int main(){
	vector<string> filenames(2);
	filenames[0] = "breast-cancer/breast-cancer-wisconsin.data.train.benign.scaled_log_prob";
	filenames[1] = "breast-cancer/breast-cancer-wisconsin.data.train.malignant.scaled_log_prob";
	ProbabilitiesDataset a(filenames);
	a.print();

	unordered_map<string, int> class_labels;
	class_labels["b"] = 0; // class benign is represented by b and by 0
	class_labels["m"] = 1; // class malignant is represented by m and my 1
	read_and_classify_test_set("breast-cancer/breast-cancer-wisconsin.data.test"
							 , a, class_labels); 
	return 0;
}

