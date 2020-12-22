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

    matrix_int64 matrix_int64::scalar(i64 multiplyier) const{
        vector<i64> answer = _matrix;
        size_t matrix_size = _matrix.size();
        for(size_t i=0; i<matrix_size; ++i){
            answer[i]*=multiplyier;
        }//
        return matrix_int64(width,height,answer);
    }

    size_t matrix_int64::area() const{
        return width*height;
    }

    void matrix_int64::status(string name) const{
        cout<<"Matrix : "<<name<<'\n';
        cout<<"Area : "<<this->area()<<'\n';
        cout<<"Dimensions : "<<this->height<<'x'<<this->width<<'\n';
    }


}