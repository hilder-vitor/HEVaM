#include "AutomatonLn.h"

using namespace std;
using namespace NTL;

/** 
 * Non-deterministic automaton that recoginazes the language (a+b)*a(a+b)^(n-2).
 * Uses PRG to compress ciphertexts.
 * It has n states and is represented by two nxn transition matrices (one for
 * the letter 'a' and other for the letter 'b').
 **/
AutomatonLn::AutomatonLn(long n){
	this->n = n;
	this->Ma.SetDims(n, n);
	this->Mb.SetDims(n, n);

	for(long i=1; i < n-1; i++){
		this->Ma[i][i+1] = 1;
		this->Mb[i][i+1] = 1;
	}
	this->Ma[0][0] = this->Mb[0][0] = 1;
	this->Ma[0][1] = 1;
}

vec_ZZ AutomatonLn::new_initial_state_vector() const{
	// initialize a state vector
	vec_ZZ state_vector;
	state_vector.SetLength(n);
	state_vector[0] = 1;
	for(long i = 1; i < n; i++)
		state_vector[i] = 0;
	return state_vector;
}

//   Let v be the n-dimensional vector returned by this function.
//   The word is accepted if, and only if, v[n-1] == 1.
vec_ZZ AutomatonLn::evaluate(string word){
	vec_ZZ state_vector = new_initial_state_vector();

	for(char& letter : word) {
		if ('a' == letter)
			state_vector *= Ma;
		else
			state_vector *= Mb;
	}
	return state_vector;
}
