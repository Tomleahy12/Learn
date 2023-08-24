#ifndef LINALG_INL
#define LINALG_INL

#include <iostream> 
#include <vector>
#include <cmath>
#include "D2array.h"
#include "LinAlg.h"
template <class T>
class Ndarray;
namespace LinAlg{
template <class T>
Ndarray<T> REF(const Ndarray<T> &ndarray) {
    Ndarray<T> ndarrayc=ndarray;
    if (ndarrayc.pivoted != true) {
        ndarrayc.partial_pivot();
    }
    // two sub routines within this loop: 
    // 1) normalize the leading value of the column
    for (int i = 0; i < ndarrayc.col; i++) {
        for (int j = i; j < ndarrayc.row; j++) {
            // helps with readability and removes infintensal values. 
            if (std::abs(ndarrayc[j * ndarrayc.col + i]) < 0.000005) {
                ndarrayc[j * ndarrayc.col + i] = 0;
            }
            //prevents unstable operations
            if (ndarrayc[j * ndarrayc.col + i] == 0) {
                break;
            }
            T norm_coef = 1 / ndarrayc[j * ndarrayc.col + i];
            for (int r = 0; r < ndarrayc.col; r++) {
                ndarrayc[j * ndarrayc.row + r] *= norm_coef;
            }
        }
        // 2) subtract the above column from the columns below
        T break_condition = 0;
        for (int row = i + 1; row < ndarrayc.row; row++) {
            for (int col = 0; col < ndarrayc.col; col++) {
                ndarrayc[row * ndarrayc.col + col] = ndarrayc[row * ndarrayc.col + col] - ndarrayc[i * ndarrayc.col + col];
                break_condition += std::abs(ndarrayc[row * ndarrayc.col + col]);
                // this condition is to remove infintensal values. 
                if (std::abs(ndarrayc[row * ndarrayc.col + col]) < 0.000005) {
                    ndarrayc[row * ndarrayc.col + col] = 0;
                }
            }
        }
        if (break_condition == 0) {
            break;
        }
    }
    return ndarrayc;
}
//reverse iteration needs more work done to be more correct
//needs help with number percision (1.0000e-16 should just be set to 0)
//need to fix the scalar magnitude when reverse iterating through the loop
//break condition is removed
template <class T>
Ndarray<T> RREF(Ndarray<T> ndarray){
    if(ndarray.pivoted != true){
        ndarray.partial_pivot();
    }
    for(int i = 0; i<ndarray.col; i++){
        for(int j =i; j<ndarray.row; j++){
            if (std::abs(ndarray[j * ndarray.col + i]) < 0.000005) {
                ndarray[j * ndarray.col + i] = 0;
            }
            //prevents unstable operations
            if (ndarray[j * ndarray.col + i] == 0) {
                break;
            }
            T norm_coef = 1/ndarray[j*ndarray.col + i];
            for(int r =0; r<ndarray.col; r++){
                ndarray[j * ndarray.row + r] *=norm_coef;
            }
        }
        T break_condition=0;
        for(int row=i+1; row< ndarray.row; row++){
            for(int col=0; col<ndarray.col; col++){
                ndarray[row*ndarray.col + col] = ndarray[row*ndarray.col + col] - ndarray[i*ndarray.col + col];
                break_condition+=std::abs(ndarray[row*ndarray.col + col]);
                if (std::abs(ndarray[row * ndarray.col + col]) < 0.000005) {
                    ndarray[row * ndarray.col + col] = 0;
                }
            }   
        }
        if(break_condition==0){
            break;
        }
    }
    for (int i = ndarray.col - 1; i >= 0; i--) {
    T break_condition = 0;
    for (int row = i - 1; row >= 0; row--) {
        T factor = ndarray[row * ndarray.col + i];
        for (int col = 0; col < ndarray.col; col++) {
            ndarray[row * ndarray.col + col] -= factor * ndarray[i * ndarray.col + col];
            break_condition += std::abs(ndarray[row * ndarray.col + col]);
        }
    }
}
    return ndarray; 
}
}
#endif