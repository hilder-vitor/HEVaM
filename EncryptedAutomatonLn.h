#ifndef __ENCRYPTED_AUTOMATON_LN__
#define __ENCRYPTED_AUTOMATON_LN__

#include <NTL/ZZ.h>
#include <NTL/mat_ZZ.h>
#include <string>

#include "HENoisyX0.h"
#include "AutomatonLn.h"


/** 
 * Ciphered NFA that recognizes the language (a+b)*a(a+b)^(n-2).
 **/
class EncryptedAutomatonLn {
	public:
		long n;
		long l;
		NTL::ZZ baseG;
		NTL::ZZ x0;
		NTL::vec_ZZ cs; // encryption of state vector
		NTL::mat_ZZ Ca; // encryption of Ma
		NTL::mat_ZZ Cb; // encryption of Mb
		HENoisyX0* he_scheme;

	EncryptedAutomatonLn();

	EncryptedAutomatonLn(const AutomatonLn& nfa, HENoisyX0* encryptor);

	/**   Let v be the n-dimensional vector returned by this function.
	*   The word is accepted if, and only if, dec(v)[n-1] == 1.
	**/
	virtual NTL::vec_ZZ evaluate(std::string word);

};
#endif
