/**
@file
@brief A wrapper to turn C++ object into C function; intends to call from Python
*/
#ifndef PARK_MILLER_RAND_CWRAPPER_H
#define PARK_MILLER_RAND_CWRAPPER_H

#include"park_miller_rand.h"

/**
@brief Generate n random numbers

@param num  the number of random numbers to return
@param seed seed for random number generation
@return an array of num of random numbers

Intends to be a wrapper to call from Python
*/
extern "C" int* n_rand(int num , int seed);

extern "C" double* uniform_rand(int num, int seed);

extern "C" double* norm_rand(int num, int seed);

#endif //PARK_MILLER_RAND_CWRAPPER_H
