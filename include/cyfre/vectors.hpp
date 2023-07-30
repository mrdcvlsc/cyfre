#ifndef MRDCVLSC_CYFRE_VECTORS_HPP
#define MRDCVLSC_CYFRE_VECTORS_HPP

#include <initializer_list>
#include <type_traits>
#include <concepts>

#include "heap_alloc.hpp"
#include "stack_alloc.hpp"
#include "matrix.hpp"

namespace cyfre {

  template <typename Dim, axis_t Axis>
  struct VecOrient {
    static constexpr bool IsFixed = !std::is_same<Dim, dynamic>::value;
    using FixedAxisX = fixed<1, Dim::rows>;
    using FixedAxisY = fixed<Dim::rows, 1>;
    using FixedOrientation = typename std::conditional<Axis == axis_t::x, FixedAxisX, FixedAxisY>::type;
    using OrientDim = typename std::conditional<IsFixed, FixedOrientation, dynamic>::type;
    static constexpr size_t rows = (Axis == axis_t::x) ? 1 : Dim::rows;
    static constexpr size_t cols = (Axis == axis_t::x) ? Dim::rows : 1;
  };

  /// ===============================================================================================================

  /// @brief Fixed vector.
  template <
    concepts::scalars T, typename Dim, axis_t Axis, order_t Order = order_t::row_major,
    typename Blas = backend::cyfre_blas>
  struct vec : public mat<T, typename VecOrient<Dim, Axis>::OrientDim, Order, Blas> {
    constexpr vec();

    vec(size_t n);

    constexpr vec(std::initializer_list<T> sequence);

    /// @returns true if the matrix is equal, false otherwise.
    constexpr bool operator==(vec const &that) const;

    /// @returns true if the matrix is equal, false otherwise.
    template <concepts::matrices Matrix>
    constexpr bool operator==(Matrix const &that) const;

    constexpr size_t size() const;
  };
} // namespace cyfre

#endif