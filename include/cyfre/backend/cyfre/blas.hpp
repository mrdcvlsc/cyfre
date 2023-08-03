#ifndef MRDCVLSC_INCLUDE_CYFRE_BACKEND_CYFRE_BLAS_HPP
#define MRDCVLSC_INCLUDE_CYFRE_BACKEND_CYFRE_BLAS_HPP

#include "../../enums.hpp"
#include "../../concepts.hpp"

namespace cyfre::backend {
  /// blas backend are raw rudimentary implementation without any checks.
  struct cyfre_blas {
    template <concepts::matrices MT1, concepts::matrices MT2>
    static constexpr void add(MT1 &A, const MT2 &B) {
      constexpr bool SameColumnMajor = MT1::MajorOrder == MT2::MajorOrder && MT1::MajorOrder == order_t::col_major;
      if constexpr (!SameColumnMajor) {
        for (size_t i = 0; i < A.rows(); ++i) {
          for (size_t j = 0; j < A.cols(); ++j) {
            A(i, j) += B(i, j);
          }
        }
      } else {
        for (size_t j = 0; j < A.cols(); ++j) {
          for (size_t i = 0; i < A.rows(); ++i) {
            A(i, j) += B(i, j);
          }
        }
      }
    }

    template <bool OverWrite = true, concepts::matrices MT1, concepts::matrices MT2, concepts::matrices MT3>
    static constexpr void add(MT1 &A, const MT2 &B, const MT3 &C) {
      constexpr bool SameColumnMajor = MT1::MajorOrder == MT2::MajorOrder && MT1::MajorOrder == MT3::MajorOrder &&
                                       MT1::MajorOrder == order_t::col_major;
      if constexpr (!SameColumnMajor) {
        for (size_t i = 0; i < A.rows(); ++i) {
          for (size_t j = 0; j < A.cols(); ++j) {
            if constexpr (OverWrite) {
              A(i, j) = B(i, j) + C(i, j);
            } else {
              A(i, j) += B(i, j) + C(i, j);
            }
          }
        }
      } else {
        for (size_t j = 0; j < A.cols(); ++j) {
          for (size_t i = 0; i < A.rows(); ++i) {
            if constexpr (OverWrite) {
              A(i, j) = B(i, j) + C(i, j);
            } else {
              A(i, j) += B(i, j) + C(i, j);
            }
          }
        }
      }
    }

    template <concepts::matrices MT1, concepts::matrices MT2>
    static constexpr void sub(MT1 &A, const MT2 &B) {
      constexpr bool SameColumnMajor = MT1::MajorOrder == MT2::MajorOrder && MT1::MajorOrder == order_t::col_major;
      if constexpr (!SameColumnMajor) {
        for (size_t i = 0; i < A.rows(); ++i) {
          for (size_t j = 0; j < A.cols(); ++j) {
            A(i, j) -= B(i, j);
          }
        }
      } else {
        for (size_t j = 0; j < A.cols(); ++j) {
          for (size_t i = 0; i < A.rows(); ++i) {
            A(i, j) -= B(i, j);
          }
        }
      }
    }

    template <bool OverWrite = true, concepts::matrices MT1, concepts::matrices MT2, concepts::matrices MT3>
    static constexpr void sub(MT1 &A, const MT2 &B, const MT3 &C) {
      constexpr bool SameColumnMajor = MT1::MajorOrder == MT2::MajorOrder && MT1::MajorOrder == MT3::MajorOrder &&
                                       MT1::MajorOrder == order_t::col_major;
      if constexpr (!SameColumnMajor) {
        for (size_t i = 0; i < A.rows(); ++i) {
          for (size_t j = 0; j < A.cols(); ++j) {
            if constexpr (OverWrite) {
              A(i, j) = B(i, j) - C(i, j);
            } else {
              A(i, j) += B(i, j) - C(i, j);
            }
          }
        }
      } else {
        for (size_t j = 0; j < A.cols(); ++j) {
          for (size_t i = 0; i < A.rows(); ++i) {
            if constexpr (OverWrite) {
              A(i, j) = B(i, j) - C(i, j);
            } else {
              A(i, j) += B(i, j) - C(i, j);
            }
          }
        }
      }
    }

    template <concepts::matrices MT1, concepts::matrices MT2>
    static constexpr void mul(MT1 &A, const MT2 &B) {
      constexpr bool SameColumnMajor = MT1::MajorOrder == MT2::MajorOrder && MT1::MajorOrder == order_t::col_major;
      if constexpr (!SameColumnMajor) {
        for (size_t i = 0; i < A.rows(); ++i) {
          for (size_t j = 0; j < A.cols(); ++j) {
            A(i, j) *= B(i, j);
          }
        }
      } else {
        for (size_t j = 0; j < A.cols(); ++j) {
          for (size_t i = 0; i < A.rows(); ++i) {
            A(i, j) *= B(i, j);
          }
        }
      }
    }

    template <bool OverWrite = true, concepts::matrices MT1, concepts::matrices MT2, concepts::matrices MT3>
    static constexpr void mul(MT1 &A, const MT2 &B, const MT3 &C) {
      constexpr bool SameColumnMajor = MT1::MajorOrder == MT2::MajorOrder && MT1::MajorOrder == MT3::MajorOrder &&
                                       MT1::MajorOrder == order_t::col_major;
      if constexpr (!SameColumnMajor) {
        for (size_t i = 0; i < A.rows(); ++i) {
          for (size_t j = 0; j < A.cols(); ++j) {
            if constexpr (OverWrite) {
              A(i, j) = B(i, j) * C(i, j);
            } else {
              A(i, j) += B(i, j) * C(i, j);
            }
          }
        }
      } else {
        for (size_t j = 0; j < A.cols(); ++j) {
          for (size_t i = 0; i < A.rows(); ++i) {
            if constexpr (OverWrite) {
              A(i, j) = B(i, j) * C(i, j);
            } else {
              A(i, j) += B(i, j) * C(i, j);
            }
          }
        }
      }
    }

    template <concepts::matrices MT1, concepts::matrices MT2>
    static constexpr void div(MT1 &A, const MT2 &B) {
      constexpr bool SameColumnMajor = MT1::MajorOrder == MT2::MajorOrder && MT1::MajorOrder == order_t::col_major;
      if constexpr (!SameColumnMajor) {
        for (size_t i = 0; i < A.rows(); ++i) {
          for (size_t j = 0; j < A.cols(); ++j) {
            A(i, j) /= B(i, j);
          }
        }
      } else {
        for (size_t j = 0; j < A.cols(); ++j) {
          for (size_t i = 0; i < A.rows(); ++i) {
            A(i, j) /= B(i, j);
          }
        }
      }
    }

    template <bool OverWrite = true, concepts::matrices MT1, concepts::matrices MT2, concepts::matrices MT3>
    static constexpr void div(MT1 &A, const MT2 &B, const MT3 &C) {
      constexpr bool SameColumnMajor = MT1::MajorOrder == MT2::MajorOrder && MT1::MajorOrder == MT3::MajorOrder &&
                                       MT1::MajorOrder == order_t::col_major;
      if constexpr (!SameColumnMajor) {
        for (size_t i = 0; i < A.rows(); ++i) {
          for (size_t j = 0; j < A.cols(); ++j) {
            if constexpr (OverWrite) {
              A(i, j) = B(i, j) / C(i, j);
            } else {
              A(i, j) += B(i, j) / C(i, j);
            }
          }
        }
      } else {
        for (size_t j = 0; j < A.cols(); ++j) {
          for (size_t i = 0; i < A.rows(); ++i) {
            if constexpr (OverWrite) {
              A(i, j) = B(i, j) / C(i, j);
            } else {
              A(i, j) += B(i, j) / C(i, j);
            }
          }
        }
      }
    }
  };
} // namespace cyfre::backend

#endif