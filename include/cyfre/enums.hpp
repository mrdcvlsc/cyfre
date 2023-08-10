/**
 *  @file   enums.hpp
 *  @brief  Contains Enum Classes For Cyfre Namespace.
 *  @author mrdcvlsc
 ***********************************************/

#ifndef MRDCVLSC_ENUMS_HPP
#define MRDCVLSC_ENUMS_HPP

namespace cyfre {

  /// @brief Type of matrix memory layout, row major or column major order.
  enum class order_t
  {
    row_major,
    col_major
  };

  /// @brief Axis type for a vector.
  enum class axis_t
  {
    x,
    y
  };

  enum class operation_t
  {
    add,
    sub,
    mul,
    div
  };
} // namespace cyfre

#endif