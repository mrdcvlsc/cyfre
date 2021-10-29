#include <iostream>
#include "../cyfre.hpp"

int main()
{
    cyfre::mat<int> subject(cyfre::TYPE::NULLZERO,3);

    cyfre::mat<int> correct({
        {0,0,0},
        {0,0,0},
        {0,0,0}
    });

    if(subject!=correct) throw std::logic_error("wrong identity construct");

    std::cout<<"test 3 correct\n";

    return 0;
}