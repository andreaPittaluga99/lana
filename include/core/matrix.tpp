namespace lana {

// constructors
template <typename T>
matrix<T>::matrix(const std::size_t r, const std::size_t c)
    : rows_(r), columns_(c), data_(r * c, T{}) {}

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
}  // namespace lana