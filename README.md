# cyfre

[![License: MIT](https://img.shields.io/badge/License-MIT-brightgreen.svg)](https://opensource.org/licenses/MIT)
![build-tests](https://github.com/mrdcvlsc/cyfre/actions/workflows/build-tests.yml/badge.svg)

A Templated **C++** matrix library which aims to provide an easy to use interface for basic and intermediate vector-vector, vector-matrix & matrix-matrix operations, and other linear algebra operations.

> [!NOTE]  
> Requires: c++20

<!-- > 
> [!IMPORTANT]  
> Crucial information necessary for users to succeed.

> [!WARNING]  
> Critical content demanding immediate user attention due to potential risks. -->

> [!IMPORTANT]  
> This library is on an ongoing re-write to improve the api and use more modern C++ features. To see the old working implementation of this library check the [version_1.9](https://github.com/mrdcvlsc/cyfre/tree/version_1.9) branch or [download it here](https://github.com/mrdcvlsc/cyfre/tree/version_1.9).

## **Goals**

This library aims to achieve the following features in the future.

1. Provide an easy to use interface zero-cost abstractions.
2. Provide support for different BLAS libraries like OpenBLAS, cuBLAS, etc. as backend to achieve fast performance.
3. Easy to setup, supports different build system for installation.
4. Continually improve the implementation.

For now the library is nowhere near the said features but this is the ultimate goal of the library. Any contributions and help that will make this library one step closer to its goals are welcome.

### **Docs**

1. [Installation (work in progress)](docs/installation.md)
2. [Compilation (work in progress)](docs/compilation.md)
3. [Initialization](docs/initialization.md)
4. [scalar operations with vectors and matrices (not available yet)](docs/scalar-to-vector-and-matrix.md)
5. [vector-vector operations (not available yet)](docs/vector-vector.md)
6. [vector-matrix operations (not available yet)](docs/vector-matrix.md)
7. [matrix-matrix operations (not available yet)](docs/matrix-matrix.md)

### **About**

This repository started in december 2020 as a personal **hobby** project **not intended** to replace big matrix libraries like [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page), [OpenCV's - cv::Mat](https://docs.opencv.org/4.x/d3/d63/classcv_1_1Mat.html) or [BLAS](https://www.netlib.org/blas/) and is **only for didactic purposes**. Though performance is still a priority, meaning this library will... as much as possible, use the fastest and the most efficient algorithms and implementations THAT THE AUTHOR(s) KNOW OF.