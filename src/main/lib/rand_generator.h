#ifndef RAND_GENERATOR_H
#define RAND_GENERATOR_H

#include<vector>

/**
@brief base class/interface for a suite of random generators

Usage:

Overloaded for generating one random number and generating a vector of random 
numbers
*/

class RandGenerator{
public:
    /**
    @brief generate a RandGenerator with a certain dimensionality (default is 1)

    @param dimen defines how many random numbers to return in one draw
    */
    RandGenerator(int dimen=1);

    ///returns the dimension of current RandGenerator instance
    inline int get_dimension() const;

    ///bridge pattern
    virtual RandGenerator* clone() const = 0;

    /**
    @brief generate a uniformly distributed random number array within (0,1)

    @param rand_array a vector of double passed in by reference to store the
    output, whose length needs to be the same as the dimensionality
    Note that 0 and 1 are excluded.
    */
    virtual void GenUniformRand(std::vector<double> & rand_array) = 0;

    /**
    @brief generator one uniformly distributed random number within (0,1)

    @param rand_num a double passed in by reference to store the output. In 
    this case, dimensionality of generator must be 1.
    */
    virtual void GenUniformRand(double & rand_num) = 0;

    /// skip a certain number of random numbers in order to avoid same numbers
    /// (paths)
    virtual void SkipNumOfPath(int num_of_path) = 0;

    /// set the seed for random number generator
    virtual void SetSeed(int seed) = 0;

    /// reset the generator to its initial state (when constructed)
    virtual void Reset() = 0;

    /**
    @brief generate an array of standard normal distribution

    @param rand_array a vector of double passed in by reference to store the
    output, whose length must be the same as the dimensionality of the
    generator 
    */
    virtual void GenNormRand(std::vector<double> & rand_array);

    /**
    @brief generate one standard normal distribution

    @param rand_num a double passed in by reference to store the
    output. The dimensionality of generator must be 1 
    */
    virtual void GenNormRand(double & rand_num);

    ///reset dimensionality of the random number generator
    virtual void ResetDimension(int new_dimen);

private:
    unsigned int dimension_;///< dimensionality that every derived class must 
                            ///< have
};
#endif //RAND_GENERATOR_H
