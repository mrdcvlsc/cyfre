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
#include <cstring>

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

    template<typename T>
    class mat
    {   
        public:

        T* matrix = NULL;
        size_t height = 0;
        size_t width = 0;
        
        // ============================== constructors ==============================
        mat();
        mat(T one_value);
        mat(std::string text_file, char separator);
        mat(std::initializer_list<std::initializer_list<T>> matrix);
        mat(std::initializer_list<T> array_vector);
        mat(const size_t height, const size_t width, const T default_value);
        mat(const size_t height, const size_t width, const RANDOM typechoice, const T lower_bound, const T upper_bound);
        mat(const TYPE matrix_type, const size_t n, T scalar);
        mat(const TYPE matrix_type, const size_t n);
        mat(const mat& original); // copy constructor
        ~mat();

        // copy assignment
        mat& operator=(const mat& original);

        // compare matrix
        inline bool operator==(const mat& that) const;
        inline bool operator!=(const mat& that) const;

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

        template<class S>
        inline friend mat operator+(const S scalar, const mat& that);

        /// --------------------------- subtraction ---------------------------------

        /// @returns element by element subtraction - old
        inline mat operator-(const mat& that) const;
        inline void operator-=(const mat& that);

        inline mat operator-(const T scalar) const;
        inline void operator-=(const T scalar);

        template<class S>
        inline friend mat operator-(const S scalar, const mat& that);

        /// ---------------------- Division -----------------------------
        /// @returns element by element division
        inline mat operator/(const mat& that) const;
        inline void operator/=(const mat& that);

        inline mat operator/(const T scalar) const;
        inline void operator/=(const T scalar);

        template<class S>
        inline friend mat operator/(const S scalar, const mat& that);

        /// ---------------------- Multiplication -----------------------------
        /// @returns matrix multiplication / dot product
        inline mat operator*(const mat& that) const;
        inline void operator*=(const mat& that);
        inline void hadamard(const mat& that);

        /// ---------------------- Division ----------------------------------
        inline mat operator*(const T scalar) const;
        inline void operator*=(const T scalar);

        template<class S>
        inline friend mat operator*(const S scalar, const mat& that);

        /// ---------------------- comparison --------------------------------
        int compare(const mat& with) const;

        // ============================== SHAPING ==============================
        void transpose();
        void padding(size_t pad_length);
        void padding(size_t pad_height, size_t pad_width);

        // ============================== MATRIX EXPOENTIAL ==============================

        /// @returns raised matrix to a certain number 'p'
        /// @note raising to a negative integer(inverse) is not supported yet but will be in the future
        void power(size_t p);
        void inv();
        void ref();
        void rref();
        void apply(std::function<T(T)> function_name);

    };// end of mat class

    template<typename T>
    void display(const mat<T>& input);
}

#ifndef MAKE_BUILD

#include "constructors.cpp"
#include "comparison.cpp"
#include "indexing.cpp"
#include "display.cpp"
#include "assign.cpp"

#include "../matrix-elementary-operation/col_operations.cpp"
#include "../matrix-elementary-operation/row_operations.cpp"

#include "../matrix-matrix/mm_addition.cpp"
#include "../matrix-matrix/mm_subtraction.cpp"
#include "../matrix-matrix/mm_division.cpp"
#include "../matrix-matrix/mm_multiplication.cpp"
#include "../matrix-matrix/mm_hadamard.cpp"

#include "../matrix-scalar/ms_addition.cpp"
#include "../matrix-scalar/ms_subtraction.cpp"
#include "../matrix-scalar/ms_division.cpp"
#include "../matrix-scalar/ms_multiplication.cpp"

#include "../methods/determinant.cpp"
#include "../methods/minmax.cpp"
#include "../methods/sum.cpp"
#include "../methods/trace.cpp"

#include "../transform/apply.cpp"
#include "../transform/inverse.cpp"
#include "../transform/power.cpp"
#include "../transform/ref.cpp"
#include "../transform/rref.cpp"

#include "../shaping/padding.cpp"
#include "../shaping/transpose.cpp"

#endif

#endif