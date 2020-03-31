#ifndef __PROBABILITIES_DATASET__
#define __PROBABILITIES_DATASET__

#include <vector>
#include <string>

class ProbabilitiesDataset{

	public:

	// prob_class[c] = log(Pr[class = c])
	std::vector<int> prob_class;
	// prob_per_attri[c][i][j] = log(Pr[x_i = j | class = c])
	std::vector< std::vector< std::vector<int> > > prob_per_attri;

	int number_classes;
	int number_attributes;

	void read_probabilities_from_file(std::string filename, int c);
	
	ProbabilitiesDataset(std::vector< std::string> filenames);

	void print();
};
#endif
