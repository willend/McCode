#pragma once
#include "types.h"


void print_vector(const char *name, scalar *a, int l);
void print_matrix(const char *name, scalar *A, int m, int n);

real_t vector_norm(const scalar *x, int n);
void   extract_region(scalar *S, int N,
		    int i0, int j0, int m, int n,
		    scalar *D);
real_t max_norm(complex_t *A, int m, int n);
void identity_matrix(scalar *Q, int n);
void real_identity_matrix(real_t *Q, int n);
void matrix_inplace_multiply(scalar *A, const scalar *B, 
			     int m, int n, int q);

void reflection_vector(/*in*/const scalar *a, const real_t anorm,
		       /*out*/scalar *v, scalar *sigma, int n);
void apply_reflection(/*in/out*/scalar *A, const scalar *v,
		      int m, int n, scalar sigma, int transpose);

void reflect_region(/*in/out*/scalar *A, int N,
		    int i0, int j0, int m, int n,
		    const scalar *v, scalar sigma, int cols);

void apply_real_reflections(const real_t *V, const int n, real_t *Q, const int m);


void QHQ(/*in/out*/scalar *A, int n, scalar *Q);
void T_QTQ(const int n,
	   const real_t *Din, const real_t *Lin,
	   real_t *Dout, real_t *Lout, real_t *Vout,
	   real_t shift);

real_pair eigvalsh2x2(real_t a, real_t b, real_t c, real_t d);

real_pair eigensystem_hermitian(const scalar *A, const int n,
				real_t *lambdas, scalar *Q);

