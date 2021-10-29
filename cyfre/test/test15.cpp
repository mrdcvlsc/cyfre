#include <iostream>
#include "../cyfre.hpp"

int main()
{
    cyfre::mat<int> A({{10, 1,33},
                   {44,50,12}});

    cyfre::mat<int> B({{ 7,19, 5},
                    { 7, 6, 5}});

    cyfre::mat<int> C = A-B;;

    cyfre::mat<int> correct({
        { 3,-18,28},
        {37, 44, 7}
    });

    std::cout<<"a = \n";
    cyfre::display(C);

    std::cout<<"\n\nb = \n";
    cyfre::display(correct);

    if(C!=correct) throw std::logic_error("wrong identity construct");

    std::cout<<"test 15 correct\n";

    return 0;
}