#include <iostream> 
#include <vector> 
#include <thread>
#ifndef DEFINITIONS_H
#define DEFINITIONS_H
// base class for matrices, stored as a standard array with indexing of array[row * max_col + col];
// only implemented for 2 dimensional arrays at the moment. working on 3 dims
template <class T> 
class D2array{
public:
    int row; 
    int col;
    bool pivoted = false;
    T* d2array;
    
    D2array();
    D2array(int row, int col);
    D2array(int row, int col,const T data_array[],bool pivoted = false);
    D2array(int row, int col, int width, const T data_array[],bool pivoted = false);
    D2array(const D2array<T> & other);
    ~D2array();

    // basic operations
    D2array<T> transpose(const D2array<T> &d2array);
    void transpose();
    void print();
    D2array<T> d2_identity(int dimensions);
    void partial_pivot();
    D2array<T> get_column(const int input_col);
    D2array<T> get_row(const int input_row);

    void row_subtract(int arg1, int arg2);
    void swap(int arg1, int arg2);
    //overloads
    D2array<T> operator =(const D2array<T>& other);
    T& operator[](const int index); 
    const T& operator[](const int index) const;
    template<class U> friend D2array<U> operator +(const D2array<U>& d2array1,const D2array<U>& d2array2 );
    template<class U> friend D2array<U> operator +(const D2array<U>& d2array1,std::vector<U> &vector);

    template<class U> friend D2array<U> operator -(const D2array<U>& d2array1,const D2array<U>& d2array2 );
    template<class U> friend D2array<U> operator -(const D2array<U>& d2array1,std::vector<U> &vector);

    template<class U> friend D2array<U> operator *(const D2array<U>& d2array1,const D2array<U>& d2array2 );
    template<class U> friend D2array<U> operator *(const D2array<U>& d2array1,const T (&vector)[]);
    template<class U> friend D2array<U> operator *(const D2array<U>& d2array1, T &scalar);
 
};
#include "D2array.INL"
#endif