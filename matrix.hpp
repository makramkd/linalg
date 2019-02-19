#ifndef PARMAT_MATRIX_HPP
#define PARMAT_MATRIX_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdint>

namespace parmat {

  // TODO: concept for T
  template <typename T>
  class matrix {
    public:
      typedef uint64_t size_type;

      // Construct default initialized matrix
      matrix(size_type rows, size_type columns)
      : _mat(rows * columns),
        rows(rows),
        cols(columns)
      {
      }

      // Fill matrix with given filler value (e.g, 0)
      matrix(size_type rows, size_type columns, T filler)
      : _mat(rows * columns),
        rows(rows),
        cols(columns)
      {
        std::fill(this->_mat.begin(), this->_mat.end(), filler);
      }

      matrix(const matrix& other)
      : _mat(other._mat),
        rows(other.rows),
        cols(other.cols)
      {
      }

      matrix(matrix&& other)
      : _mat(std::move(other._mat)),
        rows(std::move(other.rows)),
        cols(std::move(other.cols))
      {
      }

      matrix& operator=(const matrix& other)
      {
        this->_mat = other._mat;
        this->rows = other.rows;
        this->cols = other.cols;

        return *this;
      }

      matrix& operator+=(const matrix& rhs) {
        // TODO: should this be done depending on how big the matrix is?
        #pragma omp parallel for
        for (auto i = 0; i < row_count(); ++i) {
          for (auto j = 0; j < col_count(); ++j) {
            this->operator()(i, j) = this->operator()(i, j) + rhs(i, j);
          }
        }
        return *this;
      }

      // Get element at index (i, j)
      const T& operator()(size_type i, size_type j) const {
        return this->_mat[i * this->cols + j];
      }

      // Lvalue reference to element at index (i, j)
      T& operator()(size_type i, size_type j) {
        return this->_mat[i * this->cols + j];
      }

      size_type row_count() const {
        return this->rows;
      }

      size_type col_count() const {
        return this->cols;
      }
    private:
      std::vector<T> _mat;
      size_type rows;
      size_type cols;
  };

  template <typename T>
  std::ostream& operator<<(std::ostream& os, const matrix<T>& m) {
    os << "[";
    for (auto i = 0; i < m.row_count(); ++i) {
      for (auto j = 0; j < m.col_count(); ++j) {
        if (j != m.col_count() - 1) {
          os << m(i, j) << ", ";
        } else {
          os << m(i, j);
        }
      }
      if (i != m.row_count() - 1) {
        os << ";" << std::endl;
      }
    }
    os << "]";
    return os;
  }

  template <typename T>
  matrix<T> identity(uint32_t size) {
    auto mat = matrix<T>(size, size);
    // TODO: should this be done depending on how big the matrix is?
    #pragma omp parallel for
    for (auto i = 0; i < mat.row_count(); ++i) {
      mat(i, i) = 1;
    }
    return mat;
  }
}

#endif // PARMAT_MATRIX_HPP
