#ifndef __HOMOMORPHIC_NAIVE_BAYES_CLASSIFIER__
#define __HOMOMORPHIC_NAIVE_BAYES_CLASSIFIER__

#include <NTL/ZZ.h>
#include <NTL/vec_ZZ.h>
#include <NTL/mat_ZZ.h>

#include <vector>

#include "HENoisyX0.h"
#include "ProbabilitiesDataset.h"


class HomomorphicNaiveBayesClassifier {

	public:
	
	int number_attributes;
	int max_val_attr;
	int number_classes;

	// For each 0 <= c < number_classes, 
	// prob_per_class[c] is an encryption of the vector
	// (log(Pr[class = c]), 0, 0, ..., 0)
	std::vector<NTL::vec_ZZ> prob_per_class;

	
	// For each 0 <= c < number_classes and 0 <= i < number_attributes,
	// prob_per_class_att[c][i] is a decomposition of the vector encrypting the
	// logarithms of the probabilities related to attribute x_i and class c, i.e.,
	// G^-1((log(Pr[x_i=1 | class = c]), .., log(Pr[x_i=max_val_attr | class = c]))
	std::vector< std::vector< NTL::vec_ZZ> > prob_per_class_att;

	HENoisyX0* he;

	HomomorphicNaiveBayesClassifier(std::vector< NTL::vec_ZZ>& cs,
									ProbabilitiesDataset& probs,
									HENoisyX0* _he);

	
	// 	  Let y^(s) = (y^(s)_0, y^(s)_1, ..., y^(s)_(number_attributes-1)),
	// for 0 <= s < n, be the n elements to be classified.
	//    Each C[s] is an encryption of a matrix Y_s such that
	// Y_s[i-1][j] = 1 if, and only if, y^(j)_s = i.
	//  Assume that there are only two possible classes
	NTL::vec_ZZ classify_binary_class(std::vector< NTL::mat_ZZ>& C);

};
#endif
