#ifndef PARK_MILLER_RAND_H
#define PARK_MILLER_RAND_H

/**
\class ParkMillerOneRand

\brief Generate one random number using Park Miller congruential generator
           Need a none zero seed; default seed is 1
*/

class ParkMillerOneRand{
public:
    ParkMillerOneRand(long seed = 1);

    long GetOneRandInt();

    void set_seed(long seed);

/*\brief return the upper bound for random number 

The random number generated is within a min and maxmum bound. This is
[1, 2147483646] in this implementation.
*/
    unsigned long get_range_max();

/* return the lower bound for random number */
    unsigned long get_range_min();
private:
    long seed_;
};


#endif //PARK_MILLER_RAND_H
