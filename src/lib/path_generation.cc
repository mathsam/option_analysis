#include"path_generation.h"
#include<stdexcept>
#include<cmath>

PathGenerator::PathGenerator(const MarketParameters & market_params,
                             RandGenerator & rand_gen,
                  double spot, int num_times, double expiration_time):
  market_params_(market_params), rand_generator_(rand_gen),
  spot_(spot), num_times_(num_times), time_points_(num_times) {
    if (spot <= 0.0)
        throw std::invalid_argument("spot price must be positive");

    if (num_times < 1)
        throw std::invalid_argument("number of times must be at least 1");

    if (expiration_time <= 0.0)
        throw std::invalid_argument("expiration time must be positive");

    for(int i=0; i < num_times; ++i){
        time_points_[i] = double(i+1)/double(num_times) * expiration_time;
    }
}

PathGenerator::PathGenerator(const MarketParameters & market_params,
                  RandGenerator & rand_gen,
                  double spot, const std::vector<double> & time_points):
  market_params_(market_params), rand_generator_(rand_gen),
  spot_(spot), num_times_(time_points.size()), time_points_(time_points){
    if (spot <= 0.0)
        throw std::invalid_argument("spot price must be positive");

    if (num_times_ < 1)
        throw std::invalid_argument("number of times must be at least 1");

    for(int i = 0; i < time_points.size(); ++i){
        if(time_points[i] <= 0)
           throw std::invalid_argument("time points must be positive");
    }

    for(int i = 0; i < time_points.size() - 1; ++i){
        if(time_points[i] >= time_points[i+1])
           throw std::invalid_argument("time points must increase " 
                                       "monotonically");
    }
}

void PathGenerator::GetOnePath(std::vector<double> & path_out){
    if(path_out.size() != num_times_)
        throw std::invalid_argument(
                     "size of path_out does not match number of times");

    double S_i     = spot_;

    double t_left  = 0;
    double t_right;
    for(int i = 0; i < num_times_; ++i){
        if(i>0) t_left = time_points_[i-1];
        t_right = time_points_[i];

        double int_sigma_square = market_params_.volatility_->IntegralSquare(
                                                            t_left, t_right);
        double norm_rand;
        rand_generator_.GenNormRand(norm_rand);
        S_i = S_i *( std::exp(
                  market_params_.interest_rate_->Integral(t_left, t_right) 
                - market_params_.divident_rate_->Integral(t_left, t_right)
                - 0.5 * int_sigma_square 
                             
                     + std::sqrt(int_sigma_square) * norm_rand
                             )
                    );
       path_out[i] = S_i;
    }
}

void PathGenerator::GetNPaths(std::vector<std::vector<double> > & paths_out){
    if(paths_out.size() < 1)
        throw std::invalid_argument("empty vector paths_out");
    if(paths_out[0].size() != num_times_)
        throw std::invalid_argument(
                     "size of paths_out does not match number of times");

    for(int i=0; i < paths_out.size(); ++i)
        GetOnePath(paths_out[i]);
}
