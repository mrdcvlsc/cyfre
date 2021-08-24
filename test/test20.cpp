#include <iostream>
#include "../cyfre.hpp"

int main()
{
    cyfre::mat<int> X({
        { 7,12,13},
        {14, 5,20},
        {66,42,-4}
    });


    cyfre::mat<int> X_cubed = cyfre::power(X,3);
    
    cyfre::mat<int> X_squared = X;
    X_squared.power(2);

    std::cout<<"cubed = \n";
    cyfre::display(X_cubed);

    std::cout<<"\nsquared = \n";
    cyfre::display(X_squared);
    

    cyfre::mat<int> C1({
        {35599,	28068,	26659},
        {38210,	31505,	39196},
        {130302,	85590,	20042}
    });

    cyfre::mat<int> C2({
        {1075,	 690,	 279},
        {1488,	1033,	 202},
        {786,	 834,	1714}
    });

    if(X_cubed!=C1) throw std::logic_error("wrong answer on test 20 cube");
    if(X_squared!=C2) throw std::logic_error("wrong answer on test 20 square");

    std::cout<<"CORRECT ANSWERS IN TEST 20\n";

    return 0;
}