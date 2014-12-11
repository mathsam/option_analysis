#ifndef PARK_MILLER_RAND_H
#define PARK_MILLER_RAND_H
#include"rand_generator.h"
#include<vector>

/**
\class ParkMillerOneRand

\brief Generate one random integer using Park Miller congruential generator
           Need a none zero seed; default seed is 1

long integer on the platform must at least be 32 bit
*/

class ParkMillerOneRand{
public:
    ParkMillerOneRand(long seed = 1);

    long GetOneRandInt();

    void set_seed(long seed);

/**
\brief return the upper bound for random number 

The random number generated is within a min and maxmum bound. This is
[1, 2147483646] in this implementation.
*/
    unsigned long get_range_max();

/// return the lower bound for random number
    unsigned long get_range_min();
private:
    long seed_;
};

/**
@class ParkMillerRand
@brief Generate one or an array of uniformly/normally distributed random
       numbers
@note An adapter pattern to make class ParkMillerOneRand have the same interface
      as the base class RandGenerator

Usage: refer to base class RandGenerator
*/
class ParkMillerRand : public RandGenerator{
public:
    /**
    @brief constructs a random number generator with a given seed (default is 1)
    @param seed default is 1 
    */
    ParkMillerRand(long seed = 1);

    RandGenerator* clone() const;

    void GenUniformRand(std::vector<double> & rand_array);

    void GenUniformRand(double & rand_num);

    void SkipNumOfPath(int num_of_path);

    void set_seed(int seed);

    void Reset();

private:
    const long original_seed_; ///< seed when constructed; immutable after
                               ///< construction
    ParkMillerOneRand int_rand_generator_;
    double ratio_int2uniform_; ///< multiplier to convert radom integer into
                               ///< float number within (0,1) 
};

#endif //PARK_MILLER_RAND_H
