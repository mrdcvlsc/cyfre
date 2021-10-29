#include <iostream>
#include "../cyfre.hpp"

int main()
{
    cyfre::mat<int> subject({
        {2,4},
        {6,8}
    });

    subject.scale_column(1,cyfre::SCALAR::DIV,2);

    cyfre::mat<int> correct({
        {2,2},
        {6,4}
    });

    std::cout<<"a = \n";
    cyfre::display(subject);

    std::cout<<"\n\nb = \n";
    cyfre::display(correct);

    if(subject!=correct) throw std::logic_error("wrong identity construct");

    std::cout<<"test 9 correct\n";

    return 0;
}