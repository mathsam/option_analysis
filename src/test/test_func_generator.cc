#include<vector>
#include<iostream>
#include"func_generation.h"
#include"base_function.h"

int main(){
    const int kNumBases = 3;

    FuncFit polyfit;
    for(int i = 0; i < kNumBases; i++){
        Polynomial * tmp = new Polynomial (i);
        polyfit.add_base(tmp);
    }

    std::vector<double> x = {0., 1., 2.,  3.,   4.};
    std::vector<double> y = {0., 1., 1.5, 2.,   2.2};

    polyfit.AssimilateObs(x, y);

    for(int i = -10; i < 10; i++){
        std::cout << polyfit(double(i)) << '\t';
    }
}
