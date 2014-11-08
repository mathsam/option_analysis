#include"park_miller_rand.h"

/**
\fn n_rand
\brief Generate n random numbers

@param num : the number of random numbers to return
@param seed: seed for random number generation
@return : an array of num of random numbers

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
