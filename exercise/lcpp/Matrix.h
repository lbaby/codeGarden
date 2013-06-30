#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <Array2d.h>

using std::invalid_argument;

template <class T>
class Matrix : public Array2D<T>
{
public:
        Matrix (unsigned int Rows, unsigned int Columns):
                        Array2D<T>(Rows, Columns)
        {}
        Matrix<T>  operator * (Matrix const&) const;
        Matrix<T>  operator + (Matrix const&) const;
};




template <class T>
Matrix<T>
Matrix<T>::operator * (Matrix<T> const& arg) const
{
        if (this->numberOfColumns != arg.numberOfRows)
                throw invalid_argument ("incompatible matrices");
        Matrix<T> result (this->numberOfRows, arg.numberOfColumns);
        for (unsigned int i = 0; i < this->numberOfRows; ++i) {
                for (unsigned int j = 0; j < arg.numberOfColumns; ++j) {
                        T sum = 0;
                        for (unsigned int k = 0; k < this->numberOfColumns; ++k)
                                sum += static_cast<Array2D<T> > ( *this)[i][k]
                                       * static_cast<Array2D<T> >(arg)  [k][j];
                        result [i][j] = sum;
                }
        }
        return result;
}


template <class T>
Matrix<T>
Matrix<T>::operator + (Matrix<T> const& arg) const
{
        if (this->numberOfColumns != arg.numberOfColumns
                        || this->numberOfRows != arg.numberOfRows)
                throw invalid_argument ("incompatible matrices");
        Matrix<T> result (this->numberOfRows, this->numberOfColumns);
        for (unsigned int i = 0; i < this->numberOfRows; ++i) {
                for (unsigned int j = 0; j < arg.numberOfColumns; ++j) {
                        result[i][j] = static_cast<Array2D<T> >(*this) [i][j]
                                       +  static_cast<Array2D<T> >(arg)[i][j];

                }
        }
        return result;
}

#endif
