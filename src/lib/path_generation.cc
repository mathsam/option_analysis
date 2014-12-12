#include"path_generation.h"
#include<stdexcept>
#include<cmath>

PathGenerator::PathGenerator(const MarketParameters & market_params,
                             RandGenerator & rand_gen,
                  double spot, int num_times, double expiration_time):
  market_params_(market_params), rand_generator_(rand_gen.clone()),
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
  market_params_(market_params), rand_generator_(rand_gen.clone()),
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

PathGenerator::PathGenerator(const PathGenerator & path_gen):
  market_params_(path_gen.market_params_), 
  rand_generator_(path_gen.rand_generator_->clone()),
  spot_(path_gen.spot_),
  num_times_(path_gen.num_times_),
  time_points_(path_gen.time_points_){
}

PathGenerator & PathGenerator::operator=(const PathGenerator & path_gen){
  market_params_  = path_gen.market_params_;
  rand_generator_.reset(path_gen.rand_generator_->clone());
  spot_           = path_gen.spot_;
  num_times_      = path_gen.num_times_;
  time_points_    = path_gen.time_points_;
}

std::vector<double> PathGenerator::GetOnePath(){
    std::vector<double> path_out(num_times_);

    double S_i     = spot_;

    double t_left  = 0;
    double t_right;
    for(int i = 0; i < num_times_; ++i){
        if(i>0) t_left = time_points_[i-1];
        t_right = time_points_[i];

        double int_sigma_square = market_params_.volatility_->IntegralSquare(
                                                            t_left, t_right);
        double norm_rand;
        rand_generator_->GenNormRand(norm_rand);
        S_i = S_i *( std::exp(
                  market_params_.interest_rate_->Integral(t_left, t_right) 
                - market_params_.divident_rate_->Integral(t_left, t_right)
                - 0.5 * int_sigma_square 
                             
                     + std::sqrt(int_sigma_square) * norm_rand
                             )
                    );
       path_out[i] = S_i;
    }
    return path_out;
}

std::vector<std::vector<double> > PathGenerator::GetNPaths(int num_paths){
    std::vector<std::vector<double> > paths_out(num_paths, 
                                             std::vector<double> (num_times_));

    for(int i=0; i < num_paths; ++i)
        paths_out[i] = GetOnePath();

    return paths_out;
}

std::vector<double> PathGenerator::DiscountOneStepBack(
                                            std::vector<double> current_price,
                                            int current_time_step){
    std::vector<double> previous_price (current_price);
    double t_right = time_points_[current_time_step];
    double t_left  = 0.;
    if (current_time_step > 0) t_left = time_points_[current_time_step -1];
    
    for(int i = 0; i < previous_price.size(); i++){
        previous_price[i] *= std::exp(
                   -market_params_.interest_rate_->Integral(t_left, t_right)
                                     );
    }

    return previous_price;
}
