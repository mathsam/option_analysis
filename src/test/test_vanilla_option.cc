#include<iostream>
#include"vanilla_option.h"

int main(){
    ///test PayOff
    VanillaCall call1 (10.0, 1.0);

    std::cout << call1.PayOff(5.0)  << std::endl;
    std::cout << call1.PayOff(15.0) << std::endl;

    VanillaPut put1 (10.0, 1.0);

    std::cout << put1.PayOff(5.0) << std::endl;
    std::cout << put1.PayOff(15.0) << std::endl;

    ///test virtual constructor
    VanillaOption * op1 = call1.clone();
    VanillaOption * op2 = (*op1).clone();
    std::cout << (*op2).PayOff(5.0) << std::endl;
    std::cout << (*op2).PayOff(15.0)<< std::endl;
    delete op1;
    delete op2;
}
