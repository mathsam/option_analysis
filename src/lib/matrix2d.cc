#include"matrix2d.h"
#include<stdexcept>
#include<utility>
#include<iomanip>
#include<cmath>

Matrix2d::Matrix2d(int num_rows, int num_colmns, double init_val):
  num_rows_(num_rows), num_columns_(num_colmns),
  array2d_(num_rows, std::vector<double>(num_colmns, init_val)),
  LU_if_updated_(false)
{
}

Matrix2d::Matrix2d(const std::vector<std::vector<double> > & array_in):
  num_rows_(array_in.size()), num_columns_(array_in[0].size()),
  array2d_(array_in),
  LU_if_updated_(false)
{
    for (auto it = array_in.begin()+1; it != array_in.end(); it++){
        if (it->size() != num_columns_)
            throw std::invalid_argument("rows are not of the same size"); 
    }
}

Matrix2d::Matrix2d(std::vector<std::vector<double> >&& array_in):
  num_rows_(array_in.size()), num_columns_(array_in[0].size()),
  array2d_(std::move(array_in)),
  LU_if_updated_(false)
{
    for (auto it = array_in.begin()+1; it != array_in.end(); it++){
        if (it->size() != num_columns_)
            throw std::invalid_argument("rows are not of the same size");  
    }
}

Matrix2d::Matrix2d(const std::vector<double> & array_in):
  num_rows_(array_in.size()), num_columns_(1),
  array2d_(array_in.size(), std::vector<double> (1)),
  LU_if_updated_(false)
{
    for(int i = 0; i < num_rows_; i++)
        array2d_[i][0] = array_in[i];
}

Matrix2d::Matrix2d(const Matrix2d& matrix_in):
  num_rows_(matrix_in.num_rows_), num_columns_(matrix_in.num_columns_),
  array2d_(matrix_in.array2d_),
  LU_matrix_(matrix_in.LU_matrix_),
  permutation_(matrix_in.permutation_),
  LU_if_updated_(matrix_in.LU_if_updated_),
  det_(matrix_in.det_)
{
}

Matrix2d::Matrix2d(Matrix2d& matrix_in):
  num_rows_(matrix_in.num_rows_), num_columns_(matrix_in.num_columns_),
  array2d_(matrix_in.array2d_),
  LU_matrix_(matrix_in.LU_matrix_),
  permutation_(matrix_in.permutation_),
  LU_if_updated_(matrix_in.LU_if_updated_),
  det_(matrix_in.det_)
{
}

Matrix2d::Matrix2d(Matrix2d&& matrix_in):
  num_rows_(matrix_in.num_rows_), num_columns_(matrix_in.num_columns_),
  array2d_(std::move(matrix_in.array2d_)),
  LU_matrix_(std::move(matrix_in.LU_matrix_)),
  permutation_(std::move(matrix_in.permutation_)),
  LU_if_updated_(matrix_in.LU_if_updated_),
  det_(matrix_in.det_)
{
}

Matrix2d & Matrix2d::operator=(const Matrix2d & matrix_in){
    num_rows_    = matrix_in.num_rows_;
    num_columns_ = matrix_in.num_columns_;
    array2d_     = matrix_in.array2d_;
    LU_matrix_   = matrix_in.LU_matrix_;
    permutation_ = matrix_in.permutation_;
    LU_if_updated_ = matrix_in.LU_if_updated_;
    det_         = matrix_in.det_;
    return *this;
}

Matrix2d & Matrix2d::operator=(Matrix2d&& matrix_in){
    num_rows_    = matrix_in.num_rows_;
    num_columns_ = matrix_in.num_columns_;
    array2d_     = std::move(matrix_in.array2d_);
    LU_matrix_   = std::move(matrix_in.LU_matrix_);
    permutation_ = std::move(matrix_in.permutation_);
    LU_if_updated_ = matrix_in.LU_if_updated_;
    det_         = matrix_in.det_;

    return *this;
}

Matrix2d & Matrix2d::operator=(double value){
    for(int i = 0; i < num_rows_; i++){
        for(int j = 0; j < num_columns_; j++){
            array2d_[i][j] = value;
        }
    }
    LU_if_updated_ = false;
    return *this;
}

double & Matrix2d::operator()(int i_row, int j_colmn){
    return array2d_[i_row][j_colmn];
}

double Matrix2d::operator()(int i_row, int j_colmn) const{
    return array2d_[i_row][j_colmn];
}

Matrix2d Matrix2d::operator+(const Matrix2d & matrix_in){
    Matrix2d matrix_out (array2d_);
    matrix_out += matrix_in;
    return matrix_out;
}

Matrix2d & Matrix2d::operator+=(const Matrix2d & matrix_in){
    if(!check_if_same_size(*this, matrix_in) )
        throw std::invalid_argument("matrices are not of the same size \
                                     to be added");

    for(int i = 0; i < num_rows_; i++){
        for (int j = 0; j < num_columns_; j++){
            array2d_[i][j] += matrix_in.array2d_[i][j];
        }
    }
    LU_if_updated_ = false;
    return *this;
}

Matrix2d operator+(const Matrix2d & rhs, double scalar){
    Matrix2d matrix_out(rhs.array2d_);
    matrix_out += scalar;
    return matrix_out;
}

Matrix2d operator+(double scalar, const Matrix2d & rhs){
    Matrix2d matrix_out(rhs.array2d_);
    matrix_out += scalar;
    return matrix_out;
}

Matrix2d & Matrix2d::operator+=(double scalar){
    for(int i = 0; i < num_rows_; i++){
        for(int j = 0; j < num_columns_; j++){
            array2d_[i][j] += scalar;
        }
    }
    LU_if_updated_ = false;
    return *this;
}

Matrix2d Matrix2d::operator-(const Matrix2d & matrix_in){
    Matrix2d matrix_out(array2d_);
    matrix_out -= matrix_in;
    return matrix_out;
}

Matrix2d & Matrix2d::operator-=(const Matrix2d & matrix_in){
    if(!check_if_same_size(*this, matrix_in))
        throw std::invalid_argument("matrices are not of the same size \
                                     to do substraction");

    for(int i = 0; i < num_rows_; i++){
        for(int j = 0; j < num_columns_; j++){
            array2d_[i][j] -= matrix_in.array2d_[i][j];
        }
    }
    LU_if_updated_ = false;
    return *this;
}

Matrix2d operator-(const Matrix2d & rhs, double scalar){
    Matrix2d matrix_out(rhs.array2d_);
    matrix_out -= scalar;
    return matrix_out;
}

Matrix2d operator-(double scalar, const Matrix2d & rhs){
    Matrix2d matrix_out(rhs.array2d_);
    matrix_out -= scalar;
    return matrix_out;
}

Matrix2d & Matrix2d::operator-=(double scalar){
    for(int i = 0; i < num_rows_; i++){
        for(int j = 0; j < num_columns_; j++){
            array2d_[i][j] -= scalar;
        }
    }
    LU_if_updated_ = false;
    return *this;
}

Matrix2d Matrix2d::operator-(){
    Matrix2d matrix_out(*this);
    for(int i = 0; i < num_rows_; i++){
        for(int j = 0; j < num_columns_; j++){
            matrix_out.array2d_[i][j] = - matrix_out.array2d_[i][j];
        }
    }
    
    ///change the sign of U in LU decomp; no need to cal LU again
    if(LU_if_updated_){
        for(int i = 0; i < num_rows_; i++){
            for(int j = i; j < num_columns_; j++){
                LU_matrix_[i][j] = - LU_matrix_[i][j];
            }
        }
    }
    return matrix_out;
}

Matrix2d Matrix2d::operator*(const Matrix2d & matrix_in){
    Matrix2d matrix_out(array2d_);
    matrix_out *= matrix_in;
    return matrix_out;
}

Matrix2d & Matrix2d::operator*=(const Matrix2d & matrix_in){
    if(!check_if_same_size(*this, matrix_in))
        throw std::invalid_argument("matrices are not of the same size \
                                     to be multiplied");

    for(int i = 0; i < num_rows_; i++){
        for(int j = 0; j < num_columns_; j++){
            array2d_[i][j] *= matrix_in.array2d_[i][j];
        }
    }
    LU_if_updated_ = false;
    return *this;
} 

Matrix2d operator*(const Matrix2d & rhs, double scalar){
    Matrix2d matrix_out(rhs);
    matrix_out *= scalar;
    return matrix_out;
}

Matrix2d operator*(double scalar, const Matrix2d & rhs){
    Matrix2d matrix_out(rhs);
    matrix_out *= scalar;
    return matrix_out;
}

Matrix2d & Matrix2d::operator*=(double scalar){
    for(int i = 0; i < num_rows_; i++){
        for(int j = 0; j < num_columns_; j++){
            array2d_[i][j] *= scalar;
        }
    }

    /// multiply U in LU decomp. by scalar
    if(LU_if_updated_){
        for(int i = 0; i < num_rows_; i++){
            for(int j = i; j < num_columns_; j++){
                LU_matrix_[i][j] *= scalar;
            }
        }
    }
    return *this;
}

Matrix2d Matrix2d::operator/(const Matrix2d & matrix_in){
    Matrix2d matrix_out(array2d_);
    matrix_out /= matrix_in;
    return matrix_out;
}

Matrix2d & Matrix2d::operator/=(const Matrix2d & matrix_in){
    if(!check_if_same_size(*this, matrix_in))
        throw std::invalid_argument("matrices are not of the same size \
                                     to be divided"); 

    for(int i = 0; i < num_rows_; i++){
        for(int j = 0; j < num_columns_; j++){
            array2d_[i][j] /= matrix_in.array2d_[i][j];
        }
    }
    LU_if_updated_ = false;
    return *this;
}

Matrix2d operator/(const Matrix2d & rhs, double scalar){
    Matrix2d matrix_out(rhs);
    matrix_out /= scalar;
    return matrix_out;
}

Matrix2d operator/(double scalar, const Matrix2d & rhs){
    Matrix2d matrix_out(rhs);
    matrix_out /= scalar;
    return matrix_out;
}

Matrix2d & Matrix2d::operator/=(double scalar){
    if(scalar == 0)
        throw std::invalid_argument("Cannot divide by 0.0");

    for(int i = 0; i < num_rows_; i++){
        for(int j = 0; j < num_columns_; j++){
            array2d_[i][j] /= scalar;
        }
    }
    if(LU_if_updated_){
        for(int i = 0; i < num_rows_; i++){
            for(int j = i; j < num_columns_; j++){
                LU_matrix_[i][j] /= scalar;
            }
        }
    }
    return *this;
}

Matrix2d Matrix2d::dot(const Matrix2d & matrix_in){
    if(num_columns_ != matrix_in.num_rows_)
        throw std::invalid_argument("Matrices dimension doesn't match");

    Matrix2d matrix_out(num_rows_, matrix_in.num_columns_, 0.0);
    for(int i = 0; i < num_rows_; i++){
        for(int j = 0; j < matrix_in.num_columns_; j++){
            for(int k = 0; k < num_columns_; k++){
                matrix_out.array2d_[i][j] += array2d_[i][k]
                                            *matrix_in.array2d_[k][j];
            }
        }
    }

    return matrix_out;
}

Matrix2d Matrix2d::transpose(void){
    Matrix2d matrix_out (num_columns_, num_rows_);
    for(int i = 0; i < num_columns_; i++){
        for(int j = 0; j < num_rows_; j++){
            matrix_out(i,j) = array2d_[j][i];
        }
    }
    return matrix_out;
}

std::ostream & operator<<(std::ostream & os, 
                                           const Matrix2d & matrix1){
    std::ios_base::fmtflags initial_flags(os.flags());
    os << std::scientific << std::setw(5);
    for(int i = 0; i < matrix1.num_rows_; i++){
        for(int j = 0; j < matrix1.num_columns_; j++){
            os << matrix1.array2d_[i][j] << '\t';
        }
        os << '\n';
    }
    os.flags(initial_flags);
    return os;
}

/**
 * @brief solves equation A x = b
 *
 * @param rhs b on the rhs of the equation.
 *        Number of rows must equal that of A 
 *        Can have multiple columns
 * Algorithm: 
 *  A is first decomposed into A = L U
 *  then L y = b is solved, and finally
 *  U x = y is solved
 */
Matrix2d Matrix2d::left_divide(const Matrix2d & b){
    if(!LU_decompose())
        throw std::invalid_argument("left_divide: Cannot do LU decomposition");

    if(b.num_rows_ != num_rows_)
        throw std::invalid_argument("left_divide: \
                                     rhs does not match matrix dimension");

    Matrix2d rhs(b.array2d_);
    Matrix2d x(num_rows_, rhs.num_columns_);
    Matrix2d y(num_rows_, rhs.num_columns_);

    for(int i = 0; i < num_rows_; i++){
        if (permutation_[i] != i) 
            rhs.array2d_[i] = b.array2d_[permutation_[i]];
    }

    for(int j = 0; j < rhs.num_columns_; j++){
        for(int i = 0; i < num_rows_; i++){
            y.array2d_[i][j] = rhs.array2d_[i][j];
            for(int k = 0; k <= i-1; k++){
                y.array2d_[i][j] -= LU_matrix_[i][k]*y.array2d_[k][j];
            }
        }
    }

    for(int j = 0; j < rhs.num_columns_; j++){
        for(int i = num_rows_-1; i >=0; i--){
            x.array2d_[i][j] = y.array2d_[i][j];
            for(int k = i+1; k < num_rows_ ; k++){
                x.array2d_[i][j] -= LU_matrix_[i][k]*x.array2d_[k][j];
            }
            x.array2d_[i][j] /= LU_matrix_[i][i];
        }
    }
    return x;
}

double Matrix2d::det(){
    if(!LU_decompose())
        throw std::invalid_argument("Cannot evaluate determinant");

    return det_;
}

/**
 * Algorithm:
 *   For details, refer to Numerical Recipes in C by William H. Press, 
 *   Saul A. Teukolsky, et. al.
 *
 * LU decomposition:
 * \f[
 *    M=L\cdot U
 * \f]
 * where \f$ M\f$ is square matrix. \f$L\f$ is a matrix with only lower
 * elements, like
 \f[
  L=\left[\begin{array}{ccc}
  1\\
  \alpha_{21} & 1\\
  \alpha_{31} & \alpha_{23} & 1
  \end{array}\right]
 \f]
 * And \f$U\f$ is a matrix with only upper elements, like
\f[
 U=\left[\begin{array}{ccc}
\beta_{11} & \beta_{12} & \beta_{13}\\
 & \beta_{22} & \beta_{23}\\
 &  & \beta_{33}
\end{array}\right]
\f]
 *
 * Implicity pivoting:
 *   permutaion_ is initially {0, 1, 2, 3, ...}. Its elements are swapped 
 *   the same as rows in LU_matrix_
 */
bool Matrix2d::LU_decompose(double tiny){
    if (LU_if_updated_) return true;

    if (num_rows_ != num_columns_ || num_rows_ == 0) 
        return false;

    LU_matrix_ = array2d_;
    permutation_ = std::vector<int> (num_rows_);
    int num_permutation = 0;
    for(int i = 0; i < num_rows_; i++)
        permutation_[i] = i;

    /// used in implicit pivoting
    std::vector<double> rescale_ratio(num_rows_);
    for(int i = 0; i < num_rows_; i++){
        double max_this_row = std::abs(array2d_[i][0]);
        for(int j = 1; j < num_columns_; j++){
            if (std::abs(array2d_[i][j]) > max_this_row)
                max_this_row = std::abs(array2d_[i][j]);
        }
        rescale_ratio[i] = 1.0/max_this_row;
    }

    /// start LU decomposition
    for(int j = 0; j < num_columns_; j++){
        for(int i = 0; i < j; i++){
            for(int k = 0; k <= i-1; k++){
                LU_matrix_[i][j] -= LU_matrix_[i][k]*LU_matrix_[k][j];
            }
        }
        
        for(int i = j; i < num_rows_; i++){
            for(int k = 0; k <= j-1; k++){
                LU_matrix_[i][j] -= LU_matrix_[i][k]*LU_matrix_[k][j];
            }
        }

        /// find maximum pivot within rows [j, num_rows_)
        double max_pivot     = std::abs( LU_matrix_[j][j] * rescale_ratio[j] );
        int    max_pivot_row = j;
        for(int i = j+1; i < num_rows_; i++){
            double current_pivot = std::abs( LU_matrix_[i][j]*rescale_ratio[i]);
            if(current_pivot > max_pivot){
                max_pivot = current_pivot;
                max_pivot_row = i;
            }
        }

        /// swap rows
        if(max_pivot_row != j){
            LU_matrix_[j].swap(LU_matrix_[max_pivot_row]);
            std::swap(rescale_ratio[j], rescale_ratio[max_pivot_row]);
            std::swap(permutation_[j],  permutation_[max_pivot_row]);
            num_permutation++;
        }

        if(LU_matrix_[j][j] == 0.0) LU_matrix_[j][j] = tiny;

        for(int i = j+1; i < num_rows_; i++){
            LU_matrix_[i][j] /= LU_matrix_[j][j];
        }
    } /// end of LU decomposition

    /// evualuate determinant
    det_ = 1.0;
    for(int i = 0; i < num_rows_; i++)
        det_ *= LU_matrix_[i][i];
    if(num_permutation%2 == 1) det_ = - det_;

    LU_if_updated_ = true;

    return true;
}
