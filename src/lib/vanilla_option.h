#ifndef _VANILLA_OPTION_H_
#define _VANILLA_OPTION_H_

/**
 * @brief vanilla option class. Interface for call or put option with a 
 *        specified expiration date and strike.
 *
 * @note Does not specify whether it is European or American option. Can be used
 *       with either pricer.
 */

class VanillaOption{
public:

    const double strike_; ///< strike price

    const double expiration_; ///< expiration date. Unit not specified

    VanillaOption(double strike, double expiration):
      strike_(strike), expiration_(expiration) {}

    /**
     * @brief pay off for a given spot
     *
     * @param spot spot price, should be larger than 0 (>0); otherwise throw an
                   exception.
     */
    virtual double PayOff(double spot) const = 0;

    /// virtual constructor
    virtual VanillaOption* clone() = 0;
};

/**
 * @brief Vanilla call option
 */
class VanillaCall: public VanillaOption{
public:

    VanillaCall(double strike, double expiration);

    double PayOff(double spot) const;

    VanillaOption * clone();

};

/**
 * @brief Vanilla put option
 */
class VanillaPut: public VanillaOption{
public:

    VanillaPut(double strike, double expiration);

    double PayOff(double spot) const;

    VanillaOption * clone();
};


#endif //_VANILLA_OPTION_H_
