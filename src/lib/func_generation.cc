#include"func_generation.h"
#include"matrix2d.h"
#include<stdexcept>
#include<utility>

void FuncGenerator::set_coeffs(const std::vector<double> & coeffs){
    if(coeffs.size() != num_funcs_)
        throw std::invalid_argument("Different number of base function and \
                                     coefficients");

    coeffs_ = coeffs;
    is_initialized_ = true;
}

double FuncGenerator::operator()(double x) const{
    if(!is_initialized_) 
        throw std::invalid_argument("Function not initialized yet!");

    double y = 0;
    for(unsigned i = 0; i < num_funcs_; i++){
        y += coeffs_[i] * (*base_funcs_[i]) (x);
    }
    return y;
}

FuncFit::FuncFit():
  FuncGenerator(){
}

bool FuncFit::AssimilateObs(const std::vector<double> & x, 
                            const std::vector<double> & y){
    if(x.size() != y.size() || x.size() == 0)
        return false;

    Matrix2d fx (num_funcs_, x.size() );
    for(int i = 0; i < num_funcs_; i++){
        for(int j = 0; j < x.size(); j++){
            fx(i,j) = (*base_funcs_[i]) (x[j]);
        }
    }

    Matrix2d alpha = fx.dot(fx.transpose());
   
    Matrix2d obs (y);
    std::cout << obs << std::endl;
    Matrix2d b = fx.dot(obs);

    std::cout << "fit_coeffs\n";
    Matrix2d fit_coeffs = alpha.left_divide(b);
    std::cout << fit_coeffs << std::endl;
    
    std::vector<double> tmp (num_funcs_);
    for(int i = 0; i < num_funcs_; i++) tmp[i] = fit_coeffs(i,0);

    coeffs_ = std::move(tmp);
    is_initialized_ = true;
}
