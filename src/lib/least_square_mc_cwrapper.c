/**
 * @file
 * @brief A wrapper to made least square MC callable from Python
 *
 */
#include<vector>
#include"least_square_mc.h"
#include"market_parameters.h"
#include"park_miller_rand.h"
#include"rand_generator.h"
#include"path_generation.h"
#include"vanilla_option.h"
#include"func_generation.h"
#include"base_function.h"

/**
 * @brief  Price American put option using least square Monte Carlo simulation 
 *
 * @param v volatility per annuan (or other unit, but keep it the same)
 * @param r interest rate per annum (or other unit...)
 * @param d divident rate per annum (or other unit...)
 * @param T expiration time (annum, or other unit...) 
 * @param strike strike price
 * @param spot spot price
 * @param num_paths number of brownian motion to be simulated
 * @param path_length number of discrititized excercise time 
 * @param num_bases number of base functions to be used
 * @return price of the option
 */

extern "C" __attribute__ ((visibility ("default"))) double american_put(double v,
                               double r,
                               double d,
                               double T,
                               double strike,
                               double spot,
                               int num_paths,
                               int path_length,
                               int num_bases){

    ConstParameter volatility(v);
    ConstParameter interest_rate(r);
    ConstParameter divident_rate(d);
    MarketParameters market_params(volatility,
                                   interest_rate,
                                   divident_rate);

    ParkMillerRand rand_gen(1);
    PathGenerator my_path_gen(market_params,
                              rand_gen,
                              spot, path_length, T);

    FuncFit polyfit;
    for(int i = 0; i < num_bases; i++){
        Polynomial * tmp = new Polynomial (i);
        polyfit.add_base(tmp);
    }

    VanillaPut vanilla_put(strike, T);
    LeastSquareMC my_lmc(my_path_gen, vanilla_put, polyfit);

    double price = my_lmc.DoSimulation(spot, num_paths);
    return price;
}
