#include <iostream>
#include "../cyfre.hpp"
#include "../statistics/matrix_stats.hpp"

int main()
{

    cyfre::mat<short> X({
        {7,2,4},
        {4,7,6},
        {7,4,9}
    });

    long double mean   = cyfre::sts::mean(X);
    long double median = cyfre::sts::median(X);

    std::pair<size_t,std::vector<short>> getmode = cyfre::sts::mode(X);

    size_t numbers_of_modes  = getmode.second.size();
    size_t modes_occurrence  = getmode.first;

    std::vector<short> modes = getmode.second;

    std::cout<<"mean = "<<std::to_string(mean)<<"\n";
    std::cout<<"median = "<<std::to_string((int)(float)median)<<"\n";
    std::cout<<"numbers_of_modes = "<<numbers_of_modes<<"\n";
    std::cout<<"modes_occurence = "<<modes_occurrence<<"\n";
    std::cout<<"modes = \n";
    for(auto e: modes) std::cout<<"\t"<<e<<"\n";

    if(std::to_string(mean)!="5.555556") throw std::logic_error("wrong mean");
    if(std::to_string((int)(float)median)!="7") throw std::logic_error("wrong median");
    if(numbers_of_modes!=2) throw std::logic_error("wrong numbers_of_modes");
    if(modes_occurrence!=3) throw std::logic_error("wrong modes_occurrence");
    if(modes[0]!=4) throw std::logic_error("wrong modes[0]");
    if(modes[1]!=7) throw std::logic_error("wrong modes[1]");

    std::cout<<"mean, median modem correct outputs\n";

/*
  mean = 5.55556
  median = 7
  numbers_of_modes = 2
  modes_occurrence = 3
  modes = [7,4]
*/
    cyfre::mat<short> SSS({7,2,4,3,9});

    long double
    sum_of_square      = cyfre::sts::sofs(SSS),
    variance           = cyfre::sts::variance(SSS,cyfre::sts::SAMPLE),
    standard_deviation = cyfre::sts::stddvn(SSS,cyfre::sts::SAMPLE);

//     sum_of_square = 34
//   variance = 8.5
//   standard_deviation = 2.91548

    std::cout<<"(int)(float)sum_of_square) = "<<(int)(float)sum_of_square<<"\n";
    std::cout<<"(int)(float)variance) = "<<std::to_string((float)variance)<<"\n";
    std::cout<<"(int)(float)standard_deviation) = "<<std::to_string(standard_deviation)<<"\n";

    if(std::to_string((int)(float)sum_of_square)!="34") throw std::logic_error("wrong sum_of_square");
    if(std::to_string((float)variance)!="8.500000") throw std::logic_error("wrong variance");
    if(std::to_string((float)standard_deviation)!="2.915476") throw std::logic_error("wrong standard_deviation");
    std::cout<<"orrect otputs\n";

    return 0;
}