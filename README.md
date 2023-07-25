# cyfre

[![License: MIT](https://img.shields.io/badge/License-MIT-brightgreen.svg)](https://opensource.org/licenses/MIT)
![build-tests](https://github.com/mrdcvlsc/cyfre/actions/workflows/build-tests.yml/badge.svg)

A Templated **C++20** matrix library which aims to provide an easy to use interface for basic and intermediate vector-vector, vector-matrix & matrix-matrix operations.

<!-- > [!NOTE]  
> Highlights information that users should take into account, even when skimming.

> [!IMPORTANT]  
> Crucial information necessary for users to succeed.

> [!WARNING]  
> Critical content demanding immediate user attention due to potential risks. -->

> [!IMPORTANT]  
> This library is on an ongoing re-write to improve the api and use more modern C++ features. To see the old working implementation of this library check the [version_1.9](https://github.com/mrdcvlsc/cyfre/tree/version_1.9) branch or [download it here](https://github.com/mrdcvlsc/cyfre/tree/version_1.9).

### **Docs**

1. [Initialization](docs/initialization.md)
2. [vector-vector (not available yet)](docs/initialization.md)
3. [vector-matrix (not available yet)](docs/initialization.md)
4. [matrix-matrix (not available yet)](docs/initialization.md)

### **About**

This repository started in december 2020 as a personal hobby project **not intended** to replace big matrix libraries like [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page), [OpenCV's - cv::Mat](https://docs.opencv.org/4.x/d3/d63/classcv_1_1Mat.html) or [BLAS](https://www.netlib.org/blas/) and is **only for didactic purposes**. Though performance is still a priority, meaning this library will... as much as possible, use the fastest and the most efficient algorithms and implementations THAT THE AUTHOR(s) KNOW OF.