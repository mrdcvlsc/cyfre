#include "include/functions.hpp"

using namespace cyfre;

int main() {
  // ================================== allocators ==================================

  backend::dynamic<0, 0>::template allocate<char, 0, 0> dynamic_alloc1(4, 7);
  assert(dynamic_alloc1.rows == 4);
  assert(dynamic_alloc1.cols == 7);
  static_assert(sizeof(dynamic_alloc1) == sizeof(size_t) * 3, "wrong dynamic container stack size");

  backend::dynamic<0, 0>::template allocate<char, 0, 0> dynamic_alloc2 = dynamic_alloc1;
  assert(dynamic_alloc2.rows == 4);
  assert(dynamic_alloc2.cols == 7);
  static_assert(sizeof(dynamic_alloc2) == sizeof(size_t) * 3, "wrong dynamic container stack size");

  auto dynamic_alloc3 = dynamic_alloc1;
  assert(dynamic_alloc3.rows == 4);
  assert(dynamic_alloc3.cols == 7);
  static_assert(sizeof(dynamic_alloc3) == sizeof(size_t) * 3, "wrong dynamic container stack size");

  auto dynamic_alloc4 = std::move(dynamic_alloc1);
  assert(dynamic_alloc4.rows == 4);
  assert(dynamic_alloc4.cols == 7);
  static_assert(sizeof(dynamic_alloc4) == sizeof(size_t) * 3, "wrong dynamic container stack size");

  constexpr fixed<9, 10>::template allocate<char, 9, 10> fixed_alloc1;
  static_assert(fixed_alloc1.rows == 9);
  static_assert(fixed_alloc1.cols == 10);
  static_assert(sizeof(fixed_alloc1) == 90, "wrong stack size in initialization");

  // ================================== matrix ==================================

  //////////////// fixed matrix equality test ////////////////

  constexpr mat<char, fixed<4, 5>> mat1;
  static_assert(mat1.rows() == 4);
  static_assert(mat1.cols() == 5);
  static_assert(sizeof(mat1) == 20, "wrong stack size in initialization");

  constexpr auto mat2 = mat1;

  static_assert(mat2 == mat1, "equality test 1 is wrong, should be equal");
  static_assert(mat2 == mat1, "equality test 1 is wrong, should be equal");

  mat<short, fixed<3, 4>> fixed_origin;
  mat<short, fixed<3, 4>> fixed_copy = fixed_origin;

  assert(fixed_origin == fixed_copy);
  fixed_copy(1, 2) = 5;
  assert(fixed_origin != fixed_copy);

  //////////////// dynamic & fixed matrix equality test ////////////////

  mat<char, fixed<5, 5>> fixed_mat1;
  mat<char, dynamic> dynamic_mat1(10, 10);

  fixed_mat1.fill('a');
  dynamic_mat1.fill('a');
  dynamic_mat1.resize(5, 5);

  mat<char, dynamic> dynamic_mat2 = {
    {'a', 'a', 'a', 'a', 'a'}, {'a', 'a', 'a', 'a', 'a'}, {'a', 'a', 'a', 'a', 'a'},
    {'a', 'a', 'a', 'a', 'a'}, {'a', 'a', 'a', 'a', 'a'},
  };

  mat<char, fixed<5, 5>> fixed_mat2 = {
    {'a', 'a', 'a', 'a', 'a'}, {'a', 'a', 'a', 'a', 'a'}, {'a', 'a', 'a', 'a', 'a'},
    {'a', 'a', 'a', 'a', 'a'}, {'a', 'a', 'a', 'a', 'a'},
  };

  char mat[25] = {
    'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a',
    'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a',
  };

  for (size_t i = 0; i < fixed_mat2.rows(); ++i) {
    for (size_t j = 0; j < fixed_mat2.cols(); ++j) {
      assert(mat[i * 5 + j] == fixed_mat2(i, j));
    }
  }

  assert(fixed_mat1 == dynamic_mat1);
  assert(fixed_mat1 == dynamic_mat2);

  ////////////////////// MATRIX INITIALIATION //////////////////////

  {
    constexpr ::feye<int, 3> eye_fixed;
    ::deye<int> eye_dynamic(3);
    assert(eye_dynamic == eye_fixed);
  }

  std::cout << "Tests : PASSED - Initalizations\n";
  return 0;
}