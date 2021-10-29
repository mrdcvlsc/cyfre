#include <iostream>
#include "../cyfre.hpp"

int main()
{
    cyfre::mat<int> X({
        { 7,12,13},
        {14, 5,20},
        {66,42,-4}
    });

    cyfre::mat<int> W(std::vector<int>({-3,4,56}));

    cyfre::mat<int> C = W*X;

    cyfre::mat<int> correct(std::vector<int>({3731,2336,-183}));

    std::cout<<"a = \n";
    cyfre::display(C);

    std::cout<<"\n\nb = \n";
    cyfre::display(correct);

    if(C!=correct) throw std::logic_error("wrong identity construct");

    std::cout<<"test 17 correct\n";

    return 0;
}