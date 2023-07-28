/**
 *  @file   matrix.hpp
 *  @brief  Cyfre Matrix Class
 *  @author mrdcvlsc
 ***********************************************/

#ifndef MRDCVLSC_MATRIX_CLASS_HPP
#define MRDCVLSC_MATRIX_CLASS_HPP

#include <stddef.h>
#include <utility>

#include "enums.hpp"
#include "cyfre_concepts.hpp"
#include "heap_alloc.hpp"
#include "stack_alloc.hpp"

namespace cyfre {

  /// @brief matrix calss.
  /// @tparam T the type of the scalar values/elements.
  /// @tparam dim dimension allocator of the matrix, this template argument
  /// will decide whether the matrix will be fixed (stack allocated) or dynamic (heap allocated).
  /// @tparam maj_t the major order layout of the matrix, row_major or col_major.
  template <concepts::scalars T, typename Dim, order_t Order = order_t::row_major>
  class mat {
    public:

    /// @brief Fixed size stack allocation constructor.
    constexpr mat();

    /// @brief Dynamic size heap allocation constructor.
    mat(size_t rows, size_t cols);

    /// @brief Copy Constructor.
    constexpr mat(const mat &);

    /// @brief Move Constructor.
    mat(mat &&);

    /// @brief Copy Assignment.
    mat &operator=(const mat &);

    /// @brief Move Assignment.
    mat &operator=(mat &&);

    /// @returns Number of rows in the matrix.
    constexpr size_t rows() const;

    /// @returns Number of columns in the matrix.
    constexpr size_t cols() const;

    /// @brief Fill the matrix with the given value.
    constexpr void fill(T value);

    constexpr T &operator()(size_t i, size_t j);
    constexpr const T &operator()(size_t i, size_t j) const;

    /// @returns true if the matrix is equal, false otherwise.
    template <concepts::matrices Matrix>
    constexpr bool operator==(Matrix const &) const;

    private:

    using ScalarType = T;
    using AllocatorType = Dim;
    static constexpr order_t MajorOrder = Order;

    /// @brief allocated matrix.
    typename Dim::template allocate<T, Dim::rows, Dim::cols> matrix;
  };

  template <typename T, order_t maj_t = order_t::row_major>
  auto identity_dynamic(size_t side_n) {
    return std::move(mat<T, dynamic, maj_t>(side_n, side_n));
  }

  template <typename T, size_t side_n, order_t maj_t = order_t::row_major>
  auto identity_fixed() {
    return std::move(mat<T, fixed<side_n, side_n>, maj_t>(side_n, side_n));
  }

} // namespace cyfre

#endif