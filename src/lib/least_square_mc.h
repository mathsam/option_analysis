#ifndef _LEAST_SQUARE_MC_H_
#define _LEAST_SQUARE_MC_H_
#include<memory>
#include"path_generator.h"
#include"vanilla_option.h"

class LeastSquareMC{
public:

    LeastSquareMC(const PathGenerator & path_gen,
                  const VanillaOption & van_option);

    double DoSimulation(double spot, int num_paths = 100);

private:
    PathGenerator path_gen_;
    std::unique_ptr<VanillaOption> option_;
};

#endif //_LEAST_SQUARE_MC_H_
