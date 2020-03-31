#include "HENoisyX0.h"
#include "utils.h"

using namespace std;
using namespace NTL;


void HENoisyX0::initialize_alpha(){
	this->alpha = 1;
	this->alpha <<= (eta - 1);
	this->alpha /= (2*B + 1); // alpha < 2^(eta - 1) / (2B + 1)
}

HENoisyX0::HENoisyX0() {
	// Default constructor. If you use it, then you have to set everything manually!
}

void HENoisyX0::keyGen() {
	this->bound_q = gamma - eta;
	this->size_fresh_noise = 1;
	size_fresh_noise <<= rho;

	this->p = RandomPrime_ZZ(eta); // random prime in [2^(eta-1), 2^eta]

	this->x0 = p;
	for (int i = eta; i < gamma - eta; i += eta)
		this->x0 *= RandomPrime_ZZ(eta); // random prime in [2^(eta-1), 2^eta]
	if (NumBits(x0) < gamma){
		this->x0 *= RandomPrime_ZZ(gamma - NumBits(x0));
	}
	
	ZZ r0;
	do {
		RandomBits(r0, rho_0);
	}while ((this->x0 + r0) % 2 == 0);
	this->x0 += r0;

	this->l = ceil(((double)gamma) / log_baseG); // l = log(x0) in base baseG

	cout << "lambda = " << lambda << endl;
	cout << "B = " << B << endl;
	cout << "rho = " << rho << endl;
	cout << "rho_0 = " << rho_0 << endl;
	cout << "log(baseG) = " << NumBits(baseG)-1 << endl;
	cout << "eta = " << eta << endl;
	cout << "gamma = " << gamma << endl;
	cout << "NumBits(x0) = "<< NumBits(x0) << endl;
	cout << "l =" << l << endl;
	cout << "alpha =" << alpha << endl;

	cout << "this->sample_K_inv_K();" << endl;
	this->sample_K_inv_K();
	cout << "finished this->sample_K_inv_K();" << endl;

	this->digits_vec.SetLength(n*l);
}

HENoisyX0::HENoisyX0(long lambda, long n, long eta, long rho, long rho_0,
			long gamma, long log_baseG, long B) {
	
	this->lambda = lambda;
	this->n = n;
	this->B = B;
	this->eta = eta;
	this->rho = rho;
	this->rho_0 = rho_0;
	this->gamma = gamma;
	this->log_baseG = log_baseG;

	this->baseG = 1;
	this->baseG <<= log_baseG;

	this->initialize_alpha();
	
	this->keyGen();
}


/* This function should simple be something like
 *    modK = random_matrix()
 *    inversible = false
 *    do {
 *   	 try {
 *    			invK = inverse(modK)
 *    			inversible = true
 *	    } catch (InvModErrorObject& e){
 *
 *  	}
 *    }while(! inversible)
 *
 * 	But the algorithm that NTL uses to compute inverses only works modulo
 * primes (or powers of primes) and x0 is composite.
 */
void HENoisyX0::sample_K_inv_K(){
	ZZ_p::init(x0); // set modulus to be x0
	K.SetDims(n, n);
	invK.SetDims(n, n);
	mat_ZZ_p X, modK, invModK;
	X.SetDims(n, n);
	modK.SetDims(n, n);
	invModK.SetDims(n, n);

	modK = ident_mat_ZZ_p(n);
	invModK = ident_mat_ZZ_p(n);
	X = ident_mat_ZZ_p(n);

	long number_iter = 4;
	long rbeg, rend, cbeg, cend;
	for(long  _i = 0; _i < number_iter; _i++){
		// chooses if the block will be above or below the main diagonal
		if (_i % 2 == 0){
			rbeg = n/2; rend = n; cbeg = 0; cend = n/2;
		}else{
			rbeg = 0; rend = n/2; cbeg = n/2; cend = n;
		}
		// samples a random block
		for(long i = rbeg; i < rend; i++)
			for(long j = cbeg; j < cend; j++)
				X[i][j] = random_ZZ_p(); // random element mod x0
		modK = modK * X;
		// computes the inverse of X
		for(long i = rbeg; i < rend; i++)
			for(long j = cbeg; j < cend; j++)
				X[i][j] *= -1;
		invModK = X * invModK;
		// sets X to the identity again
		for(long i = rbeg; i < rend; i++)
			for(long j = cbeg; j < cend; j++)
				X[i][j] = 0;
	}
	K = conv<mat_ZZ>(modK);
	invK = conv<mat_ZZ>(invModK);
}


/**
 *	   Assume that K is already set.
 *	   This function initialize this->GtimesK with a n*l x n matrix corresponding to G*K mod x0,
 *	where G = Identity(n).tensor_product(g.transpose())
 *	and g = [1, b, b^2, b^3, ..., b^(l-1)] where b = this->baseG
 */
void HENoisyX0::computeGtimesK(){
	if (n*l != GtimesK.NumRows() || n != GtimesK.NumCols()){
		GtimesK.SetDims(n*l, n);
		ZZ power_b; // baseG^i
		for (int i = 0; i < n; i++){
			power_b = 1;
			for (int j = 0; j < l; j++){
				// set (i*l + j)-th row of GtimesK to b^j * K_i mod x0, where K_i is the i-th row of K
				for (int s = 0; s < n; s++){
//					GtimesK[i*l + j][s] = (power_b * K[i][s]) % x0;
					GtimesK[i*l + j][s] = (power_b * K[i][s]);
				}
				power_b *= baseG;
			}
		}
	}
}

/**
 * Set this->Q to a random matrix with entries in [0, 2^bound_q]
 */
void HENoisyX0::sample_Q(){
	if (n*l != Q.NumRows() || n != Q.NumCols())
		this->Q.SetDims(n*l, n);

	for(int i = 0; i < n*l; i++)
		for (int j = 0; j < n; j++)
			RandomBits(Q[i][j], bound_q);
}

/**
 * Set this->R to a random matrix with entries in [-2^rho, 2^rho]
 */
void HENoisyX0::sample_R(){
	if (n*l != R.NumRows() || n != R.NumCols())
		this->R.SetDims(n*l, n);

	for(int i = 0; i < n*l; i++){
		for (int j = 0; j < n; j++){
			RandomBits(R[i][j], rho);
			if (rand_bit()){
				R[i][j] *= -1;
			}
		}
	}
}

void HENoisyX0::enc_mat(mat_ZZ& C, const mat_ZZ& M){ // encrypt nxn matrix M
	long n = M.NumRows();
	this->sample_Q();
	this->sample_R();
	Q *= p;
	this->computeGtimesK();
	mulMod(C, GtimesK, M, x0); // C = G*K*M  mod x0
	C += R;
	C += Q; // C = pQ + R + G*K*M
	mulMod(C, C, invK, x0); // C = (pQ + R + G*K*M)*K^-1 mod x0
}

void HENoisyX0::enc_vec(vec_ZZ& c, const vec_ZZ& m) const{ // encrypt n-dimensional vector m
	// this function is used a single time to encrypt the state vector of the given automaton
	vec_ZZ q;
	q.SetLength(n);
	for (int j = 0; j < n; j++)
		RandomBits(q[j], bound_q);
	vec_ZZ r;
	r.SetLength(n);
	for (int j = 0; j < n; j++){
		RandomBits(r[j], rho);
		if (rand_bit()){
			r[j] *= -1;
		}
	}
	c = (p*q + r + alpha * m) * invK;	
	for (int j = 0; j < n; j++)
		c[j] %= x0;
}

void HENoisyX0::symmetric_mod(ZZ& a, const ZZ& b, const ZZ& c){ // set a = b % c using the set [-c/2, c/2] as Z/cZ
	a = b % c;
	if(2*a > c)
		a = a - c;
}

void HENoisyX0::dec(vec_ZZ& m, const vec_ZZ& c){ // decrypt n-dimensional vector c and store the result in m
	m = c*K;
	for (int i = 0; i < n; i++){
		m[i] = m[i] % x0;
		symmetric_mod(m[i], m[i], p);
		m[i] = rounded_division(m[i], alpha);
	}
}


void HENoisyX0::dec_mat(mat_ZZ& M, const mat_ZZ& C){ // decrypt nxn matrix C and store the result in M
	mat_ZZ words_mat;
	words_mat.SetDims(n, n*l);
	M = alpha*invK;
	reduce_mat_mod(M, x0); // remove multiple of x0

	invG_mat(words_mat, M, l, baseG);
	M = words_mat * C * K;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			M[i][j] = M[i][j] % x0;
			symmetric_mod(M[i][j], M[i][j], p);
			M[i][j] = rounded_division(M[i][j], alpha);
		}
	}
}

void HENoisyX0::multiply(vec_ZZ& c_mult, const vec_ZZ& c, const mat_ZZ& C){
	invG(digits_vec, c, l, baseG); // entries of c must be reduced mod x0
	c_mult = digits_vec * C;
	reduce_vec_mod(c_mult, x0);
}

double HENoisyX0::get_noise(const vec_ZZ& enc_vec, const vec_ZZ& msg){
	vec_ZZ vec_noise = enc_vec * K;
	double max_noise = -1;
	double noise;
	for (int i = 0; i < n; i++){
		vec_noise[i] = vec_noise[i] % x0;
		symmetric_mod(vec_noise[i], vec_noise[i], p);
		noise = log((abs(vec_noise[i] - alpha * msg[i])))/log(2);
		if (noise > max_noise)
			max_noise = noise;;
	}

	return max_noise;
}
