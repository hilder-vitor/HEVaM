#ifndef __AUTOMATON_LN__
#define __AUTOMATON_LN__


#include <NTL/mat_ZZ.h>
#include <NTL/vec_ZZ.h>

/** 
 * Non-deterministic automaton that recoginazes the language (a+b)*a(a+b)^(n-2).
 * Uses PRG to compress ciphertexts.
 * It has n states and is represented by two nxn transition matrices (one for
 * the letter 'a' and other for the letter 'b').
 **/
class AutomatonLn {

	public:
		long n;
		NTL::mat_ZZ Ma;
		NTL::mat_ZZ Mb;

	AutomatonLn(long n);

	NTL::vec_ZZ new_initial_state_vector() const;

	//   Let v be the n-dimensional vector returned by this function.
	//   The word is accepted if, and only if, v[n-1] == 1.
	NTL::vec_ZZ evaluate(std::string word);

};
#endif
