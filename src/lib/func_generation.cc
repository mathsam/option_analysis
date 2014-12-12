#include"func_generation.h"
#include"matrix2d.h"
#include<stdexcept>
#include<utility>

FuncGenerator::FuncGenerator(const FuncGenerator& func_gen):
  coeffs_(func_gen.coeffs_),
  num_funcs_(func_gen.num_funcs_),
  is_initialized_(func_gen.is_initialized_)
{
    for(int i = 0; i < func_gen.base_funcs_.size(); i++){
        BaseFunction * basef_ptr = (func_gen.base_funcs_[i])->clone();
        base_funcs_.push_back(std::unique_ptr<BaseFunction> (basef_ptr));
    }
} 

FuncGenerator & FuncGenerator::operator=(const FuncGenerator & func_gen){
    coeffs_    = func_gen.coeffs_;
    num_funcs_ = func_gen.num_funcs_;
    is_initialized_ = func_gen.is_initialized_;
    {
        std::vector<std::unique_ptr<BaseFunction> > tmp;
        for(int i = 0; i < func_gen.base_funcs_.size(); i++){
            BaseFunction * basef_ptr = (func_gen.base_funcs_[i])->clone();
            tmp.push_back(std::unique_ptr<BaseFunction> (basef_ptr));
        }
       base_funcs_ = std::move(tmp);
    }
}

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
    Matrix2d b = fx.dot(obs);
    Matrix2d fit_coeffs = alpha.left_divide(b);

#ifdef DEBUG
    std::cout << "fit_coeffs\n";
    std::cout << fit_coeffs << std::endl;
#endif
   
    { 
        std::vector<double> tmp (num_funcs_);
        for(int i = 0; i < num_funcs_; i++) tmp[i] = fit_coeffs(i,0);

        coeffs_ = std::move(tmp); ///tmp is destroyed and its space is
                                  ///transfered to coeffs_
    }
    is_initialized_ = true;

    return true;
}
