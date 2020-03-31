#ifndef __MY_UTILS_FUNCS__
#define __MY_UTILS_FUNCS__

#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <NTL/mat_ZZ_p.h>
#include <NTL/mat_ZZ.h>

using namespace std;
using namespace NTL;


/* Set A = B * C mod n */
void mulMod(mat_ZZ& A, const mat_ZZ& B, const mat_ZZ& C, const ZZ& n);


/* Multiply v by the j-th colum of A and return the result reduced mod n */
ZZ mulMod_v_column(const vec_ZZ& v, const mat_ZZ& A, const ZZ& n, long j);


void reduce_vec_mod(vec_ZZ& vec, ZZ mod);

void reduce_mat_mod(mat_ZZ& mat, ZZ mod);

bool rand_bit();

/**
 * Return  round(a/n), that is, interpret a/n as an rational number
 * then return the closest integer to it.
 */
ZZ rounded_division(const ZZ& a, const ZZ& n);

/*
 *      Set words_vec to G^-1(vec), that is, assuming that vec is an n-dimensional vector
 * and words_vec an (n*l)-dimensional, then words_vec[0:l-1] corresponds to the base-b decomposition
 * vec[0], bits_vec[l:2*l-1] corresponds to the base-b decomposition of vec[1], and so on.
 * 		Thus l must have a value such that max(abs(vec[i])) < b^l.
 */
void invG(vec_ZZ& words_vec, const vec_ZZ& vec, long l, ZZ b);

void invG_mat(mat_ZZ& words_mat, mat_ZZ& mat, long l, ZZ b);

string sample_word(long k); // random word with k chars that can be a or b. It must finish with a(a+b)(a+b)(a+b) to be accepted

#endif
