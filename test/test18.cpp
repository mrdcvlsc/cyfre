#include <iostream>
#include "../cyfre.hpp"

int square(int x) { return x*x; }


int main()
{
    cyfre::mat<int> X({
        {23,12,53,34,23},
        {33,77,53,90,28},
        {87,26,11,24,31},
        {84,32,73,64,26},
        {77,88,45,97,86}
    });

    X.apply(square);

    cyfre::mat<int> correct({
        { 529,  144, 2809, 1156, 529},
        {1089, 5929, 2809, 8100, 784},
        {7569,  676,  121,  576, 961},
        {7056, 1024, 5329, 4096, 676},
        {5929, 7744, 2025, 9409,7396}
    });

    if(X!=correct) throw std::logic_error("wrong identity construct");

    std::cout<<"test 18 correct\n";

    return 0;
}