#include <iostream>
#include "../cyfre.hpp"

int main()
{
    cyfre::mat<long double> X({
        { 5, 10,-15,  20},
        {30,-35,-40, -45},
        {55, 60, 75, -80},
    {90, 95,100,-105}
    });

    long double determinant = cyfre::det(X);

    std::cout<<determinant<<"\n";
    std::cout<<"str det ="<<std::to_string((int)(float)determinant)<<"\n";

    std::cout<<"-------------\n";
    std::cout<<"determinant = "<<std::to_string((int)(float)determinant)<<"\n";
    std::cout<<"det define  = -720000\n";
    if(std::to_string((int)(float)determinant)!="-720000") throw std::logic_error("wrong determinant");

    std::cout<<"correct determinant\n";
    
    return 0;
}