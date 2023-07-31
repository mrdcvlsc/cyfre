[[< Previous](compilation.md)] | [[Home](../README.md)] | [[Next >](scalar-to-vector-and-matrix.md)]

# Initialization (WIP)

When initializing a matrix this library offers a way to either allocate on stack or to allocate in heap.

### Stack allocation initialization

Here's how to allocate on stack, notice that we specify the dimension of the matrix inside template argument of `fixed`.

```c++
cyfre::mat<float, cyfre::fixed<4, 4>> matrix;
```

### Heap allocation initialization

Similarly here's how to allocate on the heap, the difference here is we used the `dynamic` allocation type to specify that we want a matrix in the heap, **also notice here that the size is provided in the constructor instead of the template arguments**.

```c++
cyfre::mat<float, cyfre::dynamic> matrix(4, 4);
```

### Namespace advice

Most people would use the namespace to shorten the declarations, and others will use a type definition or macro.

```c++
using namespace cyfre;
```

I would advice to use the new using keyword instead, first of all using namespace might cause some redefinitions, also using a typedef with the class provided by the `cyfre` namespace most of the time will not work since most of them are template classes.

```c++
// this things will not work
typedef cyfre::mat mat;
typedef cyfre::fixed fixed;
typedef cyfre::dynamic dynamic;
```

So it is suggested to use the using keyword.

```c++
using cyfre::mat;
using cyfre::dynamic;
using cyfre::fixed;
```

This way you can shorten the declarations like this.

```c++
mat<float, fixed<4, 4>> matrix1;
mat<float, dynamic> matrix2(4, 4);
```

-----

[[< Previous](compilation.md)] | [[Home](../README.md)] | [[Next >](scalar-to-vector-and-matrix.md)]
