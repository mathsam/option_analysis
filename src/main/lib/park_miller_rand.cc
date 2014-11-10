#include"park_miller_rand.h"
#include<stdexcept>

static const long kA = 48271;
static const long kM = 2147483647;
static const long kQ = 44488;
static const long kR = 3399;

ParkMillerOneRand::ParkMillerOneRand(long seed) : seed_(seed){
    if (seed == 0)
        throw std::invalid_argument("seed must be none zero");
}

void ParkMillerOneRand::set_seed(long seed){
    seed_ = seed;
    if (seed == 0)
        throw std::invalid_argument("seed must be none zero");
}

unsigned long ParkMillerOneRand::get_range_min(){
    return 1;
}

unsigned long ParkMillerOneRand::get_range_max(){
    return kM - 1;
}

/**
\brief returns one random integer

Lehmer random number generator (RNG) or Park-Miler RNG. It is a congruential 
generator.

Park-Miller Algorithm:
\f[
    X_{k+1} =  A\cdot X_{k}\mathrm{\ mod}\ M 
\f]
Based on Diane Crawford (1993, Technical correspondence, 
Communications of the ACM, Vol 36), the parameters are choosen as A = 48271 
and M = 2147483647 (which is 2^31 - 1).

Schrage's Algorithm:
To aviod multiplication of 32-bit numbers on a 32-bit machine, Schrage's algo 
is used. It is based on an approximate factorization of M as
\f[
    M = AQ + R,\ Q = [M/A],\ R = M\mathrm{\ mod} A
\f]
The brackets [] denotes integer division. We want R to be small and choose 
Q = 44488 and R = 3399. Note R < A and R < Q. Then the iteration becomes
\f{eqnarray*}{
    X_{k+1} &=& A (I_i - [X_i/q]\cdot Q) - R\cdot [X_i/Q] \\
            &=& A (I_i \ \mathrm{mod} Q) - R\cdot [X_i/Q]
\f}
If \f$ I_{k+1} < 0 \f$, then
\f[
    X_{k+1} = X_{k+1} + m
\f]

Proof: the key to prove is that \f$ x\mathrm{mod}b = x - [x/b]b \f$.
As M = AQ + R, we have
\f{eqnarray*}{
    X_{k+1}&=AX_{k}-[\frac{AX_{k}}{AQ+R}](AQ+R)\\
           &=AX_{k}-[\frac{X_{k}}{Q}\frac{1}{1+R/(AQ)}](AQ+R)
\f}
Because R/AQ << 1, use Taylor expansion, we have
\f[
    X_{k+1}=AX_{k}-[\frac{X_{k}}{Q}-\frac{X_{k}}{AQ}\frac{R}{Q}](AQ+R)
\f]
Because AQ~M, R<Q, we have \f$ \frac{X_{k}}{AQ}\frac{R}{Q} < 1\f$. 
So \f$ [\frac{X_{k}}{Q}-\frac{X_{k}}{AQ}\frac{R}{Q}] \f$ is either 
\f$ [\frac{X_{k}}{Q}] \f$ or \f$ [\frac{X_{k}}{Q}]-1 \f$
*/
long ParkMillerOneRand::GetOneRandInt(){
    seed_ = kA*(seed_ % kQ) - kR*(seed_ / kQ);
    if (seed_ < 0) seed_ += kM;
    return seed_;
}

ParkMillerRand::ParkMillerRand(long seed):
    original_seed_(seed){
    ParkMillerOneRand int_rand_generator_(seed);
    ratio_int2uniform_ = 1.0/((double) int_rand_generator_.get_range_max()+1.0);
    ///< + 1 thus cannot reach 1.0 
}

RandGenerator* ParkMillerRand:: clone() const{
    return new ParkMillerRand(*this);
}

void ParkMillerRand:: GenUniformRand(std::vector<double> & rand_array){
    if(rand_array.size() < 1)
        throw std::invalid_argument("array size must be no less than 1");

    for(int i=0; i<rand_array.size(); i++)
        rand_array[i] = (double) int_rand_generator_.GetOneRandInt()
                        * ratio_int2uniform_;
}

void ParkMillerRand:: GenUniformRand(double & rand_num){
    rand_num = (double) int_rand_generator_.GetOneRandInt() 
               * ratio_int2uniform_;
}

void ParkMillerRand:: SkipNumOfPath(int num_of_path){
    if(num_of_path < 0)
        throw std::invalid_argument("the number of path to skip cannot be negative");
    for(int i=0; i<num_of_path; i++)
        int_rand_generator_.GetOneRandInt();
}

void ParkMillerRand:: set_seed(int seed){
    int_rand_generator_.set_seed(seed);
}

void ParkMillerRand:: Reset(){
    int_rand_generator_.set_seed(original_seed_);
}
