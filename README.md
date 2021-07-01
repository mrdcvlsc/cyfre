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

  cyfre::mat<int> idet(cyfre::IDENTITY,SQUARE_LENGTH);   // creates a 5x5 matrix, all values in main diagonal is 1
  
  cyfre::mat<int> scal(cyfre::SCALAR,7,DEFAULT_VALUE);   // creates a 7x7 matrix, all values in main diagonal is 15
  
  cyfre::mat<int> nill(cyfre::NULLZERO,SQUARE_LENGTH);   // creates a 5x5 matrix, where all values are 0 
  
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

  <details>
  <summary><b>cyfre::SCALAR_OPERATIONS</b></summary>
  <br>
    defined : ```cyfre::SCALAR_OPERATIONS{ADD,SUB,MUL,DIV}```<br><br>
    use :<br>
    cyfre::SCALAR_OPERATION<br>
    ex: ```cyfre::ADD``` to select addition
  </details>

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
  
  // all available operations are cyfre::SCALAR_OPERATIONS{ADD,SUB,MUL,DIV}

  // the method below will return a scaled matrix of the original one
  a = cyfre::scale(origin_matrix,cyfre::ADD,2);
  
  // scale all the elements of the matrix with the give operation [changes the matrix itself]
  origin_matrix.scale(cyfre::SUB,-10);

  // scale all the elements of a row with the give operation [changes the matrix itself]
  origin_matrix.scale_row(0,cyfre::MUL,3); // multiply all elements of the 0th row index into 3

  // scale all the elements of a column with the give operation [changes the matrix itself]
  origin_matrix.scale_column(0,cyfre::DIV,2); // divide all the elements of the 0th column index into 2

  // multiplies each elements of matching columns from row index 1 & 2, then store the answers in row index 1 [changes the matrix itself]
  origin_matrix.row_operation(1,cyfre::MUL,2);

  // subtract each elements of matching rows from column index 0 & 1, then store the answers in column index 0 [changes the matrix itself]
  origin_matrix.column_operation(0,cyfre::SUB,1);

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
  cyfre::mat<int> squared_matrix, doubled_matrix, zero_matrix;
  cyfre::mat<int> product_matrix, half_values;
  cyfre::mat<int> origin_matrix(
    {{1,2,3},
     {4,5,6},
     {7,8,9}
  });
  

  // you can use the +,-,*,/ operators to perform matrix addition, subtraction, and multiplication
  
  doubled_matrix = origin_matrix + origin_matrix;
  zero_matrix    = origin_matrix - orignial_matrix;
  squared_matrix = origin_matrix * origin_matrix;
  half_values    = origin_matrix / origin_matrix;
  

  // not to be confused with matrix multiplication, hadamard product multiply two matrix element by element only
  
  product_matrix = mat::hadamard(origin_matrix,origin_matrix);

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
  
  int total_sum = origin_matrix.total();
  int main_diagonal_total_sum  = origin_matrix.trace();
  
  
  
  // getting rows & column as vectors
  
  std::vector<int> first_row = origin_matrix.row(0);  
  std::vector<int> second_column = origin_matrix.column(1);
  
  
  
  // getting rows & columns as a collection of iterators
  
  std::vector<typename std::vector<int>::const_iterator> first_row_iterators = origin_matrix.row_iterators(0);
  std::vector<typename std::vector<int>::const_iterator> second_column_iterators = origin_matrix.column_iterators(1);
  
  
  
  // transpose of a matrix
  
  t = origin_matrix.get_transpose(); // return a new transposed matrix
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
