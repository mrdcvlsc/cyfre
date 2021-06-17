# cyfre
## Under Development

### a C++ matrix library

### cyfre aims to provide an easy to use c++ matrix library with basic matrix operations.

This library uses cpp stl's std::vector intensively

<details>
<summary><b>cyfre::mat constructors - constructing matrix</b></summary>
<br>

```c++
#include <iostream>
#include <cyfre.hpp>

#define SQUARE_LENGTH 5
#define DEFAULT_VALUE 15
#define ROW_LEN 10
#define COL_LEN 20

int main()
{

  cyfre::mat<int> idet(IDENTITY,SQUARE_LENGTH);   // creates a 5x5 matrix, all values in main diagonal is 1
  
  cyfre::mat<int> scal(SCALAR,7,DEFAULT_VALUE);   // creates a 7x7 matrix, all values in main diagonal is 15
  
  cyfre::mat<int> nill(NULLZERO,SQUARE_LENGTH);   // creates a 5x5 matrix, where all values are 0 
  
  cyfre::mat<int> rect(ROW_LEN,COL_LEN,DEFAULT_VALUE); // creates a 10x20 matrix, where all values are 15
  
  cyfre::mat<int> costum(   // creates the matrix displayed below, converts it into a 2d vector
    {{1,2,3},
     {4,5,6},
     {7,8,9}
  });
  
  return 0;
}

```
</details>
  
<details>
<summary><b>Scalar Operations</b></summary>
<br>

```c++
#include <iostream>
#include <cyfre.hpp>

int main()
{
  cyfre::mat<int> a, b, c, d;
  cyfre::mat<int> origin_matrix(
    {{1,2,3},
     {4,5,6},
     {7,8,9}
  });
  
  // the methods below will return a scaled matrix of the original one
  
  a = original_matrix.get_scale(ADD,5);
  b = original_matrix.get_scale(SUB,5);
  c = original_matrix.get_scale(MUL,5);
  d = original_matrix.get_scale(DIV,5);
  
  
  // the methods below will scale the original matrix itself changing its own values
  
  original_matrix.scale(ADD,-10);
  original_matrix.scale(SUB,5);
  original_matrix.scale(MUL,23);
  original_matrix.scale(DIV,1);
  
  return 0;
}

```
  
</details>
  
<details>
<summary><b>Matrix Operations & Operators</b></summary>
<br>

  - addition(+)
  - subtraction(-)
  - multiplication(*)
  - hadamard product(mat::hadamard())
  
```c++
#include <iostream>
#include <cyfre.hpp>

int main()
{
  cyfre::mat<int> squared_matrix;
  cyfre::mat<int> product_matrix;
  cyfre::mat<int> origin_matrix(
    {{1,2,3},
     {4,5,6},
     {7,8,9}
  });
  
  // you can use the +,-,* operators to perform matrix addition, subtraction, and multiplication
  squared_matrix = original_matrix * original_matrix;
  
  // not to be confused with matrix multiplication, hadamard product multiply two matrix element by element only
  product_matrix = mat::hadamard(original_matrix,original_matrix);
  return 0;
}

```
</details>
  
  
<details>
<summary><b>Available Methods</b></summary>
<br>

```c++
#include <iostream>
#include <cyfre.hpp>

int main()
{
  
  cyfre::mat<int> back, t;
  cyfre::mat<int> origin_matrix(
    {{1,2,3},
     {4,5,6},
     {7,8,9}
  });
  
  
  // sums
  
  int total_sum = original_matrix.total();
  int main_diagonal_total_sum  = original_matrix.trace();
  
  
  
  // getting rows & column as vectors
  
  std::vector<int> first_row = original_matrix.row(0);  
  std::vector<int> second_column = original_matrix.column(1);
  
  
  
  // getting rows & columns as a collection of iterators
  
  std::vector<typename std::vector<int>::const_iterator> first_row_iterators = original_matrix.row_iterators(0);
  std::vector<typename std::vector<int>::const_iterator> second_column_iterators = original_matrix.column_iterators(1);
  
  
  
  // transpose of a matrix
  
  t = original_matrix.get_transpose(); // return a new transposed matrix
  t.transpose();  // transpose itself
  back = t;
  
  
  
  return 0;
}

```
</details>
  
<details>
<summary><b>accessing matrix elements</b></summary>
<br>

```c++
#include <iostream>
#include <cyfre.hpp>

int main()
{
  cyfre::mat<int> a, b, c, d;
  cyfre::mat<int> nums(
    {{1,2,3},
     {4,5,6},
     {7,8,9}
  });
  
  for(size_t i=0; i<nums.height; ++i)
  {
    for(size_t j=0; j<nums.width; ++j)
    {
      // the .matrix is a 2d vector member of the mat class, so you can treat it and use it like a 2d vector
      std::cout<<nums.matrix[i][j]<<'\t';
    }
    std::cout<<'\n';
  }
  
  return 0;
}

```
  
</details>
