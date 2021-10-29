#include <iostream>
#include "../cyfre.hpp"

int main()
{
    cyfre::mat<int> subject({
        {1,2,3},
        {4,5,6},
        {7,8,9}
    });

    subject.row_swap(1,2);

    cyfre::mat<int> correct({
        {1, 2, 3},
        {7, 8, 9},
        {4, 5, 6}
    });

    if(subject!=correct) throw std::logic_error("wrong identity construct");

    std::cout<<"test 5 correct\n";

    return 0;
}