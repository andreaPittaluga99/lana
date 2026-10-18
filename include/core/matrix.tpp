namespace lana {

// constructors
template <typename T>
matrix<T>::matrix(const std::size_t r, const std::size_t c)
    : rows_(r), columns_(c), data_(r * c, T{}) {}

template <typename T>
matrix<T>::matrix(const std::size_t r, const std::size_t c, const T& value)
    : rows_(r), columns_(c), data_(r * c, value) {}

template <typename T>
matrix<T>::matrix(std::initializer_list<std::initializer_list<T>> list)
    : rows_(list.size()), columns_((rows_ > 0) ? list.begin()->size() : 0) {
    this->data_.reserve(this->rows_ * this->columns_);

    // check if rows are uniform
    // we dont copy the data here because we dont want to waste time
    // if there are any error in the argument list
    for (const auto& row : list) {
        if (row.size() != this->columns_)
            throw std::invalid_argument(
                "lana::matrix constructor error: rows are not uniform");
    }
    // if all rows are uniform, we copy the data
    for (const auto& row : list) {
        for (auto& value : row) {
            this->data_.push_back(value);
        }
    }
}

template <typename T>
matrix<T> matrix<T>::zeros(const std::size_t r, const std::size_t c) {
    return matrix<T>(r, c, T{0});
}

template <typename T>
matrix<T> matrix<T>::ones(const std::size_t r, const std::size_t c) {
    return matrix<T>(r, c, T{1});
}

template <typename T>
matrix<T> matrix<T>::identity(const std::size_t n) {
    matrix<T> ret = zeros(n, n);
    for (std::size_t i = 0; i < n; ++i) {
        ret(i, i) = T{1};
    }
    return ret;
}

// operator overloads
template <typename T>
T& matrix<T>::operator()(const std::size_t r, const std::size_t c) {
    if (r >= rows_ || c >= columns_)
        throw std::out_of_range(
            "lana::matrix::operator() error: index out of range");
    return data_[r * row_stride() + c * columns_stride()];
}

template <typename T>
const T& matrix<T>::operator()(const std::size_t r, const std::size_t c) const {
    if (r >= rows_ || c >= columns_)
        throw std::out_of_range(
            "lana::matrix::operator() error: index out of range");
    return data_[r * row_stride() + c * columns_stride()];
}

template <typename T>
bool matrix<T>::operator==(const matrix<T>& other) const {
    if (this->rows_ != other.rows_ || this->columns_ != other.columns_) {
        return false;
    }

    for (std::size_t i = 0; i < this->data_.size(); ++i) {
        if (this->data_[i] != other.data_[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
matrix<T> matrix<T>::operator+(const matrix<T>& other) const {
    if (this->columns_ != other.columns_ || this->rows_ != other.rows_) {
        throw std::invalid_argument(
            "lana::operator+ error: matrices have incompatible dimensions");
    }
    matrix<T> ret = *this;
    for (std::size_t i = 0; i < this->data_.size(); ++i) {
        ret.data_[i] += other.data_[i];
    }
    return ret;
}

template <typename T>
matrix<T>& matrix<T>::operator+=(const matrix<T>& other) {
    if (this->columns_ != other.columns_ || this->rows_ != other.rows_) {
        throw std::invalid_argument(
            "lana::operator+ error: matrices have incompatible dimensions");
    }
    for (std::size_t i = 0; i < this->data_.size(); i++) {
        this->data_[i] += other.data_[i];
    }
    return *this;
}

template <typename T>
matrix<T> matrix<T>::operator-(const matrix<T>& other) const {
    if (this->columns_ != other.columns_ || this->rows_ != other.rows_) {
        throw std::invalid_argument(
            "lana::operator+ error: matrices have incompatible dimensions");
    }
    matrix<T> ret = *this;
    for (std::size_t i = 0; i < this->data_.size(); ++i) {
        ret.data_[i] -= other.data_[i];
    }
    return ret;
}

template <typename T>
matrix<T>& matrix<T>::operator-=(const matrix& other) {
    if (this->columns_ != other.columns_ || this->rows_ != other.rows_) {
        throw std::invalid_argument(
            "lana::operator+ error: matrices have incompatible dimensions");
    }
    for (std::size_t i = 0; i < this->data_.size(); i++) {
        this->data_[i] -= other.data_[i];
    }
    return *this;
}

// op
template <typename T>
matrix<T> matrix<T>::transpose() const {
    matrix<T> ret(this->columns_, this->rows_);
    for (std::size_t r = 0; r < this->rows_; r++) {
        for (std::size_t c = 0; c < this->columns_; ++c) {
            ret(c, r) = (*this)(r, c);
        }
    }
    return ret;
}

// checks
template <typename T>
bool matrix<T>::is_upper_triangular() const noexcept {
    // m is upper triangular if m(i, j) == 0 for all i > j
    if (this->rows_ != this->columns_) return false;

    for (std::size_t i = 1; i < this->rows_; ++i) {
        for (std::size_t j = 0; j < i; ++j) {
            if ((*this)(i, j) != 0) {
                return false;
            }
        }
    }
    return true;
}

template <typename T>
bool matrix<T>::is_strictly_upper_triangular() const noexcept {
    // m is strictly upper triangular if m(i, j) == 0 for all i >= j
    if (this->rows_ != this->columns_) return false;

    for (std::size_t i = 0; i < this->rows_; ++i) {
        for (std::size_t j = 0; j <= i; ++j) {
            if ((*this)(i, j) != 0) {
                return false;
            }
        }
    }
    return true;
}

template <typename T>
bool matrix<T>::is_lower_triangular() const noexcept {
    // m is lower triangular if m(i, j) == 0 for all i < j
    if (this->rows_ != this->columns_) return false;

    for (std::size_t i = 0; i < this->rows_; ++i) {
        for (std::size_t j = i + 1; j < this->columns_; ++j) {
            if ((*this)(i, j) != 0) {
                return false;
            }
        }
    }
    return true;
}

template <typename T>
bool matrix<T>::is_strictly_lower_triangular() const noexcept {
    // m is lower triangular if m(i, j) == 0 for all i <= j
    if (this->rows_ != this->columns_) return false;

    for (std::size_t i = 0; i < this->rows_; ++i) {
        for (std::size_t j = i; j < this->columns_; ++j) {
            if ((*this)(i, j) != 0) {
                return false;
            }
        }
    }
    return true;
}

template <typename T>
bool matrix<T>::is_diagonal() const noexcept {
    // m is diagonal if is both upper and lower triangular
    // so m(i, j) == 0 for all i != j
    if (this->rows_ != this->columns_) return false;

    for (std::size_t i = 0; i < this->rows_; ++i) {
        for (std::size_t j = 0; j < this->columns_; ++j) {
            if (i != j && (*this)(i, j) != 0) {
                return false;
            }
        }
    }
    return true;
}

template <typename T>
bool matrix<T>::is_symmetric() const noexcept {
    // m is symmetric if m == m.transposed
    //  so m is symmetric if m is a square matrix and m(i, j) == m(j, i)
    if (this->rows_ != this->columns_) return false;

    for (std::size_t i = 0; i < this->rows_; ++i) {
        for (std::size_t j = 0; j < this->columns_; ++j) {
            if ((*this)(i, j) != (*this)(j, i)) {
                return false;
            }
        }
    }
    return true;
}

}  // namespace lana