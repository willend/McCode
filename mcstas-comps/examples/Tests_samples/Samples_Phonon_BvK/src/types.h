#pragma once
#include <float.h>
#include <complex.h>

#define FLOAT_TYPE float64

#if   FLOAT_TYPE==float64
 #define real_t double
 #define machine_precision DBL_EPSILON
 #define PRINTF_G "%g"

#elif FLOAT_TYPE==float80
 #define real_t long double
 #define PRINTF_G "%Lg"
 #define creal(x) creall(x)
 #define cimag(x) cimagl(x)

 #define conj conjl
 #define sqrt sqrtl
 #define fabs fabsl
 #define machine_precision LDBL_EPSILON

#elif FLOAT_TYPE==float32
 #define real_t float
 #define PRINTF_G "%g"
 #define creal(x) crealf(x)
 #define cimag(x) cimagf(x)

 #define conj conjf
 #define sqrt sqrtf
 #define fabs fabsf
 #define machine_precision FLT_EPSILON
#endif

#ifdef __cplusplus
 #include <complex>
 typedef std::complex<real_t> complex_t;
#else
typedef real_t complex complex_t;
#endif


#define INLINE inline __attribute__((always_inline))


typedef struct {
  real_t value[2];
} real_pair;

typedef complex_t scalar;
