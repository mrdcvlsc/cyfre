#ifndef CYFRE_DISPLAY_CPP
#define CYFRE_DISPLAY_CPP

#include "matrix_class.hpp"
#include <iostream>

namespace cyfre {
  template <typename T>
  void display(const mat<T> &input) {
    // 100 width can still be displayed
    // 60 height can still be displayed

    std::vector<std::string> matrixstr;

    size_t n = input.height * input.width;

    for (size_t i = 0; i < n; ++i)
      matrixstr.push_back(std::to_string(input.matrix[i]));

    std::vector<size_t> max_cols_len(input.width, 0);

    for (size_t j = 0; j < input.width; ++j) {
      for (size_t i = 0; i < input.height; ++i) {
        if (matrixstr[i * input.width + j].size() > max_cols_len[j]) {
          max_cols_len[j] = matrixstr[i * input.width + j].size();
        }
      }
    }

    for (size_t i = 0; i < input.height; ++i) {
      if (i == 0)
        std::cout << "[[";
      else
        std::cout << " [";

      for (size_t j = 0; j < input.width; ++j) {
        size_t front_space = max_cols_len[j] - matrixstr[i * input.width + j].size();
        while (front_space--)
          std::cout << ' ';
        std::cout << matrixstr[i * input.width + j];
        if (j != input.width - 1)
          std::cout << ", ";
        else
          std::cout << "]";
      }
      if (i != input.height - 1)
        std::cout << ",\n";
      else
        std::cout << "]\n";
    }

    std::cout.width(0);
  }
} // namespace cyfre

#endif