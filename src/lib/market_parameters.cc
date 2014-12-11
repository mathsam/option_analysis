#include"market_parameters.h"

MarketParameters::MarketParameters(MarketParameters & orig_params){
    volatility_    = orig_params.volatility_->clone();
    interest_rate_ = orig_params.interest_rate_->clone();
    divident_rate_ = orig_params.divident_rate_->clone();
}

MarketParameters & MarketParameters:: operator=(const MarketParameters & 
                                                orig_params){
    if (this != & orig_params){
        delete volatility_;
        delete interest_rate_;
        delete divident_rate_;
        volatility_    = orig_params.volatility_->clone();
        interest_rate_ = orig_params.interest_rate_->clone();
        divident_rate_ = orig_params.divident_rate_->clone();
    }

    return (*this);
}

MarketParameters :: ~MarketParameters(){
    delete volatility_;
    delete interest_rate_;
    delete divident_rate_;
}
