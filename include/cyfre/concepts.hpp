#ifndef MRDCVLSC_CYFRE_CONCEPTS_HPP
#define MRDCVLSC_CYFRE_CONCEPTS_HPP

#include "enums.hpp"
#include <concepts>
#include <stddef.h>
#include <type_traits>
#include <utility>

namespace cyfre {

  namespace concepts {
    /// @brief concept for valid scalar type to be used in a matrix class.
    template <typename ScalarT>
    concept scalars = requires(ScalarT scalar) {
      { scalar == scalar } -> std::convertible_to<bool>;
      { scalar != scalar } -> std::convertible_to<bool>;

      { scalar < scalar } -> std::convertible_to<bool>;
      { scalar > scalar } -> std::convertible_to<bool>;
      { scalar <= scalar } -> std::convertible_to<bool>;
      { scalar >= scalar } -> std::convertible_to<bool>;

      // enable this comment if you find an easy way to accept chars too.
      // { scalar + scalar } -> std::same_as<T>; // can't accept `char` for some reasons.
      // { scalar - scalar } -> std::same_as<T>; // can't accept `char` for some reasons.
      // { scalar * scalar } -> std::same_as<T>; // can't accept `char` for some reasons.
      // { scalar / scalar } -> std::same_as<T>; // can't accept `char` for some reasons.

      // { scalar += scalar } -> std::same_as<T &>; // can't accept `char` for some reasons.
      // { scalar -= scalar } -> std::same_as<T &>; // can't accept `char` for some reasons.
      // { scalar *= scalar } -> std::same_as<T &>; // can't accept `char` for some reasons.
      // { scalar /= scalar } -> std::same_as<T &>; // can't accept `char` for some reasons.

      // for now to also accept char we just check for the existence of
      // the following operators.
      scalar + scalar;
      scalar - scalar;
      scalar *scalar;
      scalar / scalar;

      scalar += scalar;
      scalar -= scalar;
      scalar *= scalar;
      scalar /= scalar;

      { ++scalar } -> std::same_as<ScalarT &>;
      { scalar++ } -> std::convertible_to<ScalarT>;
      { --scalar } -> std::same_as<ScalarT &>;
      { scalar-- } -> std::convertible_to<ScalarT>;

      { scalar = scalar } -> std::same_as<ScalarT &>;
      // { scalar = std::move(scalar) } -> std::same_as<ScalarT &>;
    };

    template <typename ArrayT>
    concept arrays = std::is_array<ArrayT>::value || std::is_pointer<ArrayT>::value;

    template <typename AllocatorT>
    concept allocators = requires(AllocatorT obj) {
      { obj.rows } -> std::convertible_to<size_t>;
      { obj.cols } -> std::convertible_to<size_t>;
      {
        decltype(obj.matrix) {}
        } -> arrays;
    };

    /// @brief concept for valid matrix type.
    template <typename MatrixT>
    concept matrices = requires(MatrixT obj) {
      typename MatrixT::AllocatorType;
      { std::declval<typename MatrixT::ScalarType>() } -> scalars;

      { obj.MajorOrder } -> std::convertible_to<order_t>;

      { obj.matrix } -> allocators;

      { obj.rows() } -> std::convertible_to<size_t>;
      { obj.cols() } -> std::convertible_to<size_t>;
    };
  } // namespace concepts
} // namespace cyfre

#endif
