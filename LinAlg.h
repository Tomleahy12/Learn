#ifndef LINALG_H
#define LINALG_H

#include <iostream> 
#include <cmath>
#include "D2array.h"
template <class T>
class Ndarray;

namespace LinAlg{
template<class T>
Ndarray<T> partial_pivot(Ndarray<T> ndarray);
template<class T>
Ndarray<T> REF(const Ndarray<T> &ndarray);
template<class T>
Ndarray<T> RREF(Ndarray<T> ndarray);
}
#include "LinAlg.cpp"

#endif 
