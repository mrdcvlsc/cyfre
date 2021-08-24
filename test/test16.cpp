#include <iostream>
#include "../cyfre.hpp"

int main()
{
    cyfre::mat<int> A({{2,4,6},
                   {8,2,4}});

    cyfre::mat<int> B({{1,4,3},
                    {2,2,1}});

    cyfre::mat<int> C = cyfre::hadamard(A,B);

    cyfre::mat<int> correct({
        {2,16,18},
        {16, 4, 4}
    });

    std::cout<<"a = \n";
    cyfre::display(C);

    std::cout<<"\n\nb = \n";
    cyfre::display(correct);

    if(C!=correct) throw std::logic_error("wrong identity construct");

    std::cout<<"test 16 correct\n";

    return 0;
}