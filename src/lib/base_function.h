#ifndef _BASE_FUNCTION_H_
#define _BASE_FUNCTION_H_
#include<cmath>

/**
 * @brief common interface for base functions to fit 1d function
 *
 * The base functions can be polynomials, Fourier series, etc. They can be
 * ordered by an integer n.
 */
class BaseFunction{
public:
    /// initialize base function with a certain order n
    BaseFunction(int n):
      order_(n){};

    ///evaulate value at x
    virtual double operator()(double x) const = 0;

    virtual BaseFunction* clone() const = 0;

protected:
    int order_;
};

/**
 * @brief callable polynomial base funtions, i.e., 1, x, x^2, x^3, ...
 */
class Polynomial: public BaseFunction{
public:
    ///initialize a polynomial with order n, that is x^n
    Polynomial(int n): BaseFunction(n){};

    Polynomial(const Polynomial & poly):
      BaseFunction(poly.order_){};

    Polynomial & operator=(const Polynomial & poly){
        order_ = poly.order_;
        return (*this);
    }

    inline double operator()(double x) const{
        return std::pow(x,order_);
    } 

    BaseFunction* clone() const{
        return new Polynomial (*this);
    } 
};

/**
 *@brief optimized verison of polynomial base functions, i.e., 1, x, x^2, ...
 */
class PolynomialOpt: public BaseFunction{
public:
    PolynomialOpt(int n): BaseFunction(n){};

    PolynomialOpt(const PolynomialOpt & poly):
      BaseFunction(poly.order_){};

    PolynomialOpt & operator=(const PolynomialOpt & poly){
        order_ = poly.order_;
        return (*this);
    }

    inline double operator()(double x) const{
       static double last_x_       = 0.; ///< x calculated last time
       static int last_order_      = 1; ///< order calculated last time
       static double last_value_   = 0.; ///< last_x_^last_order_ 
       if (order_ == 0){
           last_x_ = x;
           last_order_ = 0;
           last_value_ = 1.;
           return 1.;
       }

       if (x==last_x_ && order_ == last_order_+1){
            last_order_++;
            last_value_ = last_value_*x;
            return last_value_;
        }
       
        last_x_ = x;
        last_order_ = order_;
        last_value_      = std::pow(x,order_); 
        return last_value_; 
    }

    BaseFunction* clone() const{
        return new PolynomialOpt (*this);
    }
};

#endif //_BASE_FUNCTION_H_
