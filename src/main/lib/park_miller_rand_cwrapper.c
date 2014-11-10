/**
@file
*/
#include"park_miller_rand.h"
#include"rand_generator.h"
#include"park_miller_rand_cwrapper.h"

/**
\fn n_rand
\brief Generate n random numbers

@param num : the number of random numbers to return
@param seed: seed for random number generation
@return an array of num of random numbers

Intends to be a wrapper to call from Python
*/
extern "C" int* n_rand(int num //< number of integers to return
                     , int seed//< seed for RNG, cannot be zero
                      )
{
    ParkMillerOneRand myrand(seed);
    int * rand_array = new int[num];
    for(int i = 0; i < num; i++){
        rand_array[i] = (int) myrand.GetOneRandInt();
    }
    return rand_array;
}

/**
\brief generate an array of uniformly distributed random number

@param num number of random number to generate
@param seed seed for random number generator
@return an array of num of random numbers
*/
extern "C" double* uniform_rand(int num, int seed){
    RandGenerator* p_rand_gen = new ParkMillerRand(seed);
    double * rand_array = new double[num];
    for(int i = 0; i < num; i++){
        p_rand_gen->GenUniformRand(rand_array[i]);
    }
    delete p_rand_gen;
    return rand_array;
}

/**
\brief generate an array of normally distributed random number

@param num number of random number to generate
@param seed seed for random number generator
@return an array of num of random numbers
*/
extern "C" double* norm_rand(int num, int seed){
    RandGenerator* p_rand_gen = new ParkMillerRand(seed);
    double * rand_array = new double[num];
    for(int i = 0; i < num; i++){
        p_rand_gen->GenNormRand(rand_array[i]);
    }
    delete p_rand_gen;
    return rand_array;
}
