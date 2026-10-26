#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace lana {

template <typename T>
class matrix {
   public:
    // constructors
    matrix(const std::size_t r, const std::size_t c);
    matrix(const std::size_t r, const std::size_t c, const T& value);
    matrix(const matrix& mat) = default;
    matrix(std::initializer_list<std::initializer_list<T>> list);
    static matrix zeros(const std::size_t r, const std::size_t c);
    static matrix ones(const std::size_t r, const std::size_t c);
    static matrix identity(const std::size_t n);

    // getters
    std::size_t rows() const noexcept { return rows_; }
    std::size_t columns() const noexcept { return columns_; }

    // iterators
    std::vector<T>::iterator begin() noexcept;
    std::vector<T>::iterator end() noexcept;

    std::vector<T>::const_iterator begin() const noexcept;
    std::vector<T>::const_iterator end() const noexcept;

    std::vector<T>::const_iterator cbegin() const noexcept;
    std::vector<T>::const_iterator cend() const noexcept;

    // operator overload
    T& operator()(const std::size_t r, const std::size_t c);
    const T& operator()(const std::size_t r, const std::size_t c) const;

    bool operator==(const matrix& other) const;
    bool operator!=(const matrix& other) const;

    matrix operator+(const matrix& other) const;
    matrix& operator+=(const matrix& other);
    matrix operator-(const matrix& other) const;
    matrix& operator-=(const matrix& other);
    matrix operator*(const matrix& other) const;
    matrix& operator*=(const matrix& other);

    template <typename S>
    matrix<std::common_type_t<T, S>> operator*(const S scalar) const;

    // op
    matrix transpose() const;

    // checks
    bool is_upper_triangular() const noexcept;
    bool is_strictly_upper_triangular() const noexcept;
    bool is_lower_triangular() const noexcept;
    bool is_strictly_lower_triangular() const noexcept;
    bool is_diagonal() const noexcept;
    bool is_symmetric() const noexcept;

   private:
    std::size_t rows_;
    std::size_t columns_;
    std::vector<T> data_;

    // stride
    std::size_t row_stride() const noexcept { return columns_; }
    std::size_t columns_stride() const noexcept { return 1; }
};

}  // namespace lana

#include "matrix.tpp"

#endif