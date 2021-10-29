#include <iostream>
#include "../cyfre.hpp"

int main()
{
    cyfre::mat<int> X({
        {1,2,3},
        {4,5,6},
        {7,8,9}
    });

    int diag_sum = X.trace();

    if(diag_sum!=15) throw std::logic_error("wrong trace");

    std::cout<<"correct trace\n";
    
    return 0;
}