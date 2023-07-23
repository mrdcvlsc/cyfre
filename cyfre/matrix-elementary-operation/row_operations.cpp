#ifndef CYFRE_ROW_OPERATIONS_CPP
#define CYFRE_ROW_OPERATIONS_CPP

#include "../classes/matrix_class.hpp"
#include <iostream>

namespace cyfre {
  /// 'ADD,SUB,MUL, or DIV' a given 'const T value' to all elements of a selected 'const size_t row_index'
  template <class T>
  void mat<T>::scale_row(const size_t row_index, const SCALAR scalar_operation, const T value) {
#ifndef CHECK_RANGE_DISABLE
    if ((row_index > height - 1)) {
      throw std::out_of_range(
        "\n\nERROR : void scale_row(const size_t row_index, const SCALAR scalar_operation, const T value)\n"
        "\tthe given row index is out of bound\n"
      );
    }
#endif

    auto operation_function = [scalar_operation](const T matrix_index, const T operation_value) {
      switch (scalar_operation) {
        case ADD:
          return matrix_index + operation_value;
        case SUB:
          return matrix_index - operation_value;
        case MUL:
          return matrix_index * operation_value;
        case DIV:
          return matrix_index / operation_value;
        default:
          throw std::invalid_argument(
            "\n\nERROR : scale_row(const size_t row_index, const SCALAR scalar_operation, const T value)\n"
            "\tscale_row was given an invalid operation\n"
          );
      }
    };

    for (size_t i = 0; i < width; ++i) {
      matrix[row_index * width + i] = operation_function(matrix[row_index * width + i], value);
    }
  }

  template <class T>
  void mat<T>::row_operation(const size_t output_index, const SCALAR scalar_operation, size_t input_index) {
#ifndef CHECK_RANGE_DISABLE
    if ((output_index > height - 1)) {
      throw std::out_of_range(
        "\n\nERROR : void row_operation(const size_t output_index, const SCALAR scalar_operation, size_t "
        "input_index)\n"
        "\tthe given row 'output_index' is out of bound\n"
      );
    } else if ((input_index > height - 1)) {
      throw std::out_of_range(
        "\n\nERROR : void row_operation(const size_t output_index, const SCALAR scalar_operation, size_t "
        "input_index)\n"
        "\tthe given row 'input_index'  is out of bound\n"
      );
    }
#endif

    auto operation_function = [scalar_operation](const T matrix_index, const T operation_value) {
      switch (scalar_operation) {
        case ADD:
          return matrix_index + operation_value;
        case SUB:
          return matrix_index - operation_value;
        case MUL:
          return matrix_index * operation_value;
        case DIV:
          return matrix_index / operation_value;
        default:
          throw std::invalid_argument(
            "\n\nERROR : void row_operation(const size_t output_index, const SCALAR scalar_operation, "
            "size_t input_index)\n"
            "\tthe 'scalar_operation' given was invalid\n"
          );
      }
    };

    for (size_t i = 0; i < width; ++i) {
      matrix[output_index * width + i] =
        operation_function(matrix[output_index * width + i], matrix[input_index * width + i]);
    }
  }

  /// @note: swaps the values of a row to another row :: a<-->b
  template <class T>
  void mat<T>::row_swap(size_t row_a, size_t row_b) {
#ifndef CHECK_RANGE_DISABLE
    if ((row_a > height - 1)) {
      throw std::out_of_range(
        "\n\nERROR : void row_swap(size_t row_a, size_t row_b)\n"
        "\tthe given row 'row_a' is out of bound\n"
      );
    } else if ((row_b > height - 1)) {
      throw std::out_of_range(
        "\n\nERROR : void row_swap(size_t row_a, size_t row_b)\n"
        "\tthe given row 'row_b'  is out of bound\n"
      );
    }
#endif

    T temp;
    for (size_t i = 0; i < width; ++i) {
      temp = matrix[row_a * width + i];
      matrix[row_a * width + i] = matrix[row_b * width + i];
      matrix[row_b * width + i] = temp;
    }
  }

  /// @note: multiply all the values of a row to a non-zero constant
  /// @arg(scalar,base_row)
  /// @param 1 scalar : template T type value that you want to multiply to all the elements of the row
  /// @param 2 base_row : size_t index of the row you want to perform scaling
  template <class T>
  void mat<T>::row_scale(T scalar, size_t base_row) {
#ifndef CHECK_RANGE_DISABLE
    if ((base_row > height - 1)) {
      throw std::out_of_range(
        "\n\nERROR : void row_scale(S scalar, size_t base_row)\n"
        "\tthe given row 'base_row' is out of bound\n"
      );
    }
#endif

    for (size_t i = 0; i < width; ++i) {
      matrix[base_row * width + i] *= scalar;
    }
  }

  /// @note: multiply all the values of a row to a non-zero constant, then add the result to another row
  /// @arg(scalar,scale_row,base_row)
  /// @param 1 scalar : template T type value that you want to multiply to all the elements of the row
  /// @param 2 scale_row : size_t index of the row you want to scale
  /// @param 3 base_row : size_t index of the row you want to add the results of the scaled row
  template <class T>
  void mat<T>::row_scale(T scalar, size_t scale_row, size_t base_row) {
#ifndef CHECK_RANGE_DISABLE
    if ((scale_row > height - 1)) {
      throw std::out_of_range(
        "\n\nERROR : void row_scale(S scalar, size_t scale_row, size_t scale_row)\n"
        "\tthe given row 'scale_row' is out of bound\n"
      );
    } else if ((base_row > height - 1)) {
      throw std::out_of_range(
        "\n\nERROR : void row_scale(S scalar, size_t scale_row, size_t base_row)\n"
        "\tthe given row 'base_row' is out of bound\n"
      );
    }
#endif

    for (size_t i = 0; i < width; ++i) {
      matrix[base_row * width + i] += scalar * matrix[scale_row * width + i];
    }
  }
} // namespace cyfre

#endif