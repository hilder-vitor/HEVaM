#include "utils.h"

using namespace std;
using namespace NTL;


/* Set A = B * C mod n */
void mulMod(mat_ZZ& A, const mat_ZZ& B, const mat_ZZ& C, const ZZ& n){
	mul(A, B, C);
	for (int i = 0; i < A.NumRows(); i++)
		for (int j = 0; j < A.NumCols(); j++)
			A[i][j] %= n;
}

/* Multiply v by the j-th colum of A and return the result reduced mod n */
ZZ mulMod_v_column(const vec_ZZ& v, const mat_ZZ& A, const ZZ& n, long j){
	ZZ res = ZZ(0);
	for (int i = 0; i < A.NumRows(); i++){
		res += v[i] * A[i][j];
	}
	return res % n;
}

void reduce_vec_mod(vec_ZZ& vec, ZZ mod){
	for (long i = 0; i < vec.length(); i++)
		vec[i] %= mod;
}
void reduce_mat_mod(mat_ZZ& mat, ZZ mod){
	for (long i = 0; i < mat.NumRows(); i++){
		for (long j = 0; j < mat.NumCols(); j++){
			mat[i][j] %= mod;
		}
	}
	
}

bool rand_bit(){
	return (rand() % 2);
}

/**
 * Return  round(a/n), that is, interpret a/n as an rational number
 * then return the closest integer to it.
 */
ZZ rounded_division(const ZZ& a, const ZZ& n){
	long signal = (a >= 0 ? 1 : -1);
	ZZ _a = a*signal;
	// interpret a = q*n + r with 0 <= r < n
	ZZ q = _a / n;
	ZZ r = _a % n;
	if (2*r < n)
		return signal * q;
	else
		return signal * (q + 1);
}

/*
 *      Set words_vec to G^-1(vec), that is, assuming that vec is an n-dimensional vector
 * and words_vec an (n*l)-dimensional, then words_vec[0:l-1] corresponds to the base-b decomposition
 * vec[0], bits_vec[l:2*l-1] corresponds to the base-b decomposition of vec[1], and so on.
 * 		Thus l must have a value such that max(abs(vec[i])) < b^l.
 */
void invG(vec_ZZ& words_vec, const vec_ZZ& vec, long l, ZZ b){
	long n = vec.length();
	for(int i = 0; i < n; i++){
		ZZ x = vec[i];
		long sign = (x < 0 ? -1 : 1);
		x *= sign;
		for (int j = 0; j < l; j++){
			words_vec[i*l + j] = sign * (x % b);
			x /= b;
		}
	}
}

void invG_mat(mat_ZZ& words_mat, mat_ZZ& mat, long l, ZZ b){
	long nrows = mat.NumRows();
	for (long i = 0; i < nrows; i++){
		invG(words_mat[i], mat[i], l, b);
	}
}

string sample_word(long k){ // random word with k chars that can be a or b. It must finish with a(a+b)(a+b)(a+b) to be accepted
    string word(k, 'a'); // word = aaa...a  (k chars all equal to a)
	for (long i = 0; i < k; i++){
		word[i] += rand_bit(); // 'a' + 0 = 'a' and 'a' + 1 = 'b'
	}
	return word;
}
