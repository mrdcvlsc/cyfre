#ifndef CYFRE_MATRIX_CLASS
#define CYFRE_MATRIX_CLASS

#include <iostream>
#include <numeric>
#include <fstream>
#include <limits>
#include <cstdio>
#include <exception>
#include <random>
#include <functional>
#include <iterator>
#include <chrono>

#ifdef OMPTHREAD
#include <omp.h>
#endif

#include "../helpers/helper_functions.hpp"
#include "../helpers/randomizer.hpp"

/*
        CONTAINS ALL CYFRE LIBRARY TYPES from classes, to enums, and typedefs
*/

namespace cyfre
{
    #define TRANSPOSE_MT_TREASHOLD 3364000

    /// MATRIX TYPES FOR CONSTRUCTING A MATRIX
    enum TYPE
    {
        /// @arg - a square matrix where every element is '0'
        NULLZERO,
        /// @arg - a square matrix where every elements in the main diagonal has a value of '1'
        IDENTITY,
        /// @arg - a square matrix where every elements in the main diagonal has a value of a given 'N'
        SCALARMATRIX
    };

    /// enum type for random value constructor
    enum RANDOM{ INTEGER, REAL };

    /// SCALAR OPERATIONS
    enum SCALAR { ADD, SUB, MUL, DIV };

    template<class T>
    class mat
    {   
        public:

        T* matrix;
        size_t height;
        size_t width;
        
        // ============================== constructors ==============================
        mat();
        mat(T one_value);
        mat(std::string text_file, char separator);
        mat(const std::vector<std::vector<T>>& matrix);
        mat(const std::vector<T>& array_vector);
        mat(const size_t height, const size_t width, const T default_value);
        mat(const size_t height, const size_t width, const RANDOM typechoice, const T lower_bound, const T upper_bound);
        mat(const TYPE matrix_type, const size_t n, T scalar);
        mat(const TYPE matrix_type, const size_t n) : mat(matrix_type,n,0);
        mat(const mat& original);
        ~mat();

        // copy operator
        mat& operator=(const mat& original);

        // =============================== methods ===================================
        /// @returns T sum, the total sum of all the elements of the matrix
        T sum() const;
        T trace() const;

        T max();
        T min();

        void scale_row(const size_t row_index, const SCALAR scalar_operation, const T value);
        void row_operation(const size_t output_index, const SCALAR scalar_operation, size_t input_index);
        void row_swap(size_t row_a, size_t row_b);
        void row_scale(T scalar, size_t base_row);
        void row_scale(T scalar, size_t scale_row, size_t base_row);
        
        void scale_column(const size_t column_index, const SCALAR scalar_operation, const T value);
        void column_operation(const size_t output_index, const SCALAR scalar_operation, size_t input_index);
        void column_swap(size_t column_a, size_t column_b);
        void column_scale(T scalar, size_t base_column);
        void column_scale(T scalar, size_t scale_column, size_t base_column);

        // ============================== SAFE INDEXING ================================

        inline T& operator()(size_t i, size_t j);
        inline const T& operator()(size_t i, size_t j) const;

        // ============================== MATRIX OPERATIONS ==============================

        /// --------------------------- addition ---------------------------------

        /// @returns element by element addition - old
        inline mat operator+(const mat& that) const;
        inline void operator+=(const mat& that);

        inline mat operator+(const T scalar) const;
        inline void operator+=(const T scalar);
        inline friend mat operator+(const T scalar, const mat& that);

        /// --------------------------- subtraction ---------------------------------

        /// @returns element by element subtraction - old
        inline mat operator-(const mat& that) const;
        inline void operator-=(const mat& that);

        inline mat operator-(const T scalar) const;
        inline void operator-=(const T scalar);
        inline friend mat operator-(const T scalar, const mat& that);

        /// ---------------------- Division -----------------------------
        /// @returns element by element division
        inline mat operator/(const mat& that) const;
        inline void operator/=(const mat& that);

        inline mat operator/(const T scalar) const;
        inline void operator/=(const T scalar);
        inline friend mat operator/(const T scalar, const mat& that);

        /// ---------------------- Multiplication -----------------------------
        /// @returns matrix multiplication / dot product
        inline mat operator*(const mat& that) const;
        inline void operator*=(const mat& that);
        inline void hadamard(const mat& that);

        /// ---------------------- Division -----------------------------
        inline mat operator*(const T scalar) const;
        inline void operator*=(const T scalar);
        inline friend mat operator*(const T scalar, const mat& that);

        // ============================== MATRIX EXPOENTIAL ==============================

        /// @returns raised matrix to a certain number 'p'
        /// @note raising to a negative integer(inverse) is not supported yet but will be in the future
        void power(size_t p);
        void transpose();
        void inv();
        void ref();
        void rref();
        void apply(std::function<T(T)> function_name);

    };// end of mat class

    template<typename T>
    void display(const mat<T>& input);
}

#ifndef MAKE_BUILD

#endif

#endif