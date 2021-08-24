#include <iostream>
#include "../cyfre.hpp"

int main()
{
    cyfre::mat<int> subject({
        {1,2},
        {3,4}
    });

    subject.scale_row(0,cyfre::SCALAR::MUL,2);

    cyfre::mat<int> correct({
        {2,4},
        {3,4}
    });

    std::cout<<"a = \n";
    cyfre::display(subject);

    std::cout<<"\n\nb = \n";
    cyfre::display(correct);

    if(subject!=correct) throw std::logic_error("wrong identity construct");

    std::cout<<"test 8 correct\n";

    return 0;
}