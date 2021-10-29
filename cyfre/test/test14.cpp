#include <iostream>
#include "../cyfre.hpp"

int main()
{
    cyfre::mat<int> A({{ 1, 2, 3},
                   { 4, 5, 6}});

    cyfre::mat<int> B({{-1,-2,-3},
                    {-4,-5,-6}});

    cyfre::mat<int> C = A+B;

    cyfre::mat<int> correct(2,3,0);

    std::cout<<"a = \n";
    cyfre::display(C);

    std::cout<<"\n\nb = \n";
    cyfre::display(correct);

    if(C!=correct) throw std::logic_error("wrong identity construct");

    std::cout<<"test 14 correct\n";

    return 0;
}