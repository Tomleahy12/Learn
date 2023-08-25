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
template <class T>
PLU<T> PLU_decomp(const D2array<T>& d2array) {
    // Returns an upper triangular matrix;
    // Returns an upper triangular matrix with 1's on the main diag.
    D2array<T> upper = d2array;  // Changed variable name from d2arrayc to upper
    if (upper.pivoted != true) {
        upper.partial_pivot();
    }
    D2array<T> permutation_matrix = partial_pivot(upper);

    D2array<T> lower = upper.d2_identity(upper.row);
    for (int i = 0; i < upper.row - 1; i++) {  // Change upper.col to upper.row - 1
        for (int j = i + 1; j < upper.row; j++) {
            T norm_coef = upper[j * upper.col + i] / upper[i * upper.col + i];
            lower[j * upper.col + i] = norm_coef;
            for (int r = i; r < upper.col; r++) {  // Change j to i here
                upper[j * upper.col + r] -= norm_coef * upper[i * upper.col + r];
            }
        }
        std::cout << "\t iteration i completed:   " << i << '\n';
        std::cout << "\t Upper Matrice:" << '\n';
        upper.print();
    }

    PLU<T> result; 
    result.upper = upper; 
    result.lower = lower; 
    result.perm = permutation_matrix; 
    return result;
}

//older functions
template <class T>
D2array<T> REF(const D2array<T> &d2array) {
    // returns an upper trianglular matrix with 1's on the main diag.
    D2array<T> d2arrayc = d2array;
    if (d2arrayc.pivoted != true) {
        d2arrayc.partial_pivot();
    }
    for (int i = 0; i < d2arrayc.col; i++) {
        for (int j = i; j < d2arrayc.row; j++) {
            if (std::abs(d2arrayc[j * d2arrayc.col + i]) < 0.000005) {
                d2arrayc[j * d2arrayc.col + i] = 0;
            }
            if (d2arrayc[j * d2arrayc.col + i] == 0) {
                break;
            }
            T norm_coef = 1 / d2arrayc[j * d2arrayc.col + i];
            for (int r = 0; r < d2arrayc.col; r++) {
                d2arrayc[j * d2arrayc.row + r] *= norm_coef;
            }
        }
        for (int row = i + 1; row < d2arrayc.row; row++) {
            for (int col = 0; col < d2arrayc.col; col++) {
                d2arrayc[row * d2arrayc.col + col] -= d2arrayc[i * d2arrayc.col + col];
                if (std::abs(d2arrayc[row * d2arrayc.col + col]) < 0.000005) {
                    d2arrayc[row * d2arrayc.col + col] = 0;
                }
            }
        }
    }
    return d2arrayc;
}

template <class T>
D2array<T> RREF(D2array<T> d2array){
    if (d2array.pivoted != true) {
        d2array.partial_pivot();
    }
    for (int i = 0; i < d2array.col; i++) {
        for (int j = i; j < d2array.row; j++) {
            if (std::abs(d2array[j * d2array.col + i]) < 0.000005) {
                d2array[j * d2array.col + i] = 0;
            }
            if (d2array[j * d2array.col + i] == 0) {
                break;
            }
            T norm_coef = 1 / d2array[j * d2array.col + i];
            for (int r = 0; r < d2array.col; r++) {
                d2array[j * d2array.row + r] *= norm_coef;
            }
        }
        T break_condition = 0;
        for (int row = i + 1; row < d2array.row; row++) {
            for (int col = 0; col < d2array.col; col++) {
                d2array[row * d2array.col + col] -= d2array[i * d2array.col + col];
                break_condition += std::abs(d2array[row * d2array.col + col]);
                if (std::abs(d2array[row * d2array.col + col]) < 0.000005) {
                    d2array[row * d2array.col + col] = 0;
                }
            }   
        }
        if (break_condition == 0) {
            break;
        }
    }
    for (int i = d2array.col - 1; i >= 0; i--) {
        T break_condition = 0;
        for (int row = i - 1; row >= 0; row--) {
            T factor = d2array[row * d2array.col + i];
            for (int col = 0; col < d2array.col; col++) {
                d2array[row * d2array.col + col] -= factor * d2array[i * d2array.col + col];
                break_condition += std::abs(d2array[row * d2array.col + col]);
            }
        }
    }
    return d2array; 
}
}
#endif
