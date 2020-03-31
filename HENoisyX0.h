#ifndef __AGCD_BASED_HE__
#define __AGCD_BASED_HE__

#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <NTL/mat_ZZ_p.h>
#include <NTL/mat_ZZ.h>


class HENoisyX0 {

	public:
		NTL::ZZ x0;
		long n; // dimension of vectors and matrices
		long log_baseG; // logarithm of baseG in base 2
		NTL::ZZ baseG; // base in which G^-1 decomposes the integers
		long l; // logarightm of x0 in base baseG
		long eta; // bitsize of the prime p
		long gamma; // bitsize of x0
		long lambda; // secutiry parameter
		long B;  // plaintexts must have entries in ]-B, B[
		long rho_0; // noise of x0 is between -2^rho_0 and 2^rho_0
	
		NTL::ZZ alpha;  // shift applied to vectors before encrypting 

	//private:
		NTL::ZZ p;
		NTL::mat_ZZ K;
		NTL::mat_ZZ invK;
		
		//-- auxiliary variables used to avoid allocating memory all the time --//
		NTL::mat_ZZ Q;
		NTL::mat_ZZ R;
		NTL::mat_ZZ GtimesK; // precomputed since G*K is needed in every encryption

		NTL::vec_ZZ digits_vec; // to store G^-1 of c when multiplying c by a matrix C

		long bound_q; // q_i sampled from [0, 2^bound_q]
		long rho; // errors sampled from ]-2^rho, 2^rho[
		NTL::ZZ size_fresh_noise; // equal to 2^rho	
	

	// Default constructor. If you use it, then you have to set everything manually!
	HENoisyX0();

	HENoisyX0(long lambda, long n, long eta, long rho, long rho_0,
			long gamma, long log_baseG, long B);


	void initialize_alpha(); // set alpha = floor(2^(eta-1) / (2B + 1))

	virtual void keyGen(); // assume that the parameters (rho, eta, gamma, etc) are already set


	virtual void sample_K_inv_K();

	/**
	 *	   Assume that K is already set.
	 *	   This function initializes this->GtimesK with an n*l x n matrix
	 *	corresponding to G*K mod x0, where
	 *	    G = Identity(n).tensor_product(g.transpose())
	 *	and g = [1, b, b^2, b^3, ..., b^(l-1)] where b = this->baseG
	 */
	void computeGtimesK();

	/**
	 * Set this->Q to a random matrix with entries in [0, 2^bound_q]
	 */
	void sample_Q();

	/**
	 * Set this->R to a random matrix with entries in [-2^rho, 2^rho]
	 */
	void sample_R();

	virtual void enc_mat(NTL::mat_ZZ& C, const NTL::mat_ZZ& M);
	
	void enc_vec(NTL::vec_ZZ& c, const NTL::vec_ZZ& m) const;

	// Sets a to (b mod c) in [-c/2, c/2 [
	void symmetric_mod(NTL::ZZ& a, const NTL::ZZ& b, const NTL::ZZ& c);

	virtual void dec(NTL::vec_ZZ& m, const NTL::vec_ZZ& c);

	virtual void dec_mat(NTL::mat_ZZ& M, const NTL::mat_ZZ& C);

	// homomorphic multiply c per C and store the result in c_mult
	virtual void multiply(NTL::vec_ZZ& c_mult, const NTL::vec_ZZ& c, const NTL::mat_ZZ& C);

	double get_noise(const NTL::vec_ZZ& enc_vec, const NTL::vec_ZZ& msg);

};
#endif
