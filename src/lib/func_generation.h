#ifndef _FUNC_GENERATION_H_
#define _FUNC_GENERATION_H_
#include<vector>
#include"base_function.h"
#include<memory>

/**
 * @brief generate a function object (callable) from base functions with
 *        specified linear combination
 */

class FuncGenerator{
public:
    /**
     * @brief construct a function with a certain num of bases functions
     *
     * @param num_bases number of bases functionsa vector of base functions
     */
    FuncGenerator():
        num_funcs_ (0){
    }
    
    /// set coeffs_
    void set_coeffs(const std::vector<double> & coeffs);

    /// set the ith base function
    void add_base(BaseFunction * basef_ptr){
        base_funcs_.push_back(std::unique_ptr<BaseFunction> (basef_ptr));
        num_funcs_++;
    }

    /// evaulate at x
    double operator()(double x) const;

protected:
    std::vector<std::unique_ptr<BaseFunction> > base_funcs_;
    std::vector<double> coeffs_; /**< coefficients for linear combination, e.g.,
                                  * < A0 + A1*x + A2*x^2 + ...
                                  */
    int num_funcs_;
    bool  is_initialized_; ///< whether ready to evaulate

private:
    FuncGenerator(const FuncGenerator& foo):
      num_funcs_(0){};

    FuncGenerator & operator=(const FuncGenerator & foo){};
}; 

/**
 * @brief give multiple observations (x0, y0), (x1, y1), ..., use bases function
 *        to fit the functional relationship between x and y.
 *
 * Does least square fit.
 */

class FuncFit: public FuncGenerator{
public:
    FuncFit();

    /**
     * @brief Take in observation and do least square fit functional
     *        relationship between x and y.
     *
     * @param x observation for x
     * @param y observation for y
     * @return bool whether assimilation is successful
     */
    bool AssimilateObs(const std::vector<double> & x, 
                       const std::vector<double> & y);
};

#endif //_FUNC_GENERATION_H_
