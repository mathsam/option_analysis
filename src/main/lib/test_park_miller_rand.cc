#include<iostream>
#include"park_miller_rand.h"

using namespace std;

int main(){
    int seed;
    cout << "Input seed" << endl;
    cin >> seed;
    ParkMillerOneRand myrand(seed); 
    int onerand;
    for(int i = 0; i< 1000; i++){
      onerand = (int) myrand.GetOneRandInt();
      cout << onerand << endl;}
    return 0;
}
