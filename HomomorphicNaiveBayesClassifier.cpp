#include "HomomorphicNaiveBayesClassifier.h"
#include "utils.h"

using namespace std;
using namespace NTL;


HomomorphicNaiveBayesClassifier::HomomorphicNaiveBayesClassifier(vector<vec_ZZ>& cs,
									ProbabilitiesDataset& probs,
									HENoisyX0* _he)
	: number_attributes(probs.number_attributes),
	  max_val_attr(cs.size()), number_classes(probs.number_classes),
	  prob_per_class_att(probs.number_classes),
	  prob_per_class(probs.number_classes), he(_he) {

	vec_ZZ tmp;
	tmp.SetLength(max_val_attr);

	for (int c = 0; c < number_classes; c++){
		vector<vec_ZZ> prob_per_attrib(number_attributes);
		for (int i = 0; i < number_attributes; i++){
			prob_per_attrib[i].SetLength(max_val_attr * he->l);
			tmp = probs.prob_per_attri[c][i][0] * cs[0];
			for (int j = 1; j < max_val_attr; j++){
				tmp += probs.prob_per_attri[c][i][j] * cs[j];
			}
			reduce_vec_mod(tmp, he->x0);
			invG(prob_per_attrib[i], tmp, he->l, he->baseG); // compute G^-1
		}
		prob_per_class_att[c] = prob_per_attrib;
	}

	for (int c = 0; c < number_classes; c++){
		// Enc( (1, 0, 0, ..., 0) * Pr[class = c] )
		prob_per_class[c] = cs[0] * probs.prob_class[c];
		for (int j = 1; j < number_attributes; j++)
			prob_per_class[c] += cs[j] * probs.prob_class[c];
		reduce_vec_mod(prob_per_class[c], he->x0);
	}
}


// 	  Let y^(s) = (y^(s)_0, y^(s)_1, ..., y^(s)_(number_attributes-1)),
// for 0 <= s < n, be the n elements to be classified.
//    Each C[s] is an encryption of a matrix Y_s such that
// Y_s[i-1][j] = 1 if, and only if, y^(j)_s = i.
//  Assume that there are only two possible classes
vec_ZZ HomomorphicNaiveBayesClassifier::classify_binary_class(vector<mat_ZZ>& C) {
	long n = he->n;
	long l = he->l;
	vec_ZZ digits_v;
	digits_v.SetLength(n * l);
	vec_ZZ v_tmp;
	v_tmp.SetLength(n);
	vec_ZZ v0(prob_per_class[0]);
	vec_ZZ v1(prob_per_class[1]);

	for (int s = 0; s < number_attributes; s++){
//		he->reconstruct_matrix_and_multiply(v_tmp, prob_per_class_att[0][s], C[s]);
		v_tmp = prob_per_class_att[0][s] * C[s];
		v0 += v_tmp;
	}

	for (int s = 0; s < number_attributes; s++){
		v_tmp = prob_per_class_att[1][s] * C[s];
		v1 += v_tmp;
	}

	return v0 - v1;
}

