#ifndef MRDCVLSC_CHECK_OPERATORS_HPP
#define MRDCVLSC_CHECK_OPERATORS_HPP

#include <stddef.h>
#include <type_traits>

// Using SFINAE to check for the pressence of operators for type T : replace this with C++ concepts in the future.

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// supported operators : + - * / += -= *= /= ++ -- < > == != <= >=
////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace cyfre {
  namespace check_t::op {
    // equal
    template <typename T, typename = void>
    struct has_eq : std::false_type {};

    template <typename T>
    struct has_eq<T, std::void_t<decltype(std::declval<T>() == std::declval<T>())>> : std::true_type {};

    // not equal
    template <typename T, typename = void>
    struct has_neq : std::false_type {};

    template <typename T>
    struct has_neq<T, std::void_t<decltype(std::declval<T>() != std::declval<T>())>> : std::true_type {};

    // less than
    template <typename T, typename = void>
    struct has_lt : std::false_type {};

    template <typename T>
    struct has_lt<T, std::void_t<decltype(std::declval<T>() < std::declval<T>())>> : std::true_type {};

    // less than equal
    template <typename T, typename = void>
    struct has_lte : std::false_type {};

    template <typename T>
    struct has_lte<T, std::void_t<decltype(std::declval<T>() <= std::declval<T>())>> : std::true_type {};

    // greater than
    template <typename T, typename = void>
    struct has_gt : std::false_type {};

    template <typename T>
    struct has_gt<T, std::void_t<decltype(std::declval<T>() > std::declval<T>())>> : std::true_type {};

    // greater than equal
    template <typename T, typename = void>
    struct has_gte : std::false_type {};

    template <typename T>
    struct has_gte<T, std::void_t<decltype(std::declval<T>() >= std::declval<T>())>> : std::true_type {};

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // add
    template <typename T, typename = void>
    struct has_add : std::false_type {};

    template <typename T>
    struct has_add<T, std::void_t<decltype(std::declval<T>() + std::declval<T>())>> : std::true_type {};

    // sub
    template <typename T, typename = void>
    struct has_sub : std::false_type {};

    template <typename T>
    struct has_sub<T, std::void_t<decltype(std::declval<T>() - std::declval<T>())>> : std::true_type {};

    // mul
    template <typename T, typename = void>
    struct has_mul : std::false_type {};

    template <typename T>
    struct has_mul<T, std::void_t<decltype(std::declval<T>() * std::declval<T>())>> : std::true_type {};

    // div
    template <typename T, typename = void>
    struct has_div : std::false_type {};

    template <typename T>
    struct has_div<T, std::void_t<decltype(std::declval<T>() / std::declval<T>())>> : std::true_type {};

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // add assign
    template <typename T, typename = void>
    struct has_add_assign : std::false_type {};

    template <typename T>
    struct has_add_assign<T, std::void_t<decltype(std::declval<T>() += std::declval<T>())>> : std::true_type {};

    // sub assign
    template <typename T, typename = void>
    struct has_sub_assign : std::false_type {};

    template <typename T>
    struct has_sub_assign<T, std::void_t<decltype(std::declval<T>() -= std::declval<T>())>> : std::true_type {};

    // mul assign
    template <typename T, typename = void>
    struct has_mul_assign : std::false_type {};

    template <typename T>
    struct has_mul_assign<T, std::void_t<decltype(std::declval<T>() *= std::declval<T>())>> : std::true_type {};

    // div assign
    template <typename T, typename = void>
    struct has_div_assign : std::false_type {};

    template <typename T>
    struct has_div_assign<T, std::void_t<decltype(std::declval<T>() /= std::declval<T>())>> : std::true_type {};

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // post increment
    template <typename T, typename = void>
    struct has_pre_inc : std::false_type {};

    template <typename T>
    struct has_pre_inc<T, std::void_t<decltype(std::declval<T>()++)>> : std::true_type {};

    // pre increment
    template <typename T, typename = void>
    struct has_post_inc : std::false_type {};

    template <typename T>
    struct has_post_inc<T, std::void_t<decltype(++std::declval<T>())>> : std::true_type {};

    // post decrement
    template <typename T, typename = void>
    struct has_pre_dec : std::false_type {};

    template <typename T>
    struct has_pre_dec<T, std::void_t<decltype(std::declval<T>()--)>> : std::true_type {};

    // pre decrement
    template <typename T, typename = void>
    struct has_post_dec : std::false_type {};

    template <typename T>
    struct has_post_dec<T, std::void_t<decltype(--std::declval<T>())>> : std::true_type {};

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // // copy assign?
    // template <typename T, typename = void>
    // struct has_assign : std::false_type {};

    // template <typename T>
    // struct has_assign<T, std::void_t<decltype(std::declval<T>() = std::declval<T>())>> : std::true_type {};

    // // move assign?
    // template <typename T, typename = void>
    // struct has_assign_ref : std::false_type {};

    // template <typename T>
    // struct has_assign_ref<T, std::void_t<decltype(std::declval<T&>() = std::declval<T>())>> : std::true_type {};

  } // namespace check_t::op

  template <typename T>
  struct valid_operators {
    static constexpr bool value =
      check_t::op::has_add<T>::value && check_t::op::has_add_assign<T>::value && check_t::op::has_sub<T>::value &&
      check_t::op::has_sub_assign<T>::value && check_t::op::has_mul<T>::value && check_t::op::has_mul_assign<T>::value &&
      check_t::op::has_div<T>::value && check_t::op::has_div_assign<T>::value &&

      check_t::op::has_eq<T>::value && check_t::op::has_neq<T>::value && check_t::op::has_gt<T>::value &&
      check_t::op::has_gte<T>::value && check_t::op::has_lt<T>::value && check_t::op::has_lte<T>::value &&

      check_t::op::has_post_inc<T>::value && check_t::op::has_pre_inc<T>::value && check_t::op::has_post_dec<T>::value &&
      check_t::op::has_pre_dec<T>::value;
  };
} // namespace cyfre

#endif