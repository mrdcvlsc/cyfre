#ifndef MRDCVLSC_CYFRE_SPECIALIZATION_HPP
#define MRDCVLSC_CYFRE_SPECIALIZATION_HPP

#include "matrix.hpp"

namespace cyfre {
  // IDENTITY MATRIX
  template <concepts::scalars T, size_t SideN, order_t Order = order_t::row_major, typename Blas = backend::cyfre_blas>
  struct feye : public mat<T, fixed<SideN, SideN>, Order, Blas> {
    constexpr feye() : mat<T, fixed<SideN, SideN>, Order, Blas>() {
      // this->fill(0);
      for (size_t i = 0; i < SideN; ++i) {
        this->operator()(i, i) = 1;
      }
    }

    /// @returns true if the matrix is equal, false otherwise.
    template <concepts::matrices Matrix>
    constexpr bool operator==(Matrix const &that) const {
      return mat<T, fixed<SideN, SideN>, Order, Blas>::operator==(that);
    }
  };

  template <concepts::scalars T, order_t Order = order_t::row_major, typename Blas = backend::cyfre_blas>
  struct deye : public mat<T, dynamic, Order, Blas> {
    deye(size_t side_n) : mat<T, dynamic, Order, Blas>(side_n, side_n) {
      this->fill(0);
      for (size_t i = 0; i < side_n; ++i) {
        this->operator()(i, i) = 1;
      }
    }

    /// @returns true if the matrix is equal, false otherwise.
    template <concepts::matrices Matrix>
    bool operator==(Matrix const &that) const {
      return mat<T, dynamic, Order, Blas>::operator==(that);
    }
  };
} // namespace cyfre

#endif