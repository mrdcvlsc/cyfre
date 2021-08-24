#include <iostream>
#include "../cyfre.hpp"

int main()
{
    cyfre::mat<int> mat_object(cyfre::TYPE::IDENTITY,3);

    cyfre::mat<int> idet({
        {1,0,0},
        {0,1,0},
        {0,0,1}
    });

    if(mat_object!=idet) throw std::logic_error("wrong identity construct");

    std::cout<<"test 1 correct\n";

    return 0;
}