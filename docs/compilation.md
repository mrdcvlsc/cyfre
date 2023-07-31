[[< Previous](installation.md)] | [[Home](../README.md)] | [[Next >](initialization.md)]

# Compiling Programs with Cyfre (WIP)

[!NOTE]  
> Recomended requirements during compilation

| Compiler Version | Required Flags |
| --- | --- |
| GCC 8 to 9 | `-std=c++2a` |
| GCC 10 or higher | `-std=c++20` |
| clang 9 | `-std=c++2a` |
| clang 10 or higher | `-std=c++20` |

Visual Studio 2019 supports all C++20 features through its `/std:c++latest` option, as of **version 16.10.0**.

An option `/std:c++20`` to enable C++20 mode is added in **version 16.11.0**.

Project properties → Configuration properties → C/C++ → Language → C++ Language Standard.

-----

[[< Previous](installation.md)] | [[Home](../README.md)] | [[Next >](initialization.md)]