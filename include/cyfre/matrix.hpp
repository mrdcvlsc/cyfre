/**
 *  @file   matrix.hpp
 *  @brief  Cyfre Matrix Class
 *  @author mrdcvlsc
 ***********************************************/

#ifndef MRDCVLSC_MATRIX_CLASS_HPP
#define MRDCVLSC_MATRIX_CLASS_HPP

#include <stddef.h>
#include "enums.hpp"
#include "heap_alloc.hpp"

namespace cyfre {

  /// @brief matrix calss.
  /// @tparam T the type of the scalar values/elements.
  /// @tparam dim dimension allocator of the matrix, this template argument will decide whether the matrix will be fixed
  /// (stack) or dynamic (heap).
  template <typename T, typename dim = dynamic, mem_layout mem_layout_t = mem_layout::row_major>
  class mat {
    public:

    mat();
    mat(size_t rows, size_t cols);

    constexpr size_t rows() const;
    constexpr size_t cols() const;

    constexpr T &operator()(size_t i, size_t j);
    constexpr const T &operator()(size_t i, size_t j) const;

    private:

    using ScalarType = T;
    using AllocatorType = dim;

    /// @brief allocated matrix.
    typename dim::template allocate<T, dim::rows, dim::cols> matrix;
  };

} // namespace cyfre

#endif