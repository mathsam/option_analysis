#include"vanilla_option.h"

VanillaCall::VanillaCall(double strike, double expiration):
  VanillaOption(strike, expiration){
}

double VanillaCall::PayOff(double spot) const{
    double K = spot - strike_;
    if(K > 0.0) return K;
    else return 0.0;
}

VanillaOption* VanillaCall::clone() const{
    return new VanillaCall (*this);
}

VanillaPut::VanillaPut(double strike, double expiration):
  VanillaOption(strike, expiration){
}

double VanillaPut::PayOff(double spot) const{
    double K = strike_ - spot;
    if(K > 0.0) return K;
    else return 0.0;
}

VanillaOption * VanillaPut::clone() const{
    return new VanillaPut (*this);
}
