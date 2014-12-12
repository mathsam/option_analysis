#ifndef _LEAST_SQUARE_MC_H_
#define _LEAST_SQUARE_MC_H_
#include<memory>
#include"path_generation.h"
#include"vanilla_option.h"
#include"func_generation.h"

/**
 * @brief Least square Monte Carlo simulation
 *
 * Algorithm refers to "Valuing American Options by Simulation:
 * A Simple Least-Square Approach" by Longstaff and Schwartz, 2001
 */
class LeastSquareMC{
public:
    /**
     * @brief construct a LeastSquareMC object. The input objects are stored
     *        as independent clones in the LeastSquareMC object.
     *
     * @param path_gen generate geometric brownian motion
     * @param van_option Vanilla option
     * @param func_fit consists of base functions to do least square fit
     */
    LeastSquareMC(const PathGenerator & path_gen,
                  const VanillaOption & van_option,
                  const FuncFit       & func_fit);

    double DoSimulation(double spot, int num_paths = 100);

private:
    PathGenerator path_gen_;
    std::unique_ptr<VanillaOption> option_;
    FuncFit func_fit_;
};

#endif //_LEAST_SQUARE_MC_H_
