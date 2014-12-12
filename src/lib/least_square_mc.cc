#include"least_square_mc.h"
#include<vector>

LeastSquareMC::LeastSquareMC(const PathGenerator & path_gen,
                             const VanillaOption & van_option,
                             const FuncFit       & func_fit):
  path_gen_(path_gen),
  option_(van_option.clone()),
  func_fit_(func_fit){
}

double LeastSquareMC::DoSimulation(double spot, int num_paths){
    path_gen_.set_spot(spot);
    std::vector<std::vector<double> > stock_paths = 
                                              path_gen_.GetNPaths(num_paths);
    int num_steps = stock_paths[0].size();
    std::vector<int> exercise_time (num_paths, num_steps-1);
    std::vector<double> excercise_price    (num_paths);
    std::vector<double> current_price      (num_paths);

    /// price at expiration date
    for(unsigned j = 0; j < num_paths; j++)
        current_price[j] = option_->PayOff(stock_paths[j].back());
    
    /// work backwards step by step
    for(int i = num_steps-2; i >=0; i--){
        std::vector<double> continuation_price = 
                             path_gen_.DiscountOneStepBack(current_price, i+1);

        std::vector<double> spot, payoff_if_continue;
        for(int j = 0; j < num_paths; j++){
            excercise_price[j] = option_->PayOff(stock_paths[j][i]);
            ///only use in the money options 
            if(excercise_price[j] > 0.0){
              spot.push_back(stock_paths[j][i]);
              payoff_if_continue.push_back(continuation_price[j]);
            }
        }

        ///build strategy whether or not excercise. func_fit_(x) gives the
        ///estimate for price if not exercise
        func_fit_.AssimilateObs(spot, payoff_if_continue);
        for(int j = 0; j < num_paths; j++){
            /// early excercise only if in money and f(S) < PayOff now
            if(excercise_price[j] > 0.0 && 
               func_fit_(stock_paths[j][i]) < excercise_price[j]){ 
                current_price[j] = excercise_price[j];
                exercise_time[j] = i;
            }
            else{
                current_price[j] = continuation_price[j];
            }
        }
    }

    current_price = path_gen_.DiscountOneStepBack(current_price, 0);

    double mean_price = 0.0;
    for(int i = 0; i < current_price.size(); i++) mean_price += current_price[i];
    mean_price = mean_price/current_price.size();
    return mean_price;
}
