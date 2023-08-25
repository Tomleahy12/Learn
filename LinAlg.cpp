#ifndef LINALG_INL
#define LINALG_INL

#include <iostream> 
#include <vector>
#include <cmath>
#include "D2array.h"
#include "LinAlg.h"
template <class T>
class D2array;
namespace LinAlg{
// functions need work to improve and fix accuracy + review of algorithms
template<class T>
D2array<T> partial_pivot(D2array<T> d2array){
	if(d2array.row != d2array.col){
		throw std::invalid_argument("*** non square input for reduction.");
	}
	D2array<T> Permutation = d2array.d2_identity(d2array.col); 
	for(int i = 0; i < d2array.col; i++){
		D2array<T> col = d2array.get_column(i);
        T max_abs = std::abs(col[0]);
		for(int j = i+1; j<d2array.row; j++){
            if(std::abs(col[j]) > max_abs){
                max_abs = std::abs(col[j]);
            if(j != i){               
                d2array.swap(i,j); 
				Permutation.swap(i,j);
                }
            }
		}
	}
    
    return Permutation;
}
// need new pivot that modifies the original function and returns permutation matrix
template <class T>
PLU<T> PLU_decomp(const D2array<T>& d2array) {
    D2array<T> upper = d2array;  // Changed variable name from d2arrayc to upper
    D2array<T> permutation_matrix = partial_pivot(upper);
    upper.partial_pivot(); 
    D2array<T> lower = upper.d2_identity(upper.row);
    for (int i = 0; i < upper.row - 1; i++) {  // Change upper.col to upper.row - 1
        for (int j = i + 1; j < upper.row; j++) {
            if(upper[i * upper.col + i] == 0){
                break;
            }
            T norm_coef = upper[j * upper.col + i] / upper[i * upper.col + i];
            lower[j * upper.col + i] = norm_coef;
            for (int r = i; r < upper.col; r++) {  // Change j to i here
                upper[j * upper.col + r] = upper[j * upper.col + r] - norm_coef * upper[i * upper.col + r];
            }
        }
    }
    PLU<T> result; 
    result.upper = upper; 
    result.lower = lower; 
    result.perm = permutation_matrix; 
    return result;
}
// Gauss needs testing.
template<class T>
D2array<T> reduce(const D2array<T> &d2array, bool ones, bool modify, bool get_lower){
        if(ones == false && modify == false){
            D2array<T> d2array_copy = d2array;
            for (int i = 0; i < d2array_copy.row - 1; i++) {  // Change upper.col to upper.row - 1
                for (int j = i + 1; j < d2array_copy.row; j++) {
                    T norm_coef = d2array_copy[j * d2array_copy.col + i] / d2array_copy[i * d2array_copy.col + i];
                    for (int r = i; r < d2array_copy.col; r++) {  // Change j to i here
                        d2array_copy[j * d2array_copy.col + r] = d2array_copy[j * d2array_copy.col + r] - norm_coef * d2array_copy[i * d2array_copy.col + r];
                    }
                }
            }
            return d2array_copy;
        }
        else if(ones == true && modify == true){
            for (int i = 0; i < d2array.row - 1; i++) {  // Change upper.col to upper.row - 1
                for (int j = i + 1; j < d2array.row; j++) {
                    T norm_coef = 1/ d2array[j * d2array.col + i];
                    for (int r = i; r < d2array.col; r++) {  // Change j to i here
                        d2array[j * d2array.col + r] = d2array[j * d2array.col + r] - norm_coef * d2array[i * d2array.col + r];
                    }
                }
            }
            return d2array; 
        }
        else if(ones == true && modify == false){
            D2array<T> d2array_copy = d2array;
            for (int i = 0; i < d2array_copy.row - 1; i++) {  // Change upper.col to upper.row - 1
                for (int j = i + 1; j < d2array_copy.row; j++) {
                    T norm_coef = d2array_copy[j * d2array_copy.col + i] / d2array_copy[i * d2array_copy.col + i];
                    for (int r = i; r < d2array_copy.col; r++) {  // Change j to i here
                        d2array_copy[j * d2array_copy.col + r] = d2array_copy[j * d2array_copy.col + r] - norm_coef * d2array_copy[i * d2array_copy.col + r];
                    }
                }
            }
            return d2array_copy;
        }
        else if(ones == true && modify == true){
            for (int i = 0; i < d2array.row - 1; i++) {  // Change upper.col to upper.row - 1
                for (int j = i + 1; j < d2array.row; j++) {
                    T norm_coef = 1/d2array[j * d2array.col + i];
                    for (int r = i; r < d2array.col; r++) {  // Change j to i here
                        d2array[j * d2array.col + r] = d2array[j * d2array.col + r] - norm_coef * d2array[i * d2array.col + r];
                    }
                }
            }
            return d2array; 
        }
    }
}
template<class T> 
D2array<T> REF(D2array<T> &d2array){
    D2array<T> out = reduce(d2array,false,false); 
}
template<class T> 
D2array<T> RREF(D2array<T> &d2array){
    D2array<T> out = reduce(d2array,true, false); 
}
#endif
