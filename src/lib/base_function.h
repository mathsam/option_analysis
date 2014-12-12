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


class Polynomial: public BaseFunction{
public:
    ///initialize a polynomial with order n, that is x^n
    Polynomial(int n): BaseFunction(n){};

    Polynomial(const Polynomial & poly):
      BaseFunction(poly.order_){};

    Polynomial & operator=(const Polynomial & poly){
        order_ = poly.order_;
    }

    double operator()(double x) const{
        return std::pow(x,order_);
    } 

    BaseFunction* clone() const{
        return new Polynomial (*this);
    } 
};

#endif //_BASE_FUNCTION_H_
