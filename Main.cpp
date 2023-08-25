#include <iostream> 
#include "D2array.h"
#include "LinAlg.h"

int main(){
    float A[]={1,3,5,9,1,3,1,7,4,3,9,7,5,2,0,9};
    D2array<float> Mat_A(4,4,A); 
    LinAlg::PLU<float> Mat_PLU = LinAlg::PLU_decomp(Mat_A);
    (Mat_PLU.lower).print();
    (Mat_PLU.upper).print();
    (Mat_PLU.perm).print();
    (Mat_PLU.lower*Mat_PLU.upper).print();
}