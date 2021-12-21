#include <iostream>
#include "../cyfre.hpp"

int main()
{
    // test for copy constructor, move assignment and copy assignment
    
    cyfre::mat<int> A{
        {1,2,3},
        {4,5,6},
        {6,5,4}
    };
    cyfre::mat<int> B{
        {1,2,3},
        {4,5,6},
        {6,5,4}
    };
    cyfre::mat<int> C = A;
    cyfre::mat<int> D;
    D = B;
    cyfre::mat<int> E = B * A;
    cyfre::mat<int> F = B * A * E;
    cyfre::mat<int> G;
    G = F * E;
    cyfre::mat<int> H;
    H = F * G * B;
    cyfre::mat<int> Z(A*F);

    return 0;
}