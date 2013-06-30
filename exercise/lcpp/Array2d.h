#ifndef __ARRAY2D_H__
#define __ARRAY2D_H__

#include <Array.h>

template <class T>
class Array2D
{
protected:
        unsigned int numberOfRows;
        unsigned int numberOfColumns;
        Array<T> array;
public:
        class Row
        {
                Array2D& array2D;
                unsigned int const row;
        public:
                Row (Array2D& _array2D, unsigned int _row) :
                                array2D (_array2D), row (_row)
                {}
                T& operator [] (unsigned int column) const
                {
                        return array2D.Select (row, column);
                }
        };

        Array2D (unsigned int, unsigned int);
        T& Select (unsigned int, unsigned int);
        Row operator [] (unsigned int);
};



template <class T>
Array2D<T>::Array2D (unsigned int m, unsigned int n) :
                numberOfRows (m),
                numberOfColumns (n),
                array (m * n)
{}

template <class T>
T& Array2D<T>::Select (unsigned int i, unsigned int j)
{
        if (i >= numberOfRows)
                throw out_of_range ("invalid row");
        if (j >= numberOfColumns)
                throw out_of_range ("invalid column");
        return array [i * numberOfColumns + j];
}

template<class T>
typename Array2D<T>:: Row
Array2D<T>::operator [] (unsigned int row)
{
        return Row (*this, row);
}


#endif



