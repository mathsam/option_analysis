#include<iostream>
#include"matrix2d.h"
#include<vector>

int main(){
    std::vector<std::vector<double> > array2d = 
        {{1.,  2., 4.},
         {0., -1., 5.},
         {1.5, 0., 3.}};

    Matrix2d M(array2d);
    Matrix2d b(3, 1, 1.0);

    std::cout << M << std::endl;

    Matrix2d x = M.left_divide(b);

    std::cout << x << std::endl;
}
