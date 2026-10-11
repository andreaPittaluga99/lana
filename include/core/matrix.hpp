#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <vector>

namespace lana {

template <typename T>
class matrix {
   public:
    // constructors
    matrix(std::size_t r, std::size_t c);
    matrix(const matrix& mat) = default;
    matrix(std::initializer_list<std::initializer_list<T>> list);
    static matrix zeros(const std::size_t r, const std::size_t c);
    static matrix ones(const std::size_t r, const std::size_t c);
    static matrix identity(const std::size_t n);

    // getters
    std::size_t rows() const noexcept { return rows_; }
    std::size_t columns() const noexcept { return columns_; }

    // operator overload
    T& operator()(const std::size_t r, const std::size_t c);
    const T& operator()(const std::size_t r, const std::size_t c) const;

    // op
    matrix transpose() const;

    // checks
    bool is_upper_triangular() const noexcept;

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