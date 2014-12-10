#ifndef _MATRIX2D_H_
#define _MATRIX2D_H_
#include<vector>
#include<iostream>
/**
 * @brief A two dimensional matrix class indexed as M(i,j) and 
 *        provides many element-wise array operations: +, -, *, /, and 
 *        matrix operations: dot, left_divide
 * 
 * @note binary operations are returned by value. Should turn on optimization to
 *       use RVO. 
 */

class Matrix2d{
public:

    /**
     * @brief allocate space for a matrix with specified size and initialization
     *        value
     *
     * @param num_rows number of rows
     * @param num_colmns number of columns
     * @param init_val value at initilization, default is 0.0
     */
    Matrix2d(int num_rows, int num_colmns, double init_val = 0.0);

    /// initialize a matrix using vector<vector<double> >
    Matrix2d(const std::vector<std::vector<double> > & array_in);

    /// move semantics: initialize with rvalue vector<vector<double> >
    Matrix2d(std::vector<std::vector<double> > && array_in);

    /// copy constructor
    Matrix2d(const Matrix2d & matrix_in);

    /// move semantics: initialize with rvalue Matrix2d object
    Matrix2d(Matrix2d && matrix_in);

    /// copy assgiment operator
    Matrix2d & operator=(const Matrix2d & matrix_in);

    /// move semantics: assgin with rvalue Matrix2d object
    Matrix2d & operator=(Matrix2d && matrix_in);

    /// access an element in a matrix as A(i,j)
    double & operator()(int i_row, int j_colmn);

    const double & operator()(int i_row, int j_colmn) const;

    /// returns the number of rows
    inline unsigned int get_num_rows() const{
        return num_rows_;
    }

    /// return the number of column
    inline unsigned int get_num_columns() const{
        return num_columns_;
    }

    /// add two matrixes
    Matrix2d operator+(const Matrix2d & matrix_in);

    Matrix2d & operator+=(const Matrix2d & matrix_in);

    /// add a matrix with a scalar, which mean add the scaler to each element in
    /// the matrix
    Matrix2d operator+(double scaler);

    Matrix2d & operator+=(double scalar);

    /// substract two matrixes
    Matrix2d operator-(const Matrix2d & matrix_in);

    Matrix2d & operator-=(const Matrix2d & matrix_in);

    /// substract a scalar from a matrix
    Matrix2d   operator-(double scaler);

    Matrix2d & operator-=(double scalar);

    /// unary operation: returns a matrix whose every element is negative of 
    /// that in original matrix
    Matrix2d operator-();

    /**
     * @brief multiple each pair of elment in the same position in two matrixes
     *
     * lhs(i,j) = rhs1(i,j)*rhs2(i,j)
     * @note not real matrix multiplication, which is dot operation below
     */
    Matrix2d   operator*(const Matrix2d & matrix_in);

    Matrix2d & operator*=(const Matrix2d & matrix_in);

    /// multiply a matrix by a scalar
    Matrix2d   operator*(double scaler);

    Matrix2d & operator*=(double scalar);

    Matrix2d   operator/(const Matrix2d & matrix_in);

    Matrix2d & operator/=(const Matrix2d & matrix_in);

    Matrix2d   operator/(double scalar);

    Matrix2d & operator/=(double scalar);

    /**
     * @brief matrix multiplication
     *
     * lhs(i,k) = sum(rhs1(i,j)*(j,k)) over j
     */
    Matrix2d dot(const Matrix2d & matrix_in);

    /// overload insertion operator for easy display to screen
    friend std::ostream & operator<<(std::ostream & os, 
                                     const Matrix2d & matrix1);

    /**
     * @brief solve linear equation; similar to \ in Matlab
     *
     * for Ax = b, x = A.left_divide(b)
     */
    Matrix2d left_divide(Matrix2d rhs);

    /**
     * @brief return determinant of the matrix
     *
     * determinant is evaulated after LU decomposition; and whether it has
     * been evaulated is indicated by LU_if_initialized_
     * @note only works for square matrix; throw an exception is performed
             for non-square matrix
     */
    double det();

    /// check if two matrices have the same dimension
    /// returns true if of same dimension
    inline friend bool check_if_same_size(const Matrix2d & matrix1, 
                                  const Matrix2d & matrix2){
        return matrix1.num_rows_    == matrix2.num_rows_ &&
               matrix1.num_columns_ == matrix2.num_columns_;
    }


private:
    unsigned int num_rows_;
    unsigned int num_columns_;
    std::vector<std::vector<double> > array2d_;///< each row in matrix is stored
                                               ///< as a vector<double>
    std::vector<std::vector<double> > LU_matrix_; ///< stores the LU 
                                                  ///< decomposition
    std::vector<std::vector<double> > permutation_;///< stores pivoting info for
                                                   ///< LU_matrix_
    bool LU_if_updated_;///< is LU decomposition is performed; default false
    double det_; ///< is LU decomp. is performed, determinant is computed

    /**
     * @brief do LU decomposition and store L and U in LU_matrix_ and 
     *        pivoting in permutation_
     *
     * @param tiny replace pivot with tiny if pivot is 0.0 
     * @return bool, false if decomposition fail, i.e. non-square matrix;
                     true if succeeded.
     */
    bool LU_decompose(double tiny = 1e-20);
};
#endif // _MATRIX2D_H_
