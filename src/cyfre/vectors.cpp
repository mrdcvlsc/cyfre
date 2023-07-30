#ifndef MRDCVLSC_CYFRE_VECTORS_CPP
#define MRDCVLSC_CYFRE_VECTORS_CPP

#include "../../include/cyfre/vectors.hpp"

namespace cyfre {

  template <concepts::scalars T, typename Dim, axis_t Axis, order_t Order, typename Blas>
  constexpr vec<T, Dim, Axis, Order, Blas>::vec()
      : mat<T, typename VecOrient<Dim, Axis>::OrientDim, Order, Blas>(
          VecOrient<Dim, Axis>::rows, VecOrient<Dim, Axis>::cols
        ) {}

  template <concepts::scalars T, typename Dim, axis_t Axis, order_t Order, typename Blas>
  vec<T, Dim, Axis, Order, Blas>::vec(size_t n) : mat<T, typename VecOrient<Dim, Axis>::OrientDim, Order, Blas>() {
    if constexpr (Axis == axis_t::x) {
      this->resize(1, n);
    } else {
      this->resize(n, 1);
    }
  }

  template <concepts::scalars T, typename Dim, axis_t Axis, order_t Order, typename Blas>
  constexpr vec<T, Dim, Axis, Order, Blas>::vec(std::initializer_list<T> sequence)
      : mat<T, typename VecOrient<Dim, Axis>::OrientDim, Order, Blas>() {
    if (sequence.size() > this->rows() * this->cols()) {
      throw std::invalid_argument("initializer list total elements should be <= vector size");
    }

    if (sequence.size() <= 1) {
      throw std::invalid_argument("initializer list total elements should be > 1");
    }

    if constexpr (Dim::Axis == axis_t::x) {
      size_t j = 0;
      for (auto e: sequence) {
        this->operator()(0, j++) = e;
      }
    } else {
      size_t i = 0;
      for (auto e: sequence) {
        this->operator()(i++, 0) = e;
      }
    }
  }

  /// @returns true if the matrix is equal, false otherwise.
  template <concepts::scalars T, typename Dim, axis_t Axis, order_t Order, typename Blas>
  constexpr bool vec<T, Dim, Axis, Order, Blas>::operator==(vec const &that) const {
    return mat<T, typename VecOrient<Dim, Axis>::OrientDim, Order, Blas>::operator==(that);
  }

  /// @returns true if the matrix is equal, false otherwise.
  template <concepts::scalars T, typename Dim, axis_t Axis, order_t Order, typename Blas>
  template <concepts::matrices Matrix>
  constexpr bool vec<T, Dim, Axis, Order, Blas>::operator==(Matrix const &that) const {
    return mat<T, typename VecOrient<Dim, Axis>::OrientDim, Order, Blas>::operator==(that);
  }

  template <concepts::scalars T, typename Dim, axis_t Axis, order_t Order, typename Blas>
  constexpr size_t vec<T, Dim, Axis, Order, Blas>::size() const {
    return this->rows() * this->cols();
  }
} // namespace cyfre

#endif