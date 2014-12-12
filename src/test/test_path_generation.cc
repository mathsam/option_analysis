#include"path_generation.h"
#include"market_parameters.h"
#include"park_miller_rand.h"
#include"rand_generator.h"
#include<vector>
#include<iostream>

int main(){
    const int kPathLength = 50;
    const int kNumPaths   = 50;
    double spot = 10;
    int num_times = kPathLength;
    double expiration_time = 1;

    ParkMillerRand rand_gen(1); 

//    ConstParameter volatility(0.1);
//    ConstParameter interest_rate(0.04);
//    ConstParameter divident_rate(0.0);
//    MarketParameters market_params(volatility,
//                                   interest_rate,
//                                   divident_rate);

    MarketParameters market_params(ConstParameter(0.1),
                                   ConstParameter(0.0),
                                   ConstParameter(0.0));
    PathGenerator my_path_gen(market_params,
                              rand_gen,
                              spot, num_times, expiration_time);

    PathGenerator my_path_gen1(my_path_gen);
    my_path_gen1 = my_path_gen;

    std::vector<double> bs_path(kPathLength);

    std::cout.precision(5);
    std::cout << std::fixed;
    for(int j = 0; j < kNumPaths; ++j){
        my_path_gen.GetOnePath(bs_path);
        for(int i = 0; i < bs_path.size(); ++i){
            std::cout << bs_path[i] << '\t';
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}
