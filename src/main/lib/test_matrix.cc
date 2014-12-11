#include<iostream>
#include"matrix2d.h"
#include<vector>
#include"park_miller_rand.h"

int main(){
    std::vector<std::vector<double> > array1 = 
        {{1.,  2., 4.},
         {0., -1., 5.},
         {1.5, 0., 3.}};

    Matrix2d M(array1);

    std::vector<std::vector<double> > array2 = 
                 {{2.5,   1.,    1.71},
                  {3.14,  4.7,   0.33},
                  {0.1,   -0.88, -3.2}};
    Matrix2d N(array2);
    
    std::cout << "Matrix M:\n" << M << std::endl;
    std::cout << "Matrix +,-,*,/ scalar" << std::endl;
    std::cout << M+1.0 << std::endl;
    std::cout << M-1.0 << std::endl;
    std::cout << M*2.0 << std::endl;
    std::cout << M/2.0 << std::endl;
    std::cout << -M    << std::endl;

    std::cout << "Incremental operator scalar" << std::endl;
    std::cout << (M+=1.0) << std::endl;
    std::cout << (M-=1.0) << std::endl;
    std::cout << (M*=2.0) << std::endl;
    std::cout << (M/=2.0) << std::endl;

    std::cout << "Elementwise Operations" << std::endl;
    std::cout << M+N << std::endl;
    std::cout << M-N << std::endl;
    std::cout << M*N << std::endl;
    std::cout << M/N << std::endl;

    std::cout << "Matrix Operation dot" << std::endl;
    std::cout << M.dot(N) << std::endl;

    Matrix2d b(3, 1, 1.0);
    std::cout << "Determinant = " << M.det() << std::endl;
    Matrix2d x = M.left_divide(b);
    std::cout << "Solve linear equation:" << std::endl;
    std::cout << x << std::endl;
    std::cout << (M * 2).left_divide(b) << std::endl;
    std::cout << (0.5*M).left_divide(b) << std::endl;

    
    /**
    int kMatrixSize = 1000;
    Matrix2d big_matrix(kMatrixSize, kMatrixSize, 0.0);
    b = Matrix2d (kMatrixSize, 1, 0.0); 
    ParkMillerRand rand_gen;
    for (unsigned i = 0; i < kMatrixSize; i++){
        b(i, 0) = double(i);
        for (unsigned j = 0; j < kMatrixSize; j++){
            double uni_rand;
            rand_gen.GenUniformRand(uni_rand);
            big_matrix(i,j) = uni_rand;
        }
    }

    x = big_matrix.left_divide(b);
    */
}
