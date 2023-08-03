#ifndef MRDCVLSC_CYFRE_VECTORS_CPP
#define MRDCVLSC_CYFRE_VECTORS_CPP

#define CYFRE_VEC_TARGS template <concepts::scalars T, typename Dim, axis_t Axis, order_t Order, typename Blas>
#define CYFRE_VEC vec<T, Dim, Axis, Order, Blas>
#define CYFRE_VEC_MAT_CONSTRUCTOR mat<T, typename VecOrient<Dim, Axis>::OrientDim, Order, Blas>

#include "../../include/cyfre/vectors.hpp"

namespace cyfre {

  CYFRE_VEC_TARGS constexpr CYFRE_VEC::vec()
      : CYFRE_VEC_MAT_CONSTRUCTOR(VecOrient<Dim, Axis>::rows, VecOrient<Dim, Axis>::cols) {}

  CYFRE_VEC_TARGS CYFRE_VEC::vec(size_t n) : CYFRE_VEC_MAT_CONSTRUCTOR() {
    if constexpr (Axis == axis_t::x) {
      this->resize(1, n);
    } else {
      this->resize(n, 1);
    }
  }

  CYFRE_VEC_TARGS constexpr CYFRE_VEC::vec(std::initializer_list<T> sequence) : CYFRE_VEC_MAT_CONSTRUCTOR() {
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

  CYFRE_VEC_TARGS constexpr T &CYFRE_VEC::operator[](size_t i) {
    if constexpr (Axis == axis_t::x) {
      return CYFRE_VEC_MAT_CONSTRUCTOR::operator()(0, i);
    } else {
      return CYFRE_VEC_MAT_CONSTRUCTOR::operator()(i, 0);
    }
  }

  CYFRE_VEC_TARGS constexpr const T &CYFRE_VEC::operator[](size_t i) const {
    if constexpr (Axis == axis_t::x) {
      return CYFRE_VEC_MAT_CONSTRUCTOR::operator()(0, i);
    } else {
      return CYFRE_VEC_MAT_CONSTRUCTOR::operator()(i, 0);
    }
  }

  /// @returns true if the matrix is equal, false otherwise.
  CYFRE_VEC_TARGS constexpr bool CYFRE_VEC::operator==(vec const &that) const {
    return CYFRE_VEC_MAT_CONSTRUCTOR::operator==(that);
  }

  /// @returns true if the matrix is equal, false otherwise.
  CYFRE_VEC_TARGS template <concepts::matrices Matrix>
  constexpr bool CYFRE_VEC::operator==(Matrix const &that) const {
    return CYFRE_VEC_MAT_CONSTRUCTOR::operator==(that);
  }

  CYFRE_VEC_TARGS constexpr size_t CYFRE_VEC::size() const { return this->rows() * this->cols(); }
} // namespace cyfre

#endif