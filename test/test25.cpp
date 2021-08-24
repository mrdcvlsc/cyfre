#include <iostream>
#include "../cyfre.hpp"

int main()
{
    cyfre::mat<int> X({
        {1,2,3},
        {4,5,6},
        {7,8,9}
    });

    int diag_sum = X.sum();

    if(diag_sum!=45) throw std::logic_error("wrong sum");

    std::cout<<"correct sum\n";
    
    return 0;
}