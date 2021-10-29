#include <iostream>
#include "../cyfre.hpp"

int main()
{
    std::cout<<"Test 27\n";
    
    cyfre::mat<int> subject1({
        {5,10,15,20},
        {30,60,2,-2},
        {7,6,5,-232}
    });

    cyfre::mat<int> target1({
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,5,10,15,20,0},
        {0,30,60,2,-2,0},
        {0,7,6,5,-232,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0}
    });

    subject1.padding(2,1);

    if(subject1!=target1) throw std::logic_error("test 27 error in padding output");

    cyfre::display(subject1);

    return 0;
}