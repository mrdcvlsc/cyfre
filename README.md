# cyfre
## Under Development

### a C++ matrix library

### cyfre aims to provide an easy to use c++ matrix library with basic matrix operations.

**```#include "cyfre/cyfre.hpp"```**

This library uses cpp stl's std::vector intensively

--------------------------------------------------

<details>
<summary><b><i>CONSTRUCTORS</i></b></summary>
<br>

<!--=====================================================================================-->
<details>
<summary><b>cyfre::MATRIX_TYPES</b></summary>
<br>
  
  **defined** :
  ```c++
  cyfre::MATRIX_TYPES{IDENTITY,NULLZERO,SCALAR}
  ```

  <br>

  **use :**
  *cyfre::MATRIX_TYPES*
  ex:
  ```c++
  cyfre::NULLZERO // to select
  ```
</details>

<!--=====================================================================================-->
<details>
<summary><b>identity matrix</b></summary>
<br>
  
  **construct an identity matrix**

  ```c++
  cyfre::mat<int> mat_object(cyfre::IDENTITY,3);

  // mat_object = [[1,0,0],
  //               [0,1,0],
  //               [0,0,1]]
  ```

</details>

<!--=====================================================================================-->
<details>
<summary><b>scalar matrix</b></summary>
<br>
  
  **construct an scalar matrix**

  ```c++
  cyfre::mat<int> mat_object(cyfre::SCALAR,3,7);

  // mat_object = [[7,0,0],
  //               [0,7,0],
  //               [0,0,7]]
  ```

</details>

<!--=====================================================================================-->
<details>
<summary><b>zero/null matrix</b></summary>
<br>
  
  **construct an zero/null matrix**

  ```c++
  cyfre::mat<int> mat_object(cyfre::NULLZERO,3);

  // mat_object = [[0,0,0],
  //               [0,0,0],
  //               [0,0,0]]
  ```

</details>

<!--=====================================================================================-->
<details>
<summary><b>shaped matrix with values</b></summary>
<br>
  
  **construct an costum shaped matrix, with initial values**

  ```c++
  cyfre::mat<int> mat_object(1,3,5);

  // mat_object = [[5],
  //               [5],
  //               [5]]
  ```

</details>

<!--=====================================================================================-->
<details>
<summary><b>defined matrix</b></summary>
<br>
  
  **construct and define a matrix**

  ```c++
  cyfre::mat<int> mat_object({
    {1,2,3},
    {4,5,6},
    {7,8,9}
  });
  ```

</details>

</details>

--------------------------------------------------

<details>
<summary><b><i>SCALAR OPERATIONS</i></b></summary>
<br>

<!--=====================================================================================-->
<details>
<summary><b>selecting a scalar operation</b></summary>
<br>
  
  **defined** :
  ```c++
  cyfre::SCALAR_OPERATIONS{ADD,SUB,MUL,DIV}
  ```

  <br>

  **use :**
  *cyfre::SCALAR_OPERATION* <br>
  ex:
  ```c++
  cyfre::ADD // to select addition
  ```

<!--=====================================================================================-->
</details>

<details>
<summary><b>matrix scalar operation</b></summary>
<br>

**returns a copy scaled matrix of the original one**

```c++
cyfre::mat<int> mat_object({
  {1,2},
  {3,4}
});

cyfre::mat<int> a = cyfre::scale(mat_object,cyfre::ADD,2);

// a = [[3,4],
//      [5,6]]
```

</details>

<!--=====================================================================================-->
<details>
<summary><b>matrix scalar operation [self]</b></summary>
<br>

**scales all the elements of the matrix using a scalar value [changes the matrix itself]**

```c++
cyfre::mat<int> mat_object({
  {1,2},
  {3,4}
});

mat_object.scale(cyfre::SUB,2);

// mat_object = [[-1,0],
//               [ 1,2]]
```

</details>

<!--=====================================================================================-->
<details>
<summary><b>row scalar operation</b></summary>
<br>

**scales all the elements of the row using a scalar value [changes the matrix itself]**

```c++
cyfre::mat<int> mat_object({
  {1,2},
  {3,4}
});

mat_object.scale_row(0,cyfre::MUL,2);

// mat_object = [[2,4],
//               [3,4]]
```

multiply all elements of the row '0' to 3, changes the original matrix

</details>

<!--=====================================================================================-->
<details>
<summary><b>column scalar operation</b></summary>
<br>

**scales all the elements of the column using a scalar value [changes the matrix itself]**

```c++
cyfre::mat<int> mat_object({
  {2,4},
  {6,8}
});

mat_object.scale_column(1,cyfre::DIV,2);

// mat_object = [[2,2],
//               [6,4]]
```

divides all elements of the column '1' to 2, changes the original matrix

</details>

<!--=====================================================================================-->
<details>
<summary><b>row to row operation</b></summary>
<br>

**scale a row using another row [changes the matrix itself]**

```c++
cyfre::mat<int> mat_object({
  {1,2,3},
  {4,5,6},
  {7,8,9}
});

mat_object.row_operation(1,cyfre::MUL,2);

// mat_object = [[ 1, 2, 3],
//               [28,40,54],
//               [ 7, 8, 9]]
```
</details>

<!--=====================================================================================-->
<details>
<summary><b>column to column operation</b></summary>
<br>

**scale a column using another column [changes the matrix itself]**

```c++
cyfre::mat<int> mat_object({
  {1,2,3},
  {4,5,6},
  {7,8,9}
});

mat_object.column_operation(2,cyfre::DIV,3);

// mat_object = [[ 1, 2, 1],
//               [ 4, 4, 2],
//               [ 7, 8, 3]]
```
</details>

</details>

--------------------------------------------------

<details>
<summary><b><i>MATRIX OPERATIONS</i></b></summary>
<br>

<!--=====================================================================================-->
<details>
<summary><b>matrix addition</b></summary>
<br>

```c++
cyfre::mat<int> A({{ 1, 2, 3},
                   { 4, 5, 6}});

cyfre::mat<int> B({{-1,-2,-3},
                   {-4,-5,-6}});

cyfre::mat<int> C = A+B;

// C = [[ 0, 0, 0],
//      [ 0, 0, 0]]
```
</details>

<!--=====================================================================================-->
<details>
<summary><b>matrix subtraction</b></summary>
<br>

```c++
cyfre::mat<int> A({{10, 1,33},
                   {44,50,12}});

cyfre::mat<int> B({{ 7,19, 5},
                   { 7, 6, 5}});

cyfre::mat<int> C = A-B;

// C = [[ 3,-18,28],
//      [37, 44, 7]]
```
</details>

<!--=====================================================================================-->
<details>
<summary><b>matrix element-by-element division</b></summary>
<br>

```c++
cyfre::mat<int> A({{2,4,6},
                   {8,2,4}});

cyfre::mat<int> B({{1,4,3},
                   {2,2,1}});

cyfre::mat<int> C = A/B;

// C = [[2,1,2],
//      [4,1,4]]
```
</details>

<!--=====================================================================================-->
<details>
<summary><b>hadamard product</b></summary>
<br>

```c++
cyfre::mat<int> A({{2,4,6},
                   {8,2,4}});

cyfre::mat<int> B({{1,4,3},
                   {2,2,1}});

cyfre::mat<int> C = cyfre::hadamard(A,B);

// C = [[ 2,16,18],
//      [16, 4, 4]]
```
</details>

<!--=====================================================================================-->
<details>
<summary><b>multiplying matrices (dot product)</b></summary>
<br>

```c++
cyfre::mat<int> X({
  { 7,12,13},
  {14, 5,20},
  {66,42,-4}
});

cyfre::mat<int> W({{-3,4,56}});

cyfre::mat<int> Y = X*W;

// C = [[3731,2336,-183]]
```
</details>

</details>

--------------------------------------------------

## OTHER METHODS
  
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
