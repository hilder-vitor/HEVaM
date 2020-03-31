#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>

#include <random>

#include "AutomatonLn.h"
#include "EncryptedAutomatonLn.h"
#include "HENoisyX0.h"
#include "ProbabilitiesDataset.h"
#include "HomomorphicNaiveBayesClassifier.h"
#include "utils.h"
#include "PreComputedParams.hpp"

using namespace std;
using namespace NTL;

using namespace std::chrono; // to measure execution times


std::map<long , PreComputedParams> select_params(long lambda){
	std::map<long , PreComputedParams> map_params;
	if (80 == lambda)
		map_params = params_80_noisy_x0; // defined in PreComputedParams.hpp
	else
		map_params = params_100_noisy_x0; // defined in PreComputedParams.hpp
	return map_params;
}


void read_and_classify_test_set(string filename, ProbabilitiesDataset& probs,
		unordered_map<string, int>& class_labels, int lambda, 
		int max_atr_val = 10){

	high_resolution_clock::time_point t_before;
    high_resolution_clock::time_point t_after;
	double avg_client_query_time = 0;
	double avg_classification_time = 0;
	double t_duration;
	double t_setup;
	int number_attributes = probs.number_attributes;
	long n = max_atr_val;
	long B = 1 << 19;

	std::map<long , PreComputedParams> map_params = select_params(lambda);
	PreComputedParams params(map_params.at(n));

	//--- SETUP client --//
	cout << "Client setup..." << endl;
	t_before = high_resolution_clock::now();

	cout << "HENoisyX0 he = new HENoisyX0" << endl;
	HENoisyX0* he = new HENoisyX0(lambda, n, params.eta, params.rho, params.rho_0,
             				params.gamma, params.log_baseG, B);

	// Encrypt the n vectors that are used by the server
	vector<vec_ZZ> cs(max_atr_val);
	
	vec_ZZ m;
	m.SetLength(max_atr_val);

	for (int i = 0; i < max_atr_val; i++){
		m[i] = 1;
		cs[i].SetLength(n);
		he->enc_vec(cs[i], m);
		m[i] = 0;
	}
	t_after = high_resolution_clock::now();
	t_setup = duration_cast<milliseconds>(t_after - t_before).count();
	cout<< t_setup<< " milliseconds for the client to finish the setup."<< endl;
	//---- END SETUP Client ---//

	mat_ZZ A;
	A.SetDims(max_atr_val, max_atr_val);
	ifstream infile(filename);
	string line;
	
	// -- SETUP server
	t_before = high_resolution_clock::now();

	HomomorphicNaiveBayesClassifier naive_bayes(cs, probs, he);

	t_after = high_resolution_clock::now();
	t_setup = duration_cast<milliseconds>(t_after - t_before).count();
	cout<< t_setup<< " milliseconds for the server to finish the setup."<< endl;

	// -- END SETUP server

	// ---- CLASSIFICATION ---//
	vector<mat_ZZ> C(number_attributes);
	vector<mat_ZZ> Y(number_attributes);
	vector<int> expect_classes(number_attributes);
	for (int i = 0; i < number_attributes; i++){
		Y[i].SetDims(n, n);
		C[i].SetDims(n * he->l, n);
	}

	int atr_tmp;
	string tmp;
	vec_ZZ vec_assigned_class, enc_vec_assigned_class;
	vec_assigned_class.SetLength(max_atr_val);
	enc_vec_assigned_class.SetLength(max_atr_val);
	int assigned_class, wrong = 0, correct = 0;
	int total_instances_classified = 0;
	int total_encrypted_matrices = 0;
	int total_vectors_downloaded = 0;


	while(infile.peek() != EOF){ // while not in the end of the file
		for (int s = 0; s < number_attributes; s++)
			clear(Y[s]); // set Y_s = the zero matrix

		// read n lines
		int j;
		for (j = 0; j < n && std::getline(infile, line); j++){
			cout << "line = " << line << endl;
			istringstream reader(line);
			// reads the class
			reader >> tmp;
			expect_classes[j] = class_labels[tmp];

			for (int s = 0; s < number_attributes; s++){
				reader >> atr_tmp;
				Y[s][atr_tmp-1][j] = 1;
			}
		}

		int number_instances_to_classify = j;
	
		// CLIENT encrypts
		cout << "Client encrypting..." << endl;
		t_before = high_resolution_clock::now();
		for (int s = 0; s < number_attributes; s++){
			he->enc_mat(C[s], Y[s]);
			total_encrypted_matrices++;
		}
		t_after = high_resolution_clock::now();
		t_duration = duration_cast<milliseconds>(t_after - t_before).count();
		cout << t_duration << " milliseconds to encrypt " << number_instances_to_classify
			 << " " << n << "x" << n << " matrices" << endl;
		avg_client_query_time += t_duration;

		// SERVER classifies
		cout << "Server classifying..." << endl;
		t_before = high_resolution_clock::now();
		enc_vec_assigned_class = naive_bayes.classify_binary_class(C);
		t_after = high_resolution_clock::now();

		t_duration = duration_cast<milliseconds>(t_after - t_before).count();
		cout << t_duration << " milliseconds to classify " <<
			    number_instances_to_classify << " instances." << endl;
		avg_classification_time += t_duration;

		// CLIENT decrypts the assigned class
		total_vectors_downloaded++;
		he->dec(vec_assigned_class, enc_vec_assigned_class);
		ZZ noise(he->get_noise(enc_vec_assigned_class, vec_assigned_class));
		cout << "   noise of enc(assigned class): " << noise << endl;
		for (j = 0; j < number_instances_to_classify; j++){
			// j-th position stores
			// log(Pr[class(y^(j)) = 0]) - log(Pr[class(y^(j)) = 1])
			if (vec_assigned_class[j] > 0)
				assigned_class = 0;
			else
				assigned_class = 1;
		
			if (expect_classes[j] == assigned_class){
				correct += 1;
				cout << "expected class == assigned class = " << assigned_class
					 << " ....  OK" << endl;
			}else{
				wrong += 1;
				cout << "expected class = " << expect_classes[j]
					 << ", assigned class = " << assigned_class
					 << " ....  ERROR" << endl;
			}
		}
		total_instances_classified += number_instances_to_classify;
	}
	cout << endl;
	cout << "Accuracy (correctly classified / total): "
		 << (float(correct) / (correct + wrong))
		 << endl;

	avg_classification_time /= total_instances_classified;
	avg_client_query_time /= total_instances_classified;
	cout << "AVG time for the client per instance: "
		 << avg_client_query_time << " milliseconds." << endl; 
	cout << "AVG time for the server to classify each instance: "
		 << avg_classification_time << " milliseconds." << endl;
	cout << total_instances_classified << " instances classified." << endl;

	double mb_size_per_matrix = (n * n * he->l * (he->eta - he->rho)) / (8.0 * 1000000);
	double mb_size_up = total_encrypted_matrices * mb_size_per_matrix;
	double mb_size_per_instance = mb_size_up / total_instances_classified;
	cout << "Client's upload per instance: " 
		 << mb_size_per_instance << " MB" << endl;

	double kb_size_per_vector = (n * he->gamma) / (8.0 * 1000);
	double kb_size_down = total_vectors_downloaded * kb_size_per_vector;
	double kb_size_per_instance = kb_size_down / total_instances_classified;
	cout << "Client's download per instance: " 
		 << kb_size_per_instance << " KB" << endl;
	delete he;
}


int test_naive_bayes_classifier(int lambda){
	int max_atr_val = 10; // each attribute is in the interval [[1, 10]]
	vector<string> filenames(2);
	filenames[0] = "breast-cancer/breast-cancer-wisconsin.data.train.benign.scaled_log_prob";
	filenames[1] = "breast-cancer/breast-cancer-wisconsin.data.train.malignant.scaled_log_prob";
	ProbabilitiesDataset log_probs(filenames);

	unordered_map<string, int> class_labels;
	class_labels["b"] = 0; // class benign is represented by b and by 0
	class_labels["m"] = 1; // class malignant is represented by m and my 1
	read_and_classify_test_set("breast-cancer/breast-cancer-wisconsin.data.test"
							 , log_probs, class_labels, lambda, max_atr_val);

	return 0;
}

/****************************************************************************
 *	END Naive Bayes Classifier
 ****************************************************************************/




bool test_encryption_decryption_vec(long lambda){

	high_resolution_clock::time_point t_before;
    high_resolution_clock::time_point t_after;
	long B = 3; // to encrypt vectors with entries in [[-B, B]]

	std::map<long , PreComputedParams> map_params = select_params(lambda);

	cout << "test_encryption_decryption_vec ... " << endl;
	for (const auto& kv : map_params) {
   		long n = kv.first;
		PreComputedParams params = kv.second;

		cout << "test_encryption_decryption_vec (n = "<<n<<") ... " << endl;
		cout << "HE he = new HENoisyX0(lambda);" << endl;
		HENoisyX0* he = new HENoisyX0(lambda, n, params.eta, params.rho, params.rho_0,
             				params.gamma, params.log_baseG, B);
		
		vec_ZZ v;
		v.SetLength(n);
		vec_ZZ cv;
		cv.SetLength(n);

		double avg_enc_time = 0;
		double avg_dec_time = 0;
		double t_duration = 0;

		int NUMBER_TESTS = 5;
		long signal = 1;
		for (int t = 0; t < NUMBER_TESTS; t++){
			for (int i = 0; i < n; i++){
				// -B <= v[i] <= B
				v[i] = signal * RandomBnd(B+1); 
				signal *= -1;
			}
			t_before = high_resolution_clock::now();
			cout << "Encrypting v = " << v << endl;
			he->enc_vec(cv, v);
			t_after = high_resolution_clock::now();
			t_duration = duration_cast<microseconds>(t_after - t_before).count() / 1000.0;
			cout << t_duration << " milliseconds to encrypt an " << n << "-dimensional vector." << endl;
			avg_enc_time += t_duration / NUMBER_TESTS;

			t_before = high_resolution_clock::now();
			he->dec(cv, cv);
			t_after = high_resolution_clock::now();
			t_duration = duration_cast<microseconds>(t_after - t_before).count() / 1000.0;
			cout << t_duration << " microseconds to decrypt a vector." << endl;
			avg_dec_time += t_duration / NUMBER_TESTS;

			if (cv != v){
				cout << "    ERROR!" << endl;
				cout << "    Vector not correctly decrypted." << endl;
				cout << "    Original vector: " << v << endl;
				cout << "    Decrypted vector: " << cv << endl;
				return false;
			}
		}

		delete he;
		cout << "AVG encryption time for " << n << "-dimensional vectors: "
			 << avg_enc_time << " milliseconds." << endl; 
		cout << "AVG decryption time for " << n << "-dimensional vectors: "
			 << avg_dec_time << " microseconds." << endl; 
		cout << "    OK!" << endl;
	}
	return true;
}

bool test_enc_dec_mult_matrices(long lambda){
	high_resolution_clock::time_point t_before;
    high_resolution_clock::time_point t_after;
	long B = 7; // plaintext matrices may have entries in [[-B, B]]

	std::map<long , PreComputedParams> map_params = select_params(lambda);

	cout << "test_encryption_decryption_time_mat ... " << endl;
	for (const auto& kv : map_params) {
   		long n = kv.first;
		PreComputedParams params = kv.second;

		cout << endl;
		cout << "HENoisyX0 he = new HENoisyX0(lambda, n);" << endl;
		HENoisyX0* he = new HENoisyX0(lambda, n, params.eta, params.rho, params.rho_0,
             				params.gamma, params.log_baseG, B);
	
		mat_ZZ M;
		M.SetDims(n, n);
		mat_ZZ _M;
		_M.SetDims(n, n);
		mat_ZZ C;
		C.SetDims(n * he->l, n);
		mat_ZZ C2;
		C2.SetDims(n * he->l, n * he->l);
		mat_ZZ Cmult;
		Cmult.SetDims(n * he->l, n);


		long signal;
		double avg_enc_time = 0;
		double avg_dec_time = 0;
		double t_duration = 0;
		int NUMBER_TESTS = 3;
		for (int t = 0; t < NUMBER_TESTS; t++){
			for (int i = 0; i < n; i++){
				for (int j = 0; j < n; j++){
					if (rand_bit()) signal = 1;
					else  signal = -1;
					// -B <= M[i][j] <= B
					M[i][j] = signal * RandomBnd(B+1); 
				}
			}

			t_before = high_resolution_clock::now();
			he->enc_mat(C, M);
			t_after = high_resolution_clock::now();
			t_duration = duration_cast<milliseconds>(t_after - t_before).count();
			cout << t_duration << " milliseconds to encrypt a " << n << "x" << n << " matrix." << endl;
			avg_enc_time += t_duration / NUMBER_TESTS;
			
			
			t_before = high_resolution_clock::now();
			he->dec_mat(_M, C);
			t_after = high_resolution_clock::now();
			t_duration = duration_cast<milliseconds>(t_after - t_before).count();
			cout << t_duration << " milliseconds to decrypt a " << n << "x" << n << " matrix." << endl;
			avg_dec_time += t_duration / NUMBER_TESTS;

			if (_M != M){
				cout << "    ERROR!" << endl;
				cout << "    matrix not correctly decrypted." << endl;
				cout << "    Original: " << M << endl;
				cout << "    Decrypted: " << _M << endl;
				return false;
			}


			t_before = high_resolution_clock::now();
			invG_mat(C2, C, he->l, he->baseG);
			Cmult = C2 * C;
			t_after = high_resolution_clock::now();
			t_duration = duration_cast<milliseconds>(t_after - t_before).count();
			cout << t_duration << " milliseconds to multiply two " << n << "x" << n << " matrices." << endl;


		}

		delete he;
		double mega_byte_size = (n*n*he->l * he->gamma) / (8.0 * 1000000);	
		cout << "Estimate size of each encrypted matrix (n = "<<n<<"): "
			 << mega_byte_size << " MB" << endl;
		cout << "AVG encryption time for " << n << "x" << n << " matrices: "
			     << avg_enc_time << " milliseconds" << endl;
		cout << "AVG decryption time for " << n << "x" << n << " matrices: "
			     << avg_dec_time << " milliseconds" << endl;
		cout << "    OK!" << endl;
	}
	return true;
}


bool test_homomorphic_evaluation_nfa(long lambda){

    high_resolution_clock::time_point t_before;
    high_resolution_clock::time_point t_after;

	long n;
	long desired_n = 8;
	long B = 1;
	std::map<long , PreComputedParams> map_params = select_params(lambda);

	for (const auto& kv : map_params) {
   		n = kv.first;
		if(n != desired_n)
			continue;

		// Take the precomputed parameters for this value of n
		PreComputedParams params = kv.second;
		cout << "test_homomorphic_evaluation_nfa ... " << endl;
		cout << "n = " << n << endl;
		cout << "gamma = " << params.gamma << endl;
		cout << "log_baseG = " << params.log_baseG << endl;

		AutomatonLn nfa = AutomatonLn(n);

		cout << "HENoisyX0 he = new HENoisyX0(lambda);" << endl;
		HENoisyX0* he = new HENoisyX0(lambda, n, params.eta, params.rho, params.rho_0,
             				params.gamma, params.log_baseG, B);

		cout << "eta = " << he->eta << endl;
		cout << "b = " << he->baseG << endl;
		cout << "l = " << he->l << endl;
		cout << "gamma = " << he->gamma << endl;
		cout << "rho = " << he->rho << endl;

		double mega_byte_size = (n * n * he->l * he->gamma) / (8.0 * 1000000);
		cout << "Estimate size of each encrypted matrix (n = "<<n<<"): " << mega_byte_size << " MB" << endl;
		mega_byte_size = (n * n * he->l * (he->eta - he->rho)) / (8.0 * 1000000);
		cout << "Estimate size of each compressed encrypted matrix (n = "<<n<<"): " << mega_byte_size << " MB" << endl;

		EncryptedAutomatonLn* encNFA;

		cout << "EncryptedAutomatonLn encNFA = EncryptedAutomatonLn(nfa, he);" << endl;
		t_before = high_resolution_clock::now();
		encNFA = new EncryptedAutomatonLn(nfa, he);
		t_after = high_resolution_clock::now();
		
		cout << duration_cast<milliseconds>(t_after - t_before).count() << " milliseconds to encrypt (n = "<<n<<")." << endl;

		vec_ZZ dec_eval;
		dec_eval.SetLength(n);
		
		int NUMBER_TESTS = 8;
		long k = 8;
		for (int t = 0; t < NUMBER_TESTS; t++){
			string word = sample_word(k);
			cout << "---   ---   ---   ---" << endl;
			cout << "   word = " << word << endl;
			cout << "   len(word) = " << k << endl;

			vec_ZZ eval = nfa.evaluate(word);
			t_before = high_resolution_clock::now();
			vec_ZZ enc_eval = encNFA->evaluate(word); // evaluate homomorphically
			t_after = high_resolution_clock::now();

			cout << duration_cast<milliseconds>(t_after - t_before).count()
				 << " milliseconds to evaluate homomorphically (n = "<<n<<")"
				 << " (k = "<< k <<")." << endl;
  		   
			t_before = high_resolution_clock::now();
			he->dec(dec_eval, enc_eval);
			t_after = high_resolution_clock::now();
			cout << duration_cast<milliseconds>(t_after - t_before).count()
				 << " milliseconds to decrypt (n = "<<n<<")." << endl;

			cout << "    noise: " << he->get_noise(enc_eval, eval) << endl;

			if (dec_eval != eval){
				cout << "    ERROR!" << endl;
				cout << "    homomorphic evaluation didn't decrypt correctly." << endl;
				return false;
			}
			k = 2*k;
		}
		delete he;
		delete encNFA;
		cout << "   OK!" << endl << endl << endl;
		desired_n *= 2;
	}

	return true;
}

void random_vec(vec_ZZ& v, int bitsize){
	for (int i = 0; i < v.length(); i++){
		RandomBits(v[i], bitsize);
		if (rand_bit()){
			v[i] *= -1;
		}
	}
}

void random_mat(mat_ZZ& A, int bitsize){
	for (int i = 0; i < A.NumRows(); i++){
		for (int j = 0; j < A.NumCols(); j++){
			RandomBits(A[i][j], bitsize);
			if (rand_bit()){
				A[i][j] *= -1;
			}
		}
	}
}


int main(int argc, char* argv[]){

	srand(time(NULL)); // XXX: This is insecure. We are using it only for testing!

	long lambda = 80; // security level
	long n = 16; // number of states of automaton

	string opt("none");

	if (1 == argc){
		cout << "ERROR" << endl;
		cout << "  usage: ./a.out <test_name>" << endl;
		return 1;
	}

	if (argc > 1)
		opt = argv[1];

	if (opt == "test_vectors"){
		if(! test_encryption_decryption_vec(lambda))
			return 1;
	}

	if (opt == "test_matrices"){
		if(! test_enc_dec_mult_matrices(lambda))
			return 1;
	}

	if (opt == "test_nfa"){
		if(! test_homomorphic_evaluation_nfa(lambda)){
			cout << endl;
			cout << "Check the value of baseG!" << endl;
			cout << endl;
			return 1;
		}
	}
	
	if (opt == "test_naive_bayes_classifier"){
		if(! test_naive_bayes_classifier(lambda))
			return 1;
	}

    return 0;
}

