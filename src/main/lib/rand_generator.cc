#include"rand_generator.h"
#include<stdexcept>
#include<cmath>

RandGenerator::RandGenerator(int dimen = 1):
    dimension_(dimen){
    if (dimen < 1)
        throw std::invalid_argument("dimension must no less than 1");
}

int RandGenerator::get_dimension(){
    return dimension_;
}

void RandGenerator::GenNormRand(std::vector<double> & rand_array){

}

void RandGenerator::GenNormRand(double & rand_num){

}

void ResetDimension(int new_dimen){
    if (new_dimen < 1)
        throw std::invalid_argument("dimension must no less than 1");
    else
        dimension_ = new_dimen;
}

/**
@brief Box-Muller algorithm in polar form to transform two uniformly distributed
       random variable into two with standard normal distribution

@param uniform_rand1 first uniform distributed random number within (0, 1)
@param uniform_rand2 second uniform distributed random number within (0, 1)
@param norm_rand1 passed in by reference to output first normal random number
@param norm_rand2 passed in by reference to output second normal random number
@return an integer indicating error code; 0 for success, 1 for failure
        There is 27.32% chance that this transform will fail beause it needs two
        input random numbers to be distributed within a unit circle
@warning always check the error code the function returns
 
*/
static int box_muller_polar(double uniform_rand1, double uniform_rand2,
                            double & norm_rand1,  double & norm_rand2){
    double s;
    double u = 2.0*uniform_rand1 - 1.0; ///< transform (0,1) dist. into (-1,1)
    double v = 2.0*uniform_rand2 - 1.0;
    s = std::sqrt(u*u + v*v);
    if(s > 1.0 || s== 0.0)  
        return 1;

    double s_ratio = std::sqrt(-2.0* std::log(s) / s)
    norm_rand1 = uniform_rand1*s_ratio;
    norm_rand2 = uniform_rand2*s_ratio;
    return 0;
}
