#ifndef _PATH_GENERATION_
#define _PATH_GENERATION_
#include"rand_generator.h"
#include"market_parameters.h"
#include<vector>

class PathGenerator{
public:
    /** 
     * @brief generate geometric brownian motion at equally spaced
     *        times
     *
     * The browian motion is time series S0, S1, ... Sn. S0 is at time
     * zero, and is equal to spot. n is num_times. Sn is at the 
     * expiration_time.
     * The times are (1/N, 2/N, ..., 1) * expiration_time, where N is
     * num_times.
     * @param params_in contains volatility and interest rate
     * @param rand_gen random number generator
     * @param spot  spot price at time 0
     * @param num_times number of points for the generated path
     * @param expiration_time how long does it expire from now (time 0)
    */
    PathGenerator(const MarketParameters & market_params, 
                  RandGenerator & rand_gen,
                  double spot, int num_times, double expiration_time);

    /**
     * @brief generate path at times specified by time_points
     *
     * similar to the constructor above, but can generate path at unequally
     * spaced times
    */
    PathGenerator(const MarketParameters & market_parms, 
                  RandGenerator & rand_gen, 
                  double spot, const std::vector<double> & time_points);

    void GetOnePath(std::vector<double> & path_out);

    void GetNPaths(std::vector<std::vector<double> > & paths_out);

    inline std::vector<double> get_time_points(){
        return time_points_;
    }

private:
    const MarketParameters & market_params_;
    RandGenerator & rand_generator_;
    double spot_;
    double num_times_;
    std::vector<double> time_points_;
};

#endif //_PATH_GENERATION_
