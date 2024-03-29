#ifndef CYFRE_COL_OPERATIONS_CPP
#define CYFRE_COL_OPERATIONS_CPP

#include "../classes/matrix_class.hpp"
#include <iostream>

namespace cyfre {
  /// 'ADD,SUB,MUL, or DIV' a given 'const T value' to all elements of a selected 'const size_t column_index'
  template <class T>
  void mat<T>::scale_column(const size_t column_index, const SCALAR scalar_operation, const T value) {
#ifndef CHECK_RANGE_DISABLE
    if ((column_index > width - 1)) {
      throw std::out_of_range(
        "\n\nERROR : void scale_column(const size_t column_index, const SCALAR scalar_operation, const T "
        "value)\n"
        "\tthe given column index is out of bound\n"
      );
    }
#endif

    auto operation_function = [scalar_operation](const T matrix_index, const T operation_value) {
      switch (scalar_operation) {
        case ADD: return matrix_index + operation_value;
        case SUB: return matrix_index - operation_value;
        case MUL: return matrix_index * operation_value;
        case DIV: return matrix_index / operation_value;
        default:
          throw std::invalid_argument(
            "\n\nERROR : scale_column(const size_t column_index, const SCALAR scalar_operation, const T "
            "value)\n"
            "\tscale_column was given an invalid scalar operation\n"
          );
      }
    };

    for (size_t i = 0; i < height; ++i) {
      matrix[i * width + column_index] = operation_function(matrix[i * width + column_index], value);
    }
  }

  template <class T>
  void mat<T>::column_operation(const size_t output_index, const SCALAR scalar_operation, size_t input_index) {
#ifndef CHECK_RANGE_DISABLE
    if ((output_index > width - 1)) {
      throw std::out_of_range(
        "\n\nERROR : void column_operation(const size_t output_index, const SCALAR scalar_operation, size_t "
        "input_index)\n"
        "\tthe given column 'output_index' is out of bound\n"
      );
    } else if ((input_index > width - 1)) {
      throw std::out_of_range(
        "\n\nERROR : void column_operation(const size_t output_index, const SCALAR scalar_operation, size_t "
        "input_index)\n"
        "\tthe given column 'input_index' is out of bound\n"
      );
    }
#endif

    auto operation_function = [scalar_operation](const T matrix_index, const T operation_value) {
      switch (scalar_operation) {
        case ADD: return matrix_index + operation_value;
        case SUB: return matrix_index - operation_value;
        case MUL: return matrix_index * operation_value;
        case DIV: return matrix_index / operation_value;
        default:
          throw std::invalid_argument(
            "\n\nERROR : void column_operation(const size_t output_index, const SCALAR scalar_operation, "
            "size_t input_index)\n"
            "\tthe 'scalar_operation' given was invalid\n"
          );
      }
    };

    for (size_t i = 0; i < height; ++i) {
      matrix[i * width + output_index] =
        operation_function(matrix[i * width + output_index], matrix[i * width + input_index]);
    }
  }

  /// @note: swaps the values of a column to another column :: a<-->b
  template <class T>
  void mat<T>::column_swap(size_t column_a, size_t column_b) {
#ifndef CHECK_RANGE_DISABLE
    if ((column_a > width - 1)) {
      throw std::out_of_range(
        "\n\nERROR : void column_swap(size_t column_a, size_t column_b)\n"
        "\tthe given column 'column_a' is out of bound\n"
      );
    } else if ((column_b > width - 1)) {
      throw std::out_of_range(
        "\n\nERROR : void column_swap(size_t column_a, size_t column_b)\n"
        "\tthe given column 'column_b'  is out of bound\n"
      );
    }
#endif

    T temp;
    for (size_t i = 0; i < height; ++i) {
      temp = matrix[i * width + column_a];
      matrix[i * width + column_a] = matrix[i * width + column_b];
      matrix[i * width + column_b] = temp;
    }
  }

  /// @note: multiply all the values of a column to a non-zero constant
  /// @arg(scalar,base_column)
  /// @param 1 scalar : template S type value that you want to multiply to all the elements of the column
  /// @param 2 base_column : size_t index of the column you want to perform scaling
  template <class T>
  void mat<T>::column_scale(T scalar, size_t base_column) {
#ifndef CHECK_RANGE_DISABLE
    if ((base_column > width - 1)) {
      throw std::out_of_range(
        "\n\nERROR : void column_scale(S scalar, size_t base_column)\n"
        "\tthe given column 'base_column' is out of bound\n"
      );
    }
#endif

    for (size_t i = 0; i < height; ++i) {
      matrix[i * width + base_column] *= scalar;
    }
  }

  /// @note: multiply all the values of a column to a non-zero constant, then add the result to another column
  /// @arg(scalar,scale_column,base_column)
  /// @param 1 scalar : template S type value that you want to multiply to all the elements of the column
  /// @param 2 scale_column : size_t index of the column you want to scale
  /// @param 3 base_column : size_t index of the column you want to add the results of the scaled column
  template <class T>
  void mat<T>::column_scale(T scalar, size_t scale_column, size_t base_column) {
#ifndef CHECK_RANGE_DISABLE
    if ((scale_column > width - 1)) {
      throw std::out_of_range(
        "\n\nERROR : void column_scale(S scalar, size_t scale_column, size_t scale_column)\n"
        "\tthe given column 'scale_column' is out of bound\n"
      );
    } else if ((base_column > width - 1)) {
      throw std::out_of_range(
        "\n\nERROR : void column_scale(S scalar, size_t scale_column, size_t base_column)\n"
        "\tthe given column 'base_column' is out of bound\n"
      );
    }
#endif

    for (size_t i = 0; i < height; ++i) {
      matrix[i * width + base_column] += scalar * matrix[i * width + scale_column];
    }
  }
} // namespace cyfre

#endif