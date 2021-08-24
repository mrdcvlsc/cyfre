#include <iostream>
#include "../cyfre.hpp"

int main()
{
    cyfre::mat<int> mat_object(cyfre::TYPE::SCALARMATRIX,3,7);

    cyfre::mat<int> scalars({
        {7,0,0},
        {0,7,0},
        {0,0,7}
    });

    if(mat_object!=scalars) throw std::logic_error("wrong identity construct");

    std::cout<<"test 2 correct\n";

    return 0;
}