#include"rand_generator.h"
#include<stdexcept>
#include<cmath>

static int box_muller_polar(double uniform_rand1, double uniform_rand2,
                            double & norm_rand1,  double & norm_rand2);

RandGenerator::RandGenerator(int dimen):
    dimension_(dimen){
    if (dimen < 1)
        throw std::invalid_argument("dimension must no less than 1");
}

inline int RandGenerator::get_dimension() const{
    return dimension_;
}

void RandGenerator::GenNormRand(std::vector<double> & rand_array){
    if (rand_array.size() != dimension_)
        throw std::invalid_argument("vector's size must equal RNG's dimension");

    ///if size of rand_array is an odd number, get a normal random number for
    ///rand_array[0] first, and then the size rest of the array is even
    int start_index = rand_array.size()%2; 
    if(0 != start_index) GenNormRand(rand_array[0]);
    for(int i=start_index; i<rand_array.size(); i+=2){
        double uniform_rand1, uniform_rand2;
        do{
            GenUniformRand(uniform_rand1);
            GenUniformRand(uniform_rand2);
        }
        while(box_muller_polar(uniform_rand1, uniform_rand2,
                           rand_array[i], rand_array[i+1]));
    }
}

void RandGenerator::GenNormRand(double & rand_num){
    if (1 != dimension_)
        throw std::invalid_argument("RNG's dimension is not 1");

    double uniform_rand1, uniform_rand2;
    double norm_rand1, norm_rand2;
    do{
        GenUniformRand(uniform_rand1);
        GenUniformRand(uniform_rand2);
    }
    while(box_muller_polar(uniform_rand1, uniform_rand2,
                           norm_rand1, norm_rand2));

    rand_num = norm_rand1;
}

void RandGenerator::ResetDimension(int new_dimen){
    if (new_dimen < 1)
        throw std::invalid_argument("dimension must no less than 1");
    else
        dimension_ = (unsigned int) new_dimen;
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
@note Algorithm
The original Box-Muller algorithm (1958, Box and Muller, Ann. Math. Statist.) 
do the following transform
\f{eqnarray*}{
    X_{1}&=&(-2\ln U_{1})^{1/2}\cos(2\pi U_{2}), \\
    X_{2}&=&(-2\ln U_{1})^{1/2}\sin(2\pi U_{2}),
\f}
where \f$ U_1 \f$ and \f$ U_2 \f$ are uniformly distributed random variables 
within (0, 1). \f$ X_1 \f$ and \f$ X_2 \f$ follow standard normal distribution.

The polar form is based on rejection sampling. We set
\f[
    s = u^{2} + u^{2},
\f]
and use it if \f$ s<1 \f$, otherwise draw another pair of \f$ u\f$ and  
\f$ v\f$, where \f$ u\f$ and \f$ v\f$ are uniform distributed random numbers
within (-1, 1).
We can show that \f$ s\f$ is a uniformly distributed
random variable within (0,1). Furthermore, the angle determined by 
\f$ \tan\theta=U_{1}/U_{2} \f$ is also uniformly distributed. The process can
be thought as throwing a pin randomly onto a unit circle. The transform is now
\f{eqnarray*}{
    X_{1}&=&(-2\ln(s) /s)^{1/2} u, \\
    X_{2}&=&(-2\ln(s) /s)^{1/2} v,
\f}
*/
static int box_muller_polar(double uniform_rand1, double uniform_rand2,
                            double & norm_rand1,  double & norm_rand2){
    double s;
    double u = 2.0*uniform_rand1 - 1.0; ///< transform (0,1) dist. into (-1,1)
    double v = 2.0*uniform_rand2 - 1.0;
    s = std::sqrt(u*u + v*v);
    if(s > 1.0 || s== 0.0)  
        return 1;

    double s_ratio = std::sqrt(-2.0* std::log(s) / s);
    norm_rand1 = uniform_rand1*s_ratio;
    norm_rand2 = uniform_rand2*s_ratio;
    return 0;
}
