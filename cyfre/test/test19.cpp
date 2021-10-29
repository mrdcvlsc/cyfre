#include <iostream>
#include "../cyfre.hpp"

int square(int x) { return x*x; }


int main()
{
    cyfre::mat<int> X({
        {1,2,3,4},
        {5,6,7,8},
    });

    X.transpose();

    cyfre::mat<int> correct({
        {1,5},
        {2,6},
        {3,7},
        {4,8}
    });

    if(X!=correct) throw std::logic_error("wrong identity construct");

    std::cout<<"test 19 correct\n";

    return 0;
}