#ifndef PARMAT_MATRIX_HPP
#define PARMAT_MATRIX_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <initializer_list>
#include <cstdint>
#include <cassert>

namespace parmat {

  // TODO: concept for T
  template <typename T>
  class matrix {
    public:
      typedef uint64_t size_type;

      // Dtor
      ~matrix(){}

      // Useless default ctor
      matrix()
      : _mat(0),
        rows(0),
        cols(0)
      {
      }

      matrix(size_type rows, size_type columns, const std::initializer_list<T>& init_list)
      : _mat(rows * columns),
        rows(rows),
        cols(columns)
      {
        if (init_list.size() == (rows * cols)) {
          std::copy(init_list.begin(), init_list.end(), this->_mat.begin());
        }
      }

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
        if (this != &other) {
          this->_mat = other._mat;
          this->rows = other.rows;
          this->cols = other.cols;
        }
        return *this;
      }

      matrix& operator=(matrix&& other)
      {
        // TODO: check similar to copy assignment operator?
        this->_mat = std::move(other._mat);
        this->rows = std::move(other.rows);
        this->cols = std::move(other.cols);

        return *this;
      }

      matrix& operator+=(const matrix& rhs) {
        // TODO: error handling?
        assert(this->rows == rhs.rows);
        assert(this->cols == rhs.cols);

        for (size_type i = 0; i < this->rows; ++i) {
          #pragma omp parallel for
          for (size_type j = 0; j < this->cols; ++j) {
            this->operator()(i, j) += rhs(i, j);
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
    using size_type = typename matrix<T>::size_type;
    os << "[";
    for (size_type i = 0; i < m.row_count(); ++i) {
      for (size_type j = 0; j < m.col_count(); ++j) {
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
    os << "]\n";
    return os;
  }

  template <typename T>
  matrix<T> identity(typename matrix<T>::size_type size, T identity) {
    auto mat = matrix<T>(size, size);
    // TODO: should this be done depending on how big the matrix is?
    using size_type = typename matrix<T>::size_type;
    #pragma omp parallel for
    for (size_type i = 0; i < mat.row_count(); ++i) {
      mat(i, i) = identity;
    }
    return mat;
  }
}

#endif // PARMAT_MATRIX_HPP
