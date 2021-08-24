#include <iostream>
#include "../cyfre.hpp"

int main()
{
    cyfre::mat<int> subject({
        {1,2,3},
        {4,5,6},
        {7,8,9}
    });

    subject.row_scale(5,0);

    cyfre::mat<int> correct({
        {5,10,15},
        {4, 5, 6},
        {7, 8, 9}
    });

    std::cout<<"a = \n";
    cyfre::display(subject);

    std::cout<<"\n\nb = \n";
    cyfre::display(correct);

    if(subject!=correct) throw std::logic_error("wrong identity construct");

    std::cout<<"test 6 correct\n";

    return 0;
}