#include <iostream>
#include "../cyfre.hpp"

int main()
{
    cyfre::mat<int> subject({
        {1,2,3},
        {4,5,6},
        {0,0,0}
    });

    subject.row_scale(7,0,2);

    cyfre::mat<int> correct({
        {1, 2, 3},
        {4, 5, 6},
        {7,14,21}
    });

    std::cout<<"a = \n";
    cyfre::display(subject);

    std::cout<<"\n\nb = \n";
    cyfre::display(correct);

    if(subject!=correct) throw std::logic_error("wrong identity construct");

    std::cout<<"test 7 correct\n";

    return 0;
}