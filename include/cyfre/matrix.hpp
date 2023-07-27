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
#include "heap_alloc.hpp"
#include "stack_alloc.hpp"

namespace cyfre {

  /// @brief matrix calss.
  /// @tparam T the type of the scalar values/elements.
  /// @tparam dim dimension allocator of the matrix, this template argument will decide whether the matrix will be fixed
  /// (stack) or dynamic (heap).
  template <typename T, typename dim, mem_layout mem_layout_t = mem_layout::row_major>
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

    /// @returns number of rows in the matrix.
    constexpr size_t rows() const;

    /// @returns number of columns in the matrix.
    constexpr size_t cols() const;

    constexpr T &operator()(size_t i, size_t j);
    constexpr const T &operator()(size_t i, size_t j) const;

    constexpr bool operator==(mat const &) const;

    private:

    using ScalarType = T;
    using AllocatorType = dim;

    /// @brief allocated matrix.
    typename dim::template allocate<T, dim::rows, dim::cols> matrix;
  };

  template <typename T, mem_layout mem_layout_t = mem_layout::row_major>
  auto identity_dynamic(size_t side_n) {
    return std::move(mat<T, dynamic, mem_layout_t>(side_n, side_n));
  }

  template <typename T, size_t side_n, mem_layout mem_layout_t = mem_layout::row_major>
  auto identity_fixed() {
    return std::move(mat<T, fixed<side_n, side_n>, mem_layout_t>(side_n, side_n));
  }

} // namespace cyfre

#endif