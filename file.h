#ifndef __FILE_H__
#define __FILE_H__
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])
//typedef double complex cplx;

double* audiofileSelec();

#endif