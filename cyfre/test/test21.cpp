#include <iostream>
#include "../cyfre.hpp"

int main()
{
    cyfre::mat<long double> X({
        {23,12,53},
        {33,77,53},
        {87,26,11}
    });

    X.inv();

    cyfre::mat<long double> correct({
        {0.00196078L, -0.00460101L, 0.0127211L},
        {-0.0156863L, 0.0160925L, -0.00195709L},
        {0.0215686L, -0.00164691L, -0.00507736L}
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