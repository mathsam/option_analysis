#ifndef _MARKET_PARAMETERS_
#define _MARKET_PARAMETERS_
/**
 * @brief class to manage market parameters including volatility and interest 
 *        rate
 *
 * Volatility and interest rate are generally functions of time. Their integral
 * and square integral are generally needed in simulation. Therefore, it is
 * useful to combine data and behavior (evaluating inegrals) together.
 */
class SmartParameter{
public:
    SmartParameter(){};

    /**
    * @brief get value at a give time
    
    * @param t time, default value is zero
    */
    virtual double operator()(double t=0) const = 0;

    /**
     * @brief evaluate integral at interval (time1, time2)

     * @param time1 left range of time interval
     * @param time2 right range of time interval
     */    
    virtual double Integral(double time1, double time2) const = 0;

    /** 
     * @brief evaluate integral of square
     *
     * Int(x^2)
     */
    virtual double IntegralSquare(double time1, double time2) const = 0;

    /**
     * @brief virtual constructor
    */
    virtual SmartParameter * clone() const = 0;


};

/**
 * @brief constant parameter class
 *
 * the market parameters are constant with respect to time
 */
class ConstParameter: public SmartParameter{
public:
    ConstParameter(double value) : value_(value){}

    inline double operator()(double t=0) const {
        return value_;
    }

    inline double Integral(double time1, double time2) const {
        return (time2 - time1) * value_;
    }

    inline double IntegralSquare(double time1, double time2) const {
        return (time2 - time1) * value_ * value_;
    }

    inline SmartParameter * clone() const {
        return new ConstParameter(*this);
    }

private:
    double value_;
}; 


/**
 * @brief a class that combines market parameters together
 *
 * In this work this class essentially contains just volatility and interest
 * rate.
 */
class MarketParameters{
public:
    MarketParameters(const SmartParameter & sigma, 
                     const SmartParameter & r,
                     const SmartParameter & d):
      volatility_(sigma.clone()), 
      interest_rate_(r.clone()),
      divident_rate_(d.clone()){};

    SmartParameter * volatility_;

    SmartParameter * interest_rate_;

    SmartParameter * divident_rate_;

    ~MarketParameters();

    MarketParameters(MarketParameters & orig_params);

    MarketParameters & operator=(const MarketParameters & orig_params);
};

#endif // _MARKET_PARAMETERS_
