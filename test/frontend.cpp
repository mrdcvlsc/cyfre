#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <type_traits>

// #include "../../extended-precision-integers/epi.hpp"
#include "../include/cyfre.hpp"

int main() {
  //////////////// dynamic matrix equality test ////////////////

  cyfre::mat<char, cyfre::dynamic> mat3(2, 12);
  assert(mat3.rows() == 2);
  assert(mat3.cols() == 12);
  static_assert(sizeof(mat3) == sizeof(size_t) * 3, "wrong dynamic container stack size");

  auto mat4 = mat3;
  assert(mat4 == mat3);
  mat4(1, 6) = 77;
  assert(mat4 != mat3);

  auto mat5 = std::move(mat3);

  // ================================== matrix ==================================

  std::cout << "Tests : PASSED\n";

  return 0;
}

#ifdef ENABLE_OLD_TEST

int main() {
  // ############### test 01 ###############
  {
    mat<int> mat_object(cyfre::TYPE::IDENTITY, 3);
    mat<int> idet({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}});
    if (mat_object != idet)
      throw std::logic_error("error at test 01");
    std::cout << "test 1 correct\n";
  }

  // ############### test 02 ###############
  {
    mat<int> mat_object(cyfre::TYPE::SCALARMATRIX, 3, 7);
    mat<int> scalars({{7, 0, 0}, {0, 7, 0}, {0, 0, 7}});
    if (mat_object != scalars)
      throw std::logic_error("error at test 02");
    std::cout << "test 2 correct\n";
  }

  // ############### test 03 ###############
  {
    mat<int> subject(cyfre::TYPE::NULLZERO, 3);
    mat<int> correct({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
    if (subject != correct)
      throw std::logic_error("error at test 03");
    std::cout << "test 3 correct\n";
  }

  // ############### test 04 ###############
  {
    mat<int> subject(3, 2, 5);
    mat<int> correct({{5, 5}, {5, 5}, {5, 5}});
    if (subject != correct)
      throw std::logic_error("error at test 04");
    std::cout << "test 4 correct\n";
  }

  // ############### test 05 ###############
  {
    mat<int> subject({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    subject.row_swap(1, 2);
    mat<int> correct({{1, 2, 3}, {7, 8, 9}, {4, 5, 6}});
    if (subject != correct)
      throw std::logic_error("error at test 05");
    std::cout << "test 5 correct\n";
  }

  // ############### test 06 ###############
  {
    mat<int> subject({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    subject.row_scale(5, 0);
    mat<int> correct({{5, 10, 15}, {4, 5, 6}, {7, 8, 9}});
    if (subject != correct)
      throw std::logic_error("error at test 06");
    std::cout << "test 6 correct\n";
  }

  // ############### test 07 ###############
  {
    mat<int> subject({{1, 2, 3}, {4, 5, 6}, {0, 0, 0}});
    subject.row_scale(7, 0, 2);
    mat<int> correct({{1, 2, 3}, {4, 5, 6}, {7, 14, 21}});
    if (subject != correct)
      throw std::logic_error("error at test 07");
    std::cout << "test 7 correct\n";
  }

  // ############### test 08 ###############
  {
    mat<int> subject({{1, 2}, {3, 4}});
    subject.scale_row(0, cyfre::SCALAR::MUL, 2);
    mat<int> correct({{2, 4}, {3, 4}});
    if (subject != correct)
      throw std::logic_error("error at test 08");
    std::cout << "test 8 correct\n";
  }

  // ############### test 09 ###############
  {
    mat<int> subject({{2, 4}, {6, 8}});
    subject.scale_column(1, cyfre::SCALAR::DIV, 2);
    mat<int> correct({{2, 2}, {6, 4}});
    if (subject != correct)
      throw std::logic_error("error at test 09");
    std::cout << "test 9 correct\n";
  }

  // ############### test 10 ###############
  {
    mat<int> subject({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    subject.row_operation(1, cyfre::SCALAR::MUL, 2);
    mat<int> correct({{1, 2, 3}, {28, 40, 54}, {7, 8, 9}});
    if (subject != correct)
      throw std::logic_error("error at test 10");
    std::cout << "test 10 correct\n";
  }

  // ############### test 11 ###############
  {
    mat<int> subject({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    subject.column_operation(1, cyfre::SCALAR::DIV, 2);
    mat<int> correct({{1, 0, 3}, {4, 0, 6}, {7, 0, 9}});
    if (subject != correct)
      throw std::logic_error("error at test 11");
    std::cout << "test 11 correct\n";
  }

  // ############### test 12 ###############
  {
    mat<int> subject({{1, 2}, {3, 4}});
    subject = subject + 2;
    mat<int> correct({{3, 4}, {5, 6}});
    if (subject != correct)
      throw std::logic_error("error at test 12");
    std::cout << "test 12 correct\n";
  }

  // ############### test 13 ###############
  {
    mat<int> subject({{1, 2}, {3, 4}});
    subject += 2;
    mat<int> correct({{3, 4}, {5, 6}});
    if (subject != correct)
      throw std::logic_error("error at test 13");
    std::cout << "test 13 correct\n";
  }

  // ############### test 14 ###############
  {
    mat<int> A({{1, 2, 3}, {4, 5, 6}});

    mat<int> B({{-1, -2, -3}, {-4, -5, -6}});
    mat<int> C = A + B;
    mat<int> correct(2, 3, 0);
    if (C != correct)
      throw std::logic_error("error at test 14");
    std::cout << "test 14 correct\n";
  }

  // ############### test 15 ###############
  {
    mat<int> A({{10, 1, 33}, {44, 50, 12}});
    mat<int> B({{7, 19, 5}, {7, 6, 5}});
    mat<int> C = A - B;
    ;
    mat<int> correct({{3, -18, 28}, {37, 44, 7}});
    if (C != correct)
      throw std::logic_error("error at test 15");
    std::cout << "test 15 correct\n";
  }

  // ############### test 16 ###############
  {
    mat<int> A({{2, 4, 6}, {8, 2, 4}});
    mat<int> B({{1, 4, 3}, {2, 2, 1}});
    mat<int> C = cyfre::hadamard(A, B);
    mat<int> correct({{2, 16, 18}, {16, 4, 4}});
    if (C != correct)
      throw std::logic_error("error at test 16");
    std::cout << "test 16 correct\n";
  }

  // ############### test 17 ###############
  {
    mat<int> X({{7, 12, 13}, {14, 5, 20}, {66, 42, -4}});
    mat<int> W{-3, 4, 56};

    mat<int> C = W * X;
    mat<int> correct{3731, 2336, -183};

    if (C != correct)
      throw std::logic_error("error at test 17");
    std::cout << "test 17 correct\n";
  }

  // ############### test 18 ###############
  {
    auto square = [](int x) { return x * x; };
    mat<int> X(
      {{23, 12, 53, 34, 23}, {33, 77, 53, 90, 28}, {87, 26, 11, 24, 31}, {84, 32, 73, 64, 26}, {77, 88, 45, 97, 86}}
    );
    X.apply(square);
    mat<int> correct(
      {{529, 144, 2809, 1156, 529},
       {1089, 5929, 2809, 8100, 784},
       {7569, 676, 121, 576, 961},
       {7056, 1024, 5329, 4096, 676},
       {5929, 7744, 2025, 9409, 7396}}
    );
    if (X != correct)
      throw std::logic_error("error at test 18");
    std::cout << "test 18 correct\n";
  }

  // ############### test 19 ###############
  {
    mat<int> X({
      {1, 2, 3, 4},
      {5, 6, 7, 8},
    });
    X.transpose();
    mat<int> correct({{1, 5}, {2, 6}, {3, 7}, {4, 8}});
    if (X != correct)
      throw std::logic_error("error at test 19");
    std::cout << "test 19 correct\n";
  }

  // ############### test 20 ###############
  {
    mat<int> X({{7, 12, 13}, {14, 5, 20}, {66, 42, -4}});
    mat<int> X_cubed = cyfre::power(X, 3);
    mat<int> X_squared = X;
    X_squared.power(2);

    mat<int> C1({{35599, 28068, 26659}, {38210, 31505, 39196}, {130302, 85590, 20042}});
    mat<int> C2({{1075, 690, 279}, {1488, 1033, 202}, {786, 834, 1714}});
    if (X_cubed != C1)
      throw std::logic_error("wrong answer on test 20 cube");
    if (X_squared != C2)
      throw std::logic_error("wrong answer on test 20 square");
    std::cout << "CORRECT ANSWERS IN TEST 20\n";
  }

  // ############### test 21 ###############
  {
    mat<long double> X({{23, 12, 53}, {33, 77, 53}, {87, 26, 11}});
    X.inv();
    mat<long double> correct(
      {{0.00196078L, -0.00460101L, 0.0127211L},
       {-0.0156863L, 0.0160925L, -0.00195709L},
       {0.0215686L, -0.00164691L, -0.00507736L}}
    );
    for (size_t i = 0; i < 3; ++i) {
      for (size_t j = 0; j < 3; ++j) {
        if ((std::to_string(X(i, j))) != (std::to_string(correct(i, j)))) {
          throw std::logic_error("wrong answer inverse 21\n");
        }
      }
    }
    std::cout << "test 21 correct\n";
  }

  // ############### test 22 ###############
  {
    mat<int> X({{1, 2, 3, 4}, {5, 6, 7, 8}, {-2, 3, -4, 1}});
    X = cyfre::rref(X);
    mat<int> correct({{1, 0, 0, -1}, {0, 1, 0, 1}, {0, 0, 1, 1}});
    for (size_t i = 0; i < 3; ++i) {
      for (size_t j = 0; j < 3; ++j) {
        if ((std::to_string(X(i, j))) != (std::to_string(correct(i, j)))) {
          throw std::logic_error("wrong answer rref 22\n");
        }
      }
    }
    std::cout << "test 22 correct\n";
  }

  // ############### test 23 ###############
  {
    mat<long double> X({{5, 10, -15, 20}, {30, -35, -40, -45}, {55, 60, 75, -80}, {90, 95, 100, -105}});
    long double determinant = cyfre::det(X);
    if (std::to_string((int) (float) determinant) != "-720000")
      throw std::logic_error("wrong determinant (23)");
    std::cout << "correct determinant (23)\n";
  }

  // ############### test 24 ###############
  {
    mat<int> X({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    int diag_sum = X.trace();
    if (diag_sum != 15)
      throw std::logic_error("wrong trace (24)");
    std::cout << "correct trace (24)\n";
  }

  // ############### test 25 ###############
  {
    mat<int> X({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    int diag_sum = X.sum();
    if (diag_sum != 45)
      throw std::logic_error("wrong sum (25)");
    std::cout << "correct sum (25)\n";
  }

  // ############### test 26 ###############
  {
    mat<short> X({{7, 2, 4}, {4, 7, 6}, {7, 4, 9}});

    long double mean = cyfre::sts::mean(X);
    long double median = cyfre::sts::median(X);

    std::pair<size_t, std::vector<short>> getmode = cyfre::sts::mode(X);

    size_t numbers_of_modes = getmode.second.size();
    size_t modes_occurrence = getmode.first;

    std::vector<short> modes = getmode.second;

    if (std::to_string(mean) != "5.555556")
      throw std::logic_error("wrong mean (26:1)");
    if (std::to_string((int) (float) median) != "7")
      throw std::logic_error("wrong median (26:2)");
    if (numbers_of_modes != 2)
      throw std::logic_error("wrong numbers_of_modes (26:3)");
    if (modes_occurrence != 3)
      throw std::logic_error("wrong modes_occurrence (26:4)");
    if (modes[0] != 4)
      throw std::logic_error("wrong modes[0] (26:5)");
    if (modes[1] != 7)
      throw std::logic_error("wrong modes[1] (26:6)");

    std::cout << "mean, median modem correct outputs : 1 (26)\n";

    /*
    mean = 5.55556
    median = 7
    numbers_of_modes = 2
    modes_occurrence = 3
    modes = [7,4]
    */
    mat<short> SSS({7, 2, 4, 3, 9});

    long double sum_of_square = cyfre::sts::sofs(SSS), variance = cyfre::sts::variance(SSS, cyfre::sts::SAMPLE),
                standard_deviation = cyfre::sts::stddvn(SSS, cyfre::sts::SAMPLE);

    //   sum_of_square = 34
    //   variance = 8.5
    //   standard_deviation = 2.91548

    if (std::to_string((int) (float) sum_of_square) != "34")
      throw std::logic_error("wrong sum_of_square (26:7)");
    if (std::to_string((float) variance) != "8.500000")
      throw std::logic_error("wrong variance (26:8)");
    if (std::to_string((float) standard_deviation) != "2.915476")
      throw std::logic_error("wrong standard_deviation (26:9)");
    std::cout << "correct outputs : 2 (26)\n";
  }

  // ############### test 27 ###############
  {
    mat<int> subject1({{5, 10, 15, 20}, {30, 60, 2, -2}, {7, 6, 5, -232}});
    mat<int> target1(
      {{0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0},
       {0, 5, 10, 15, 20, 0},
       {0, 30, 60, 2, -2, 0},
       {0, 7, 6, 5, -232, 0},
       {0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0}}
    );
    subject1.padding(2, 1);
    if (subject1 != target1) {
      throw std::logic_error("test 27 error in padding output");
    } else {
      std::cout << "correct (27)\n";
    }
  }

  // ############### test 28 ###############
  {
    mat<int> A{{1, 2, 3}, {4, 5, 6}, {6, 5, 4}};
    mat<int> B{{1, 2, 3}, {4, 5, 6}, {6, 5, 4}};
    mat<int> C = A;
    mat<int> D;
    D = B;
    mat<int> E = B * A;
    mat<int> F = B * A * E;
    mat<int> G;
    G = F * E;
    mat<int> H;
    H = F * G * B;
    mat<int> Z(A * F);
  }

  return 0;
}

#endif
