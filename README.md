# linalg

Some parallelized linear algebra routines written in C++.

Meant to be a header-only library with no dependencies other than standard C++.

Tests will use [googletest](https://github.com/google/googletest) and benchmarks will use [benchmark](https://github.com/google/benchmark).

# Build

This repo requires OpenMP. As such, you need an OpenMP compliant compiler.
See [here](https://www.openmp.org/resources/openmp-compilers-tools/) for compilers that support OpenMP.

# Project Goals

* Use C++ concepts to constrain template parameters to valid values. E.g, in order to place a type inside a matrix, you need to define addition, multiplication, subtraction, etc. for your type.
* Parallelize algorithms where possible. Lots of linear algebra algorithms are embarassingly parallel problems. Harness the simplicity of OpenMP to easily parallelize for loops, at the very least.
* Unit tests for all algorithms.
* Benchmarks for all algorithms, compared with the state of the art. I don't expect to write faster code, but I do hope to be in the same ball park, with hopefully more readable code than LAPACK.
* Easily include-able into other projects via a single (not sure yet) header.
* Simple looking code.
* Binary serialization/deserialization of matrices. This is so that data can be saved/loaded efficiently in terms of both space and time, similar to what `pickle` is for Python applications.
