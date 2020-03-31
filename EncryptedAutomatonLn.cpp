#include "EncryptedAutomatonLn.h"
#include "utils.h"

using namespace std;
using namespace NTL;

EncryptedAutomatonLn::EncryptedAutomatonLn(){

}

/** 
 * Ciphered NFA that recoginazes the language (a+b)*a(a+b)^(n-2).
 **/
EncryptedAutomatonLn::EncryptedAutomatonLn(const AutomatonLn& nfa, HENoisyX0* encryptor){
	this->n = nfa.n;
	this->l = encryptor->l;
	this->x0 = encryptor->x0;
	this->baseG = encryptor->baseG;
	vec_ZZ v = nfa.new_initial_state_vector();
	this->cs.SetLength(n);
	encryptor->enc_vec(cs, v);

	this->Ca.SetDims(l * n, n);
	this->Cb.SetDims(l * n, n);
	encryptor->enc_mat(Ca, nfa.Ma);
	encryptor->enc_mat(Cb, nfa.Mb);
	this->he_scheme = encryptor;
}


/**   Let v be the n-dimensional vector returned by this function.
*   The word is accepted if, and only if, dec(v)[n-1] == 1.
**/
vec_ZZ EncryptedAutomatonLn::evaluate(string word){
	vec_ZZ state_vector(cs);

	for(char& letter : word) {
		if ('a' == letter)
			// state_vector = state_vector * Ca
			he_scheme->multiply(state_vector, state_vector, Ca);
		else
			he_scheme->multiply(state_vector, state_vector, Cb);
	}
	return state_vector;
}
