#include<iostream>
#include<vector>
#include"least_square_mc.h"
#include"market_parameters.h"
#include"park_miller_rand.h"
#include"rand_generator.h"
#include"path_generation.h"
#include"vanilla_option.h"
#include"func_generation.h"
#include"base_function.h"

int main(){
    const int kPathLength = 50;
    const int kNumPaths   = 10000;

    double v, r, strike;
    double spot = 1.0;
#ifdef INTERACTIVE
    std::cout << "Input volatility: " ;
    std::cin >> v;
    std::cout << "Input interest rate: ";
    std::cin >> r;
    std::cout << "Input strike: ";
    std::cin >> strike;
#else
    v = 0.2; r = 0.06; strike = 40.0;
    spot = strike;
#endif
    ConstParameter volatility(v);
    ConstParameter interest_rate(r);
    ConstParameter divident_rate(0.0);
    MarketParameters market_params(volatility,
                                   interest_rate,
                                   divident_rate);

    ParkMillerRand rand_gen(1);
    double expiration_time = 1;
    PathGenerator my_path_gen(market_params,
                              rand_gen,
                              spot, kPathLength, expiration_time);

    VanillaPut vanilla_put(strike, expiration_time);

    const int kNumBases = 6;

    FuncFit polyfit;
    for(int i = 0; i < kNumBases; i++){
        PolynomialOpt * tmp = new PolynomialOpt (i);
//        Polynomial * tmp = new Polynomial (i);
        polyfit.add_base(tmp);
    }

    LeastSquareMC my_lmc(my_path_gen, vanilla_put, polyfit);

#ifdef INTERACTIVE
    while(1)
#endif
    {
#ifdef INTERACTIVE
        std::cout << "Input spot: ";
        std::cin  >> spot;
#endif
        double price = my_lmc.DoSimulation(spot, kNumPaths);

        std::cout << "Price is " << price << '\n' << std::endl;
    }
}
