/**
 *  @file   matrix.hpp
 *  @brief  Cyfre Matrix Class
 *  @author mrdcvlsc
 ***********************************************/

#ifndef MRDCVLSC_MATRIX_CLASS_HPP
#define MRDCVLSC_MATRIX_CLASS_HPP

#include <algorithm>
#include <exception>
#include <iostream>
#include <utility>

#include "enums.hpp"
#include "concepts.hpp"
#include "backend/cyfre/blas.hpp"

#include "heap_alloc.hpp"
#include "stack_alloc.hpp"

namespace cyfre {

  /// @brief matrix calss.
  /// @tparam T the type of the scalar values/elements.
  /// @tparam dim dimension allocator of the matrix, this template argument
  /// will decide whether the matrix will be fixed (stack allocated) or dynamic (heap allocated).
  /// @tparam Order the major order layout of the matrix, row_major or col_major.
  template <concepts::scalars T, typename Dim, order_t Order = order_t::row_major, typename Blas = backend::cyfre_blas>
  struct mat {
    /// @brief Fixed size stack allocation constructor.
    constexpr mat();

    /// @brief Dynamic size heap allocation constructor.
    mat(size_t rows, size_t cols);

    constexpr mat(std::initializer_list<std::initializer_list<T>> sequence);

    /// @brief Copy Constructor.
    constexpr mat(const mat &);

    /// @brief Move Constructor.
    mat(mat &&);

    /// @brief Copy Assignment.
    constexpr mat &operator=(const mat &);

    /// @brief Move Assignment.
    mat &operator=(mat &&);

    /// @brief Copy Constructor For Different Types.
    template <concepts::matrices MatrixT>
    constexpr mat(const MatrixT &);

    /// @brief Move Constructor For Different Types.
    template <concepts::matrices MatrixT>
    mat(MatrixT &&);

    /// @brief Copy Assignment For Different Types.
    template <concepts::matrices MatrixT>
    constexpr mat &operator=(const MatrixT &);

    /// @brief Move Assignment For Different Types.
    template <concepts::matrices MatrixT>
    mat &operator=(MatrixT &&);

    // void *operator new(std::size_t) throw();
    // void operator delete(void *) throw();
    // void *operator new[](std::size_t) throw();
    // void operator delete[](void *) throw();

    /// @returns Number of rows in the matrix.
    constexpr size_t rows() const;

    /// @returns Number of columns in the matrix.
    constexpr size_t cols() const;

    /// @brief Fill the matrix with the given value.
    constexpr void fill(T value);

    /// @brief Print the matrix.
    void print() const;

    /// @brief Resizes the the matrix (only for dynamic).
    void resize(size_t rows, size_t cols);

    constexpr T &operator()(size_t i, size_t j);
    constexpr const T &operator()(size_t i, size_t j) const;

    /// @returns true if the matrix is equal, false otherwise.
    constexpr bool operator==(mat const &) const;

    /// @returns true if the matrix is equal, false otherwise.
    template <concepts::matrices Matrix>
    constexpr bool operator==(Matrix const &) const;

    ///////////////////////////////////////////////////////////////////////////////////////////

    constexpr mat &operator+=(T scalar);
    constexpr mat operator+(T scalar) const;

    constexpr mat &operator-=(T scalar);
    constexpr mat operator-(T scalar) const;

    constexpr mat &operator*=(T scalar);
    constexpr mat operator*(T scalar) const;

    constexpr mat &operator/=(T scalar);
    constexpr mat operator/(T scalar) const;

    ///////////////////////////////////////////////////////////////////////////////////////////

    template <concepts::matrices MatrixT>
    constexpr mat &operator+=(MatrixT const &);

    template <concepts::matrices MatrixT>
    constexpr mat operator+(MatrixT const &) const;

    template <concepts::matrices MatrixT>
    constexpr mat &operator-=(MatrixT const &);

    template <concepts::matrices MatrixT>
    constexpr mat operator-(MatrixT const &) const;

    template <concepts::matrices MatrixT>
    constexpr mat &operator*=(MatrixT const &);

    template <concepts::matrices MatrixT>
    constexpr mat operator*(MatrixT const &) const;

    template <concepts::matrices MatrixT>
    constexpr mat &operator/=(MatrixT const &);

    template <concepts::matrices MatrixT>
    constexpr mat operator/(MatrixT const &) const;

    ///////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////////////////////

    using ScalarType = T;
    using AllocatorType = Dim;
    static constexpr order_t MajorOrder = Order;

    /// @brief allocated matrix.
    typename Dim::template allocate<T, Dim::rows, Dim::cols> matrix;

    void print_mem() {
      for (size_t i = 0; i < rows() * cols(); ++i) {
        std::cout << matrix[i] << " ";
      }
      std::cout << "\n";
    }
  };
} // namespace cyfre

#endif