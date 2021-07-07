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
  cyfre::mat<int> mat_object(cyfre::IDENTITY,3);  /*

  mat_object = [[1,0,0],
                [0,1,0],
                [0,0,1]]

  */
  ```

</details>

<!--=====================================================================================-->
<details>
<summary><b>scalar matrix</b></summary>
<br>
  
  **construct an scalar matrix**

  ```c++
  cyfre::mat<int> mat_object(cyfre::SCALAR,3,7);  /*

  mat_object = [[7,0,0],
                [0,7,0],
                [0,0,7]]

  */
  ```

</details>

<!--=====================================================================================-->
<details>
<summary><b>zero/null matrix</b></summary>
<br>
  
  **construct an zero/null matrix**

  ```c++
  cyfre::mat<int> mat_object(cyfre::NULLZERO,3);  /*

  mat_object = [[0,0,0],
                [0,0,0],
                [0,0,0]]

  */
  ```

</details>

<!--=====================================================================================-->
<details>
<summary><b>shaped matrix with values</b></summary>
<br>
  
  **construct an costum shaped matrix, with initial values**

  ```c++
  cyfre::mat<int> mat_object(1,3,5);  /*

  mat_object = [[5],
                [5],
                [5]]

  */
  ```

</details>

<!--=====================================================================================-->
<details>
<summary><b>defined matrix (row)</b></summary>
<br>
  
  **construct and define a matrix**

  ```c++
  cyfre::mat<int> mat_object({5,10,15,20,25});

  // mat_object = [[5,10,15,20,25]] <-- (1x5 matrix)
  ```

</details>

<!--=====================================================================================-->
<details>
<summary><b>defined matrix (2D)</b></summary>
<br>
  
  **construct and define a matrix**

  ```c++
  cyfre::mat<int> mat_object({
    {1,2,3},
    {4,5,6},
    {7,8,9}
  });

  /*
    mat_object = [[1,2,3],
                  [4,5,6],
                  [7,8,9]]
  */
  ```

</details>

<!--=====================================================================================-->
<details>
<summary><b>read matrix from a txt file</b></summary>
<br>

  *matrix1.txt*

  ```txt
  23 12 53 34 23
  33 77 53 90 28
  87 26 11 24 31
  84 32 73 64 26
  77 88 45 97 86
  ```

  ```c++
  cyfre::mat<int> mat_object("matrix1.txt",' ');  /*

  mat_object = [
    [23,12,53,34,23]
    [33,77,53,90,28]
    [87,26,11,24,31]
    [84,32,73,64,26]
    [77,88,45,97,86]
  ]

  */
  ```

</details>

</details>

--------------------------------------------------

<details>
<summary><b><i>ELEMENTARY ROW/COLUMN OPERATIONS</i></b></summary>
<br>

**ROWS**
- row_swap(size_t,size_t)
- row_scale(S,size_t)
- row_scale(S,size_t,size_t)

**COLUMNS**
- column_swap(size_t,size_t)
- column_scale(S,size_t)
- column_scale(S,size_t,size_t)

<!--=====================================================================================-->
<details>
<summary><b>swaping rows/columns</b></summary>
<br>

**row_swap(row1,row2)**

```c++
cyfre::mat<int> mat_object({
  {1,2,3},
  {4,5,6},
  {7,8,9}
});

mat_object.row_swap(1,2);  /*

mat_object = [[ 1, 2, 3],
              [ 7, 8, 9],
              [ 4, 5, 6]]

*/
```
</details>

<!--=====================================================================================-->
<details>
<summary><b>scaling rows/columns</b></summary>
<br>

**row_scale(scalar_value,row_to_scale)**

```c++
cyfre::mat<int> mat_object({
  {1,2,3},
  {4,5,6},
  {7,8,9}
});

mat_object.row_scale(5,0);  /*

mat_object = [[ 5,10,15],
              [ 4, 5, 6],
              [ 7, 8, 9]]

*/
```
</details>

<!--=====================================================================================-->
<details>
<summary><b>scale a row/column then add the products to another row</b></summary>
<br>

**row_scale(scalar_value,row_to_scale,base_row)**

```c++
cyfre::mat<int> mat_object({
  {1,2,3},
  {4,5,6},
  {0,0,0}
});

mat_object.row_scale(7,0,2);  /*

mat_object = [[ 1, 2, 3],
              [ 4, 5, 6],
              [ 7,14,21]]

*/
```
</details>

</details>

--------------------------------------------------

<details>
<summary><b><i>ADDITIONAL SCALAR OPERATIONS</i></b></summary>
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

cyfre::mat<int> a = mat_object+2;  /*

a = [[3,4],
     [5,6]]

NOTE : cyfre::mat<int> a = 2+mat_object;  <-- is also a valid expression

*/
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

mat_object-=2;  /*

mat_object = [[-1,0],
              [ 1,2]]

*/
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

mat_object.scale_row(0,cyfre::MUL,2);  /*

mat_object = [[2,4],
              [3,4]]

*/
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

mat_object.scale_column(1,cyfre::DIV,2);  /*

mat_object = [[2,2],
              [6,4]]

*/
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

mat_object.row_operation(1,cyfre::MUL,2);  /*

mat_object = [[ 1, 2, 3],
              [28,40,54],
              [ 7, 8, 9]]

*/
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

mat_object.column_operation(2,cyfre::DIV,3); /*

mat_object = [[ 1, 2, 1],
              [ 4, 4, 2],
              [ 7, 8, 3]]

*/
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

cyfre::mat<int> C = A+B; /*

C = [[ 0, 0, 0],
     [ 0, 0, 0]]

*/
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

cyfre::mat<int> C = A-B; /*

C = [[ 3,-18,28],
     [37, 44, 7]]

*/
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

cyfre::mat<int> C = A/B; /*

C = [[2,1,2],
     [4,1,4]]

*/
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

cyfre::mat<int> C = cyfre::hadamard(A,B); /*

C = [[ 2,16,18],
     [16, 4, 4]]

*/

A.hadamard(B); /* faster in some cases because of direct operation on the A matrix

A = [[ 2,16,18],
     [16, 4, 4]]

*/
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

<details>
<summary><b><i>METHODS</i></b></summary>
<br>

<!--=====================================================================================-->
<details>
<summary><b>Applying functions to all elements of the matrix</b></summary>
<br>

**.apply() is a shortcut method for applying a function to all elements of a matrix**

```c++

int square(int x) { return x*x; }

cyfre::mat<int> X({
  {23,12,53,34,23},
  {33,77,53,90,28},
  {87,26,11,24,31},
  {84,32,73,64,26},
  {77,88,45,97,86}
});

X.apply(square);  /*

X = [[529 144  2809 1156 529],
    [1089 5929 2809 8100 784],
    [7569 676  121  576  961],
    [7056 1024 5329 4096 676],
    [5929 7744 2025 9409 7396]]

*/
```
**NOTE:**
  - the function should only have one parameter
  - the function's return type, and parameter type should be the same as the matrix type

</details>

<!--=====================================================================================-->
<details>
<summary><b>sum of all elements</b></summary>
<br>

```c++
cyfre::mat<int> X({
  {1,2,3},
  {4,5,6},
  {7,8,9}
});

int sum = X.total();

// sum = 45

```
</details>

<!--=====================================================================================-->
<details>
<summary><b>sum of the main-diagonal</b></summary>
<br>

```c++
cyfre::mat<int> X({
  {1,2,3},
  {4,5,6},
  {7,8,9}
});

int diag_sum = X.trace();

// diag_sum = 15

```
</details>

<!--=====================================================================================-->
<details>
<summary><b>getting row/column as std::vector</b></summary>
<br>

```c++
cyfre::mat<int> plane({
  {1,2,3},
  {4,5,6},
  {7,8,9}
});

std::vector<int> x = plane.row(1);  
std::vector<int> y = plane.column(1);

/*

x = [4,5,6]
y = [2,5,8]

*/
```
</details>

<!--=====================================================================================-->
<details>
<summary><b>getting row/column as std::vector of std::iterators</b></summary>
<br>

- **you can modify values of rows and columns using a vector of iterator from a matrix**

```c++
cyfre::mat<int> P({
  { 30, 40, 42},
  { 10, 25, 90},
  {102, 88,150}
});

std::vector<typename std::vector<int>::iterator> xaxis = P.row_iterators_r(1);
std::vector<typename std::vector<int>::iterator> yaxis = P.column_iterators_r(1);

for(size_t i=0; i<3; ++i)
{
    *xaxis[i] = 1;
    *yaxis[i] = 1;
}   /*

X = [[30    1    42],
     [1     1     1],
     [102   1   150]]

*/

```

- *for vectors of const_iterator use the method below instead*

```c++
std::vector<typename std::vector<int>::const_iterator> xaxis = P.row_iterators(1);
std::vector<typename std::vector<int>::const_iterator> yaxis = P.column_iterators(1);
```

</details>

<!--=====================================================================================-->
<details>
<summary><b>Transpose of a Matrix</b></summary>
<br>

```c++
cyfre::mat<int> X({
  {1,2,3,4},
  {5,6,7,8},
});

X.transpose();

/*

X = [[1,5],
     [2,6],
     [3,7],
     [4,8]]

*/

```
</details>

<!--=====================================================================================-->
<details>
<summary><b>rasing a matrix to a certain power</b></summary>
<br>

```c++
cyfre::mat<int> X({
  { 7,12,13},
  {14, 5,20},
  {66,42,-4}
});


cyfre::mat<int> X_cubed = cyfre::power(X,3);  /*

X_cubed = [[32427  23838 25975],
           [37818  28389 38636],
           [128454 83358 17402]]

*/

cyfre::mat<int> X_squared = X;
X_squared.power(2); /*

X_squared = [[1047 666  239],
             [1488 1005 202],
             [786  702  1714]]

*/

```
</details>

<!--=====================================================================================-->
<details>
<summary><b>Determinant of a Matrix</b></summary>
<br>

```c++
cyfre::mat<long double> X({
  { 5, 10,-15,  20},
  {30,-35,-40, -45},
  {55, 60, 75, -80},
  {90, 95,100,-105}
});

long double determinant = cyfre::det(X);  /*

determiant = -720000

*/

```
</details>

<!--=====================================================================================-->
<details>
<summary><b>Inverse of a Matrix</b></summary>
<br>

```c++
cyfre::mat<long double> X({
  {23,12,53},
  {33,77,53},
  {87,26,11}
});

X.inv();  /* or  X = cyfre::inv(X);

X = [[0.00196078 -0.00460101 0.0127211],
     [-0.0156863 0.0160925 -0.00195709],
     [0.0215686 -0.00164691 -0.00507736]]

*/

```
</details>

<!--=====================================================================================-->
<details>
<summary><b>Echelon Forms (ref & rref)</b></summary>
<br>

**R***educe* **R***ow* **E***chelon* **F***orm*

```c++
cyfre::mat<int> X({
  {1,2,3,4},
  {5,6,7,8},
  {-2,3,-4,1}
});

X = cyfre::rref(X);

/* or

X.rref();

X = [[1 0 0 -1],
    [0 1 0 1],
    [0 0 1 1]]

*/
```

**R***ow* **E***echelon* **F***orm* : **```X.ref()```** *or* **```X = cyfre::ref(X)```**

</details>

</details>
  
--------------------------------------------------

<details>
<summary><b>mat members: matrix, height, & width</b></summary>
<br>

**operator(i,j)** - performs check of indices, terminates program if indices are out of range

**.matrix[i][j]** - direct access, no checks, faster way

```c++
  cyfre::mat<int> nums(
    {{1,2,3},
     {4,5,6},
     {7,8,9}
  });
  
  for(size_t i=0; i<nums.height; ++i)
  {
    for(size_t j=0; j<nums.width; ++j)
    {
      /* operator() */

      nums(i,j)*=2;
      std::cout<<nums(i,j)<<'\t';


      /* direct access

      nums.matrix[i][j]*=2;
      std::cout<<nums.matrix[i][j]<<'\t';

      */
    }
    std::cout<<'\n';
  }

```

**output :**
```
2       4       6
8       10      12
14      16      18
```
  
</details>

--------------------------------------------------

<details>
<summary><b><i>STATISTICS</i></b></summary>
<br>

<!--=====================================================================================-->
<details>
<summary><b>mean, median, mode</b></summary>
<br>

```c++
cyfre::mat<short> X({
  {7,2,4},
  {4,7,6},
  {7,4,9}
});

long double mean   = cyfre::sts::mean(X);
long double median = cyfre::sts::median(X);

std::pair<size_t,std::vector<short>> getmode = cyfre::sts::mode(X);

size_t numbers_of_modes  = getmode.second.size();
size_t modes_occurrence  = getmode.first;

std::vector<short> modes = getmode.second;

/*
  mean = 3.22222
  median = 7
  numbers_of_modes = 2
  modes_occurrence = 3
  modes = [7,4]
*/

```
</details>

<!--=====================================================================================-->
<details>
<summary><b>sum of squares, variance, standard deviation</b></summary>
<br>

```c++
cyfre::mat<short> X({7,2,4,3,9});

long double
  sum_of_square      = cyfre::sts::sofs(X,cyfre::SAMPLE),
  variance           = cyfre::sts::variance(X,cyfre::SAMPLE),
  standard_deviation = cyfre::sts::stddvn(X,cyfre::SAMPLE);;

/*
  sum_of_square = 34
  variance = 8.5
  standard_deviation = 2.91548

  for population use 'cyfre::POPULATION' instead
*/
```
</details>

</details>