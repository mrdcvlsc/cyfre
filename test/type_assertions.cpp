#include <cassert>
#include <iostream>
#include <stdexcept>

#include "../include/cyfre.hpp"

using namespace cyfre;

struct MatrixType1 {
  MatrixType1() {}
};

struct MatrixType2 {
  int rows;
  int cols;

  MatrixType2() {}

  //   protected:

  using ScalarType = char;
  using AllocatorType = double;
};

struct MatrixType3 {
  int rows();
  MatrixType1 cols();

  MatrixType3() {}

  //   protected:

  using ScalarType = char;
  using AllocatorType = double;
  char matrix;
  int MajorOrder = 5;
};

struct MatrixType4 {
  size_t rows();
  size_t cols();

  MatrixType4() {}

  //   protected:

  using ScalarType = MatrixType1;
  using AllocatorType = double;
  int matrix[10];
  order_t MajorOrder = order_t::col_major;
};

struct MatrixType5 {
  size_t rows();
  char cols();

  MatrixType5() {}

  //   protected:

  using ScalarType = char;
  using AllocatorType = double;
  char matrix = 2;
  order_t MajorOrder = order_t::col_major;
};

struct MatrixType6 {
  size_t rows();
  size_t cols();

  MatrixType6() {}

  //   protected:

  using ScalarType = char;
  using AllocatorType = double;
  char *matrix;
  order_t MajorOrder = order_t::col_major;
};

struct MatrixType7 {
  size_t rows();
  size_t cols();

  MatrixType7() : matrix(4, 4) {}

  //   protected:

  using ScalarType = char;
  using AllocatorType = dynamic;
  dynamic::allocate<char, 0, 0> matrix;
  order_t MajorOrder = order_t::col_major;
};

int arr_test1[10];
int *arr_test2;
int arr_test3;

int main() {
  static_assert(concepts::arrays<decltype(arr_test1)>, "should be valid");
  static_assert(concepts::arrays<decltype(arr_test2)>, "should be valid");
  static_assert(not concepts::arrays<decltype(arr_test3)>, "should not be valid");
  static_assert(not concepts::arrays<MatrixType1>, "should not be valid");

  // scalar type checks
  static_assert(concepts::scalars<char>, "Scalar Type1 - test");
  static_assert(concepts::scalars<float>, "Scalar Type2 - test");
  static_assert(concepts::scalars<int>, "Scalar Type3 - test");
  static_assert(not concepts::scalars<MatrixType1>, "Scalar Type3 - test");
  static_assert(not concepts::scalars<MatrixType2>, "Scalar Type4 - test");
  static_assert(not concepts::scalars<MatrixType3>, "Scalar Type5 - test");
  // static_assert(concepts::scalars<epi::uint1024_t>, "Scalar Type1 - test");

  // allocator types
  static_assert(concepts::allocators<dynamic::allocate<char, 0, 0>>, "dynamic allocator");
  static_assert(concepts::allocators<fixed<5, 5>::allocate<char, 5, 5>>, "stack allocator");
  static_assert(not concepts::allocators<MatrixType1>, "stack allocator");

  static_assert(not concepts::matrices<MatrixType1>, "MatrixType1 - test");
  static_assert(not concepts::matrices<MatrixType2>, "MatrixType2 - test");
  static_assert(not concepts::matrices<MatrixType3>, "MatrixType3 - test");
  static_assert(not concepts::matrices<MatrixType4>, "MatrixType4 - test");
  static_assert(not concepts::matrices<MatrixType5>, "MatrixType5 - test");
  static_assert(not concepts::matrices<MatrixType6>, "MatrixType6 - test");

  // problem with protected members if not accessed inside the mat class.
  static_assert(concepts::matrices<MatrixType7>, "MatrixType6 - test");

  static_assert(concepts::matrices<mat<int, fixed<4, 4>>>, "Matrix Test - test 1");
  static_assert(concepts::matrices<mat<int, dynamic>>, "Matrix Test - test 2");

  std::cout << "Tests : PASSED - Type Assertions\n";
  return 0;
}