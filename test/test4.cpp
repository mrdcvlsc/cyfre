#include <iostream>
#include "../cyfre.hpp"

int main()
{
    cyfre::mat<int> subject(3,2,5);

    cyfre::mat<int> correct({
        {5,5},
        {5,5},
        {5,5}
    });

    if(subject!=correct) throw std::logic_error("wrong identity construct");

    std::cout<<"test 4 correct\n";

    return 0;
}