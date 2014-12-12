#include"least_square_mc.h"
#include<vector>

LeastSquareMC::LeastSquareMC(const PathGenerator & path_gen,
                             const VanillaOption & van_option):
  path_gen_(path_gen),
  option_(van_option.clone()){
}

double LeastSquareMC::DoSimulation(double spot, int num_paths){
    std::vector<std::vector<double> > stock_paths = 
                                              path_gen_.GetNPaths(num_paths);
}
