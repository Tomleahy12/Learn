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
    //constructor list
    D2array();
    D2array(int row, int col);
    D2array(int row, int col,const T data_array[],bool pivoted = false);
    D2array(int row, int col, int width, const T data_array[],bool pivoted = false);
    //copy constructor
    D2array(const D2array<T> & other);
    //destructor
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
//////// Class Function Declarations /////////////////////////////////////////////////////////////////////////
// specal functions: Innerproduct, get row, get column
template <class T> 
void D2array<T>::swap(int arg1, int arg2){
    if (arg2 < arg1){
        int temp = arg2; 
        arg2 = arg1;
        arg1 = temp; 
    }
    for (int i = 0; i < col; i++) {
        T temp = d2array[arg1*col + i];
        d2array[arg1*col + i] = d2array[arg2 * col+ i];
        d2array[arg2*col + i] = temp;
    }
}
template <class T> 
D2array<T> D2array<T>::get_column(const int input_col){
    D2array<T> column(row, 1);
    for(int i = 0; i < row; i++){
            column[i]= d2array[input_col + i *(col)];
    }
    return column;
}
template<class T>
D2array<T> D2array<T>::get_row(const int input_row){
    D2array<T> row(1, col);
    for(int i =  0; i < col; i++){
        row[i] = d2array[input_row * col + i];
    }
    return row; 
}
//destructor
template <class T>
D2array<T>::~D2array(){
        delete[] d2array;
    }
// Constructors defined
template<class T>
D2array<T>::D2array(): row(row), col(col), d2array(nullptr){}
template<class T>
D2array<T>::D2array(int row, int col): row(row), col(col){
        d2array = new T[row * col]; 
        std::fill(d2array, d2array + (row * col),0);
}
template<class T>
D2array<T>::D2array(int row, int col, const T data_array[], bool piv):row(row), col(col), pivoted(piv){
    d2array = new T[row*col]; 
    for(int i =0; i<row*col; i++){
        d2array[i] = data_array[i];
    }
}
template<class T>
D2array<T>::D2array(int row, int col, int width, const T data_array[],bool piv):row(row), col(col), pivoted(piv){
    d2array = new T[row*col*width]; 
    for(int i =0; i<row*col*width; i++){
        d2array[i] = data_array[i];
    }
}
template<class T>
D2array<T>::D2array(const D2array<T> & other){
    T* d2array_copy = new T[other.row * other.col];
    std::copy(other.d2array, other.d2array + (other.row * other.col), d2array_copy);
    this->col = other.col;
    this->row = other.row; 
    this->pivoted = other.pivoted;
    this->d2array = d2array_copy;
}

// Operator Overloads defined: 
template<class T> 
D2array<T> D2array<T>::operator =(const D2array<T>& d2array){
    if(this!=&d2array){
        T* d2array_copy = new T[d2array.row * d2array.col];
        std::copy(d2array.d2array, d2array.d2array + (d2array.row * d2array.col), d2array_copy);
        this->row = d2array.row;
        this->col = d2array.col;
        this->pivoted = pivoted;
        this->d2array = d2array_copy;
    }
    return *this;
}
template<class T>
T& D2array<T>::operator[](const int index){
    return d2array[index];
}
template <class T>
const T& D2array<T>::operator[](const int index) const {
    return d2array[index];
}
 template<class T> 
 D2array<T> operator +(const D2array<T>& d2array1,const D2array<T>& d2array2){
    if(d2array1.row!=d2array2.row ^ d2array1.col!=d2array2.col){
        throw std::invalid_argument("*** dimensionality error. Expected [m x n] * [n x m]");
    }
    D2array<T> d2array(d2array1.row,d2array1.col);
    for(int i = 0; i<d2array1.row*d2array1.col; i++){
        d2array[i] = d2array1[i]+d2array2[i]; 
    }
    return d2array;
 }
 template<class T> 
 D2array<T> operator -(const D2array<T>&d2array1,const D2array<T>& d2array2){
    if(d2array1.row!=d2array2.row ^ d2array1.col!=d2array2.col){
        throw std::invalid_argument("*** dimensionality error. Expected [m x n] * [n x m]");
    }
    D2array<T> out_d2array(d2array1.row, d2array1.col);
    for(int i = 0; i<d2array1.row*d2array1.col; i++){
        out_d2array[i] = d2array1[i] - d2array2[i]; 
    }
    return out_d2array;
 }
 template<class T> 
 D2array<T> operator *(const D2array<T>& d2array1,const D2array<T>& d2array2){
    if(d2array1.col!=d2array2.row ^ d2array1.row!=d2array2.col){
        throw std::invalid_argument("*** dimensionality error. Expected [m x n] * [n x m]");
    }
    D2array<T> d2array(d2array1.row, d2array2.col); 
	for(int i =0; i <d2array1.row; i++){
		for (int j = 0; j<d2array2.col; j++){
            for(int k = 0; k<d2array2.row; k++){
			d2array[i * d2array.col + j] += d2array1[i * d2array.col + k] * d2array2[k * d2array2.col + j];
            }
        }
    }
    return d2array;
 }
 template<class T> 
 D2array<T> operator *(const D2array<T>& d2array,T vector[]){
    D2array<T> new_vector(sizeof(vector)/sizeof(vector[0], 1, vector)); delete[] vector;
    if(&d2array.col!= vector.row){
        throw std::invalid_argument("*** dimensionality error.expected [m x n] * [n x 1]");
    }
    D2array<T> new_d2array(d2array.row,1);
    for(int j = 0; j<d2array.col; j++){
        for(int i = 0; i<d2array.row; i++){
            new_d2array[(i * d2array.row) + j] += d2array[(i * d2array.row) + j] * new_vector[i]; 
		}
	}
    return new_d2array;
 }
 template<class T> 
 D2array<T> operator *(const D2array<T>& d2array,T &scalar){
    D2array<T> new_d2array(d2array.row, d2array.col);
    for(int i = 0; i <d2array.row*d2array.col; i++){
        new_d2array[i] = scalar * d2array[i];
    }
    return new_d2array; 
 }
 //detached from class
 template <class T> 
 D2array<T> transpose(const D2array<T> &d2array){
    D2array<T> d2array_t(d2array.col, d2array.row);
    for(int i =0; i<d2array.col; i++){
         for (int j = 0; j < d2array.col; j++) {
            d2array_t.d2array[j * d2array.row + i] = d2array.ndarray[i * d2array.col + j];
        }
    }  
    
    return d2array_t; 
 }
template <class T> 
void D2array<T>::transpose(){
    for(int i =0; i<col; i++){
        for (int j = 0; j < col; j++) {
            d2array[j *row + i] = d2array[i * col + j];
        }
    }
 } 
// Other Functions
 template <class T> 
 void D2array<T>::print(){
    for(int i =  0; i < row; i++){
        std::cout<<'\n';
        for(int j =  0; j < col; j++){
            std::cout<< d2array[i * col + j]<<"\t";
            }
        }
    std::cout<<'\n'; 
}
// needs fixing
template<class T>
void D2array<T>::partial_pivot(){
	if(row != col){
		throw std::invalid_argument("*** non square input for reduction.");
	}
	for(int i = 0; i < col; i++){
		D2array<T> col = get_column(i);
        T max_abs = std::abs(col[0]);
		for(int j = i+1; j<row; j++){
            if(std::abs(col[j]) > max_abs){
                max_abs = std::abs(col[j]);
                if(j!=i){
                    this->swap(i,j); 
                    }
            }
		}
	}
    pivoted = true;
}

template <class T> 
D2array<T> D2array<T>::d2_identity(int dimensions){ 
	D2array<T> identity(dimensions,dimensions); 
	for(int i =0; i<dimensions; i++){
		identity[i * dimensions + i] = 1;
	}
	return identity;
}

template <class T>
void D2array<T>::row_subtract(int arg1, int arg2){
	// takes the first argument row away from the 2nd argument row
	for(int i =0; i<d2array.col; i++){
		d2array[arg2 * d2array.col + i] = d2array[arg2 * d2array.col + i] - d2array[arg1 * d2array.col + i];
	}
}
#endif