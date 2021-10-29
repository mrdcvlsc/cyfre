#include <iostream>
#include "../cyfre.hpp"

int main()
{
    cyfre::mat<int> subject({
        {1,2,3},
        {4,5,6},
        {7,8,9}
    });

    subject.column_operation(1,cyfre::SCALAR::DIV,2);

    cyfre::mat<int> correct({
        {1, 0, 3},
        {4, 0, 6},
        {7, 0, 9}
    });

    std::cout<<"a = \n";
    cyfre::display(subject);

    std::cout<<"\n\nb = \n";
    cyfre::display(correct);

    if(subject!=correct) throw std::logic_error("wrong identity construct");

    std::cout<<"test 11 correct\n";

    return 0;
}