# cyfre
## Under Development
### my implementation of a C++ matrix library

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

### scalar operations

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

### supported operations and operators

  -addition(+)
  -subtraction(-)
  -multiplication(*)
  
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
  
### matrix methods

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
  
  int total_sum = original_matrix.total();
  
  int main_diagonal_total_sum  = original_matrix.trace();
  
  std::vector<int> first_row = original_matrix.row(0);
  std::vector<int> second_column = original_matrix.column(1);
  
  return 0;
}

```

### accessing matrix elements

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
