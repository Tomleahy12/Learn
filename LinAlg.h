#ifndef LINALG_H
#define LINALG_H

#include <iostream> 
#include <cmath>
#include "D2array.h"
template <class T>
class Ndarray;

namespace LinAlg{
    template <class T>
    struct PLU: public D2array<T>{
        D2array<T> upper; 
        D2array<T> lower;
        D2array<T> perm;
    };
    template<class T>
    PLU<T> reduce(const D2array<T> &d2array);
    template<class T>
    D2array<T> REF(const D2array<T> &d2array);
    template<class T>
    D2array<T> RREF(D2array<T> d2array);
}
#include "LinAlg.cpp"

#endif 
