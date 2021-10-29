#include <iostream>
#include "../cyfre.hpp"

int main()
{
    cyfre::mat<int> X({
        {1,2,3,4},
        {5,6,7,8},
        {-2,3,-4,1}
    });

    X = cyfre::rref(X);

    cyfre::mat<int> correct({
        {1,0,0,-1},
        {0,1,0,1},
        {0,0,1,1}
    });

    std::cout<<"a = \n";
    cyfre::display(X);

    std::cout<<"\n\nb = \n";
    cyfre::display(correct);

    for(size_t i=0; i<3; ++i)
    {
        for(size_t j=0; j<3; ++j)
        {
            if((std::to_string(X(i,j)))!=(std::to_string(correct(i,j))))
            {
                throw std::logic_error("wrong answer inverse\n");
            }
        }
    }

    std::cout<<"test 21 correct\n";

    return 0;
}