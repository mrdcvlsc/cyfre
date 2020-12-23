#include "cyfre.h"

namespace cyfre
{
    void matrix_int64::view() const{
        for(size_t i=0; i<this->height; ++i){
            for(size_t j=0; j<this->width; ++j)
                cout<<this->operator()(i,j)<<' ';
            cout<<'\n';
        }
    }

    void matrix_int64::status(string name) const{
        cout<<"\nMatrix : "<<name<<'\n';
        cout<<"Area : "<<this->area()<<'\n';
        cout<<"Dimensions : "<<this->height<<'x'<<this->width<<"\n\n";
    }
}