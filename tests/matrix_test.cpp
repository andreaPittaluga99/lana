#include "matrix.hpp"

#include <gtest/gtest.h>

TEST(MatrixConstructors, InitList) {
    lana::matrix<int> m({{1, 2, 3}, {1, 2, 3}, {1, 2, 3}});

    EXPECT_EQ(m.rows(), 3);
    EXPECT_EQ(m.columns(), 3);

    EXPECT_EQ(m(0, 0), 1);
    EXPECT_EQ(m(0, 1), 2);
    EXPECT_EQ(m(0, 2), 3);

    EXPECT_EQ(m(1, 0), 1);
    EXPECT_EQ(m(1, 1), 2);
    EXPECT_EQ(m(1, 2), 3);

    EXPECT_EQ(m(2, 0), 1);
    EXPECT_EQ(m(2, 1), 2);
    EXPECT_EQ(m(2, 2), 3);
}

TEST(MatrixConstructors, InitListVector_1xn) {
    lana::matrix<int> m({{1, 2, 3}});

    EXPECT_EQ(m.rows(), 1);
    EXPECT_EQ(m.columns(), 3);

    EXPECT_EQ(m(0, 0), 1);
    EXPECT_EQ(m(0, 1), 2);
    EXPECT_EQ(m(0, 2), 3);
}

TEST(MatrixConstructors, InitListVector_nx1) {
    lana::matrix<int> m({{1}, {2}, {3}});

    EXPECT_EQ(m.rows(), 3);
    EXPECT_EQ(m.columns(), 1);

    EXPECT_EQ(m(0, 0), 1);
    EXPECT_EQ(m(1, 0), 2);
    EXPECT_EQ(m(2, 0), 3);
}

TEST(MatrixConstructors, InitListRejectsUnequalRows) {
    EXPECT_THROW((lana::matrix<int>{{1, 2}, {3}}), std::invalid_argument);
}

TEST(MatrixTranspose, RectangularMatrix) {
    lana::matrix<int> m({{1, 2, 3}, {4, 5, 6}});

    auto t = m.transpose();

    EXPECT_EQ(t.rows(), 3);
    EXPECT_EQ(t.columns(), 2);

    EXPECT_EQ(t(0, 0), 1);
    EXPECT_EQ(t(0, 1), 4);
    EXPECT_EQ(t(1, 0), 2);
    EXPECT_EQ(t(1, 1), 5);
    EXPECT_EQ(t(2, 0), 3);
    EXPECT_EQ(t(2, 1), 6);

    // original matrix should remain the same
    EXPECT_EQ(m(0, 1), 2);
    EXPECT_EQ(m(1, 0), 4);
}

TEST(IsUpperTriangular, Positive) {
    lana::matrix<int> m{{2, 10, -1}, {0, 1, 0}, {0, 0, 3}};
    EXPECT_TRUE(m.is_upper_triangular());

    lana::matrix<int> u{{1}};
    EXPECT_TRUE(u.is_upper_triangular());
}

TEST(IsUpperTriangular, Negative) {
    lana::matrix<int> m{{0, 0, -1}, {1, 1, 0}, {0, 0, 0}};
    EXPECT_FALSE(m.is_upper_triangular());
}

TEST(IsStrictlyUpperTriangular, Positive) {
    lana::matrix<int> m{{0, 1, 2, 3}, {0, 0, 1, 2}, {0, 0, 0, 1}, {0, 0, 0, 0}};
    EXPECT_TRUE(m.is_strictly_upper_triangular());

    lana::matrix<int> u{{0}};
    EXPECT_TRUE(u.is_strictly_upper_triangular());
}

TEST(IsStrictlyUpperTriangular, Negative) {
    lana::matrix<int> m{{0, 1, 2, 3}, {0, 0, 1, 2}, {0, 0, 0, 1}, {1, 0, 0, 0}};
    EXPECT_FALSE(m.is_strictly_upper_triangular());

    lana::matrix<int> u{{1}};
    EXPECT_FALSE(u.is_strictly_upper_triangular());
}

TEST(IsStrictlyUpperTriangular, NonSquareMatrix) {
    lana::matrix<int> m{{0, 1, 2, 3}, {0, 0, 1, 2}, {0, 0, 0, 1}};
    EXPECT_FALSE(m.is_strictly_upper_triangular());
}

TEST(IsLowerTriangular, Positive) {
    lana::matrix<int> m{{1, 0, 0}, {1, 1, 0}, {1, 1, 1}};
    EXPECT_TRUE(m.is_lower_triangular());
}

TEST(IsLowerTriangular, Negative) {
    lana::matrix<int> m{{1, 0, 1}, {1, 1, 1}, {1, 1, 1}};
    EXPECT_FALSE(m.is_lower_triangular());
}

TEST(IsLowerTriangular, NonSquareMatrix) {
    lana::matrix<int> m{{1, 0, 1}, {1, 1, 1}};
    EXPECT_FALSE(m.is_lower_triangular());
}

TEST(IsStrictlyLowerTriangular, Positive) {
    lana::matrix<int> m{{0, 0, 0, 0}, {1, 0, 0, 0}, {2, 3, 0, 0}, {4, 5, 6, 0}};
    EXPECT_TRUE(m.is_strictly_lower_triangular());

    lana::matrix<int> u{{0}};
    EXPECT_TRUE(u.is_strictly_lower_triangular());
}

TEST(IsStrictlyLowerTriangular, Negative) {
    lana::matrix<int> m{{0, 1, 0}, {1, 0, 0}, {2, 3, 0}};
    EXPECT_FALSE(m.is_strictly_lower_triangular());

    lana::matrix<int> u{{0, 0, 0}, {1, 2, 0}, {2, 3, 0}};
    EXPECT_FALSE(u.is_strictly_lower_triangular());

    lana::matrix<int> w{{1}};
    EXPECT_FALSE(w.is_strictly_lower_triangular());
}

TEST(IsStrictlyLowerTriangular, NonSquareMatrix) {
    lana::matrix<int> m{{0, 0, 0}, {1, 0, 0}};
    EXPECT_FALSE(m.is_strictly_lower_triangular());
}

TEST(isDiagonal, Positive) {
    lana::matrix<int> d{{2, 0, 0}, {0, 1, 0}, {0, 0, -3}};
    EXPECT_TRUE(d.is_diagonal());
    lana::matrix<int> u{{1}};
    EXPECT_TRUE(u.is_diagonal());
    lana::matrix<int> z{{0}};
    EXPECT_TRUE(z.is_diagonal());
}

TEST(isDiagonal, Negative) {
    lana::matrix<int> d{{2, 0, 1}, {0, 1, 0}, {0, 0, -3}};
    EXPECT_FALSE(d.is_diagonal());
}

TEST(IsSymmetric, Positive) {
    lana::matrix<int> id = lana::matrix<int>::identity(5);
    EXPECT_TRUE(id.is_symmetric());

    lana::matrix<int> m{{3, 2, 1}, {2, 4, 0}, {1, 0, 5}};
    EXPECT_TRUE(m.is_symmetric());

    lana::matrix<int> u{{1}};
    EXPECT_TRUE(u.is_symmetric());
}

TEST(IsSymmetric, Negative) {
    lana::matrix<int> m{{3, 2, 1}, {1, 4, 0}, {1, 7, 1}};
    EXPECT_FALSE(m.is_symmetric());
}

TEST(Equality, Positive) {
    lana::matrix<int> m = {{1, 1, 0}, {2, 5, 6}};
    auto b = m;
    EXPECT_TRUE(m == b);
}

TEST(Equality, Negative) {
    lana::matrix<int> m = {{1, 1, 0}, {2, 5, 6}};
    lana::matrix<int> n = {{1, 1, 0}, {2, 5, 6}, {1, 2, 3}};

    EXPECT_FALSE(m == n);
}

TEST(Inequality, Positive) {
    lana::matrix<int> m = {{1, 1, 0}, {2, 5, 6}};
    lana::matrix<int> n = {{1, 1, 0}, {2, 5, 6}, {32, 54, 4}};
    EXPECT_TRUE(m != n);
}

TEST(Inequality, Negative) {
    lana::matrix<int> m = {{1, 1, 0}, {2, 5, 6}};
    auto n = m;
    EXPECT_FALSE(m != n);
}

TEST(MatrixAddition, SameSizeMatrices) {
    lana::matrix<int> a{{1, 2, 3}, {4, 5, 6}};
    lana::matrix<int> b{{6, 5, 4}, {3, 2, 1}};
    lana::matrix<int> expected{{7, 7, 7}, {7, 7, 7}};

    auto result = a + b;

    EXPECT_TRUE(result == expected);
    EXPECT_TRUE((a == lana::matrix<int>{{1, 2, 3}, {4, 5, 6}}));
    EXPECT_TRUE((b == lana::matrix<int>{{6, 5, 4}, {3, 2, 1}}));
}

TEST(MatrixAddition, SquareMatrices) {
    lana::matrix<int> a{{1, 2}, {3, 4}};
    lana::matrix<int> b{{5, 6}, {7, 8}};
    lana::matrix<int> expected{{6, 8}, {10, 12}};

    EXPECT_TRUE(a + b == expected);
}

TEST(MatrixAddition, ZeroMatrix) {
    lana::matrix<int> a{{1, 2}, {3, 4}};
    lana::matrix<int> zero{{0, 0}, {0, 0}};
    lana::matrix<int> expected{{1, 2}, {3, 4}};

    EXPECT_TRUE(a + zero == expected);
}

TEST(MatrixAddition, DifferentSizes) {
    lana::matrix<int> a{{1, 2, 3}, {4, 5, 6}};
    lana::matrix<int> b{{1, 2}, {3, 4}};

    EXPECT_THROW((a + b), std::invalid_argument);
}

TEST(MatrixAdditionAssignment, SameSizeMatrices) {
    lana::matrix<int> a{{1, 2}, {3, 4}};
    lana::matrix<int> b{{5, 6}, {7, 8}};
    lana::matrix<int> expected{{6, 8}, {10, 12}};
    lana::matrix<int> expected_b{{5, 6}, {7, 8}};

    lana::matrix<int>& result = (a += b);

    EXPECT_TRUE(a == expected);
    EXPECT_TRUE(b == expected_b);
    EXPECT_EQ(&result, &a);
}

TEST(MatrixAdditionAssignment, DifferentSizes) {
    lana::matrix<int> a{{1, 2, 3}, {4, 5, 6}};
    lana::matrix<int> b{{1, 2}, {3, 4}};

    EXPECT_THROW((a += b), std::invalid_argument);
}

TEST(MatrixSubtraction, SameSizeMatrices) {
    lana::matrix<int> a{{7, 8, 9}, {6, 5, 4}};
    lana::matrix<int> b{{1, 2, 3}, {4, 5, 6}};
    lana::matrix<int> expected{{6, 6, 6}, {2, 0, -2}};

    auto result = a - b;

    EXPECT_TRUE(result == expected);
    EXPECT_TRUE((a == lana::matrix<int>{{7, 8, 9}, {6, 5, 4}}));
    EXPECT_TRUE((b == lana::matrix<int>{{1, 2, 3}, {4, 5, 6}}));
}

TEST(MatrixSubtraction, DifferentSizes) {
    lana::matrix<int> a{{1, 2, 3}, {4, 5, 6}};
    lana::matrix<int> b{{1, 2}, {3, 4}};

    EXPECT_THROW((a - b), std::invalid_argument);
}

TEST(MatrixSubtractionAssignment, SameSizeMatrices) {
    lana::matrix<int> a{{7, 8}, {9, 10}};
    lana::matrix<int> b{{1, 2}, {3, 4}};
    lana::matrix<int> expected{{6, 6}, {6, 6}};
    lana::matrix<int> expected_b{{1, 2}, {3, 4}};

    lana::matrix<int>& result = (a -= b);

    EXPECT_TRUE(a == expected);
    EXPECT_TRUE(b == expected_b);
    EXPECT_EQ(&result, &a);
}

TEST(MatrixSubtractionAssignment, DifferentSizes) {
    lana::matrix<int> a{{1, 2, 3}, {4, 5, 6}};
    lana::matrix<int> b{{1, 2}, {3, 4}};

    EXPECT_THROW((a -= b), std::invalid_argument);
}

TEST(MatrixMultiplication, CompatibleRectangularMatrices) {
    lana::matrix<int> a{{1, 2, 3}, {4, 5, 6}};
    lana::matrix<int> b{{7, 8}, {9, 10}, {11, 12}};
    lana::matrix<int> expected{{58, 64}, {139, 154}};

    auto result = a * b;

    EXPECT_TRUE(result == expected);
    EXPECT_EQ(result.rows(), 2);
    EXPECT_EQ(result.columns(), 2);

    // operands should remain the same
    lana::matrix<int> expected_a{{1, 2, 3}, {4, 5, 6}};
    lana::matrix<int> expected_b{{7, 8}, {9, 10}, {11, 12}};
    EXPECT_TRUE(a == expected_a);
    EXPECT_TRUE(b == expected_b);
}

TEST(MatrixMultiplication, SquareMatrices) {
    lana::matrix<int> a{{1, 2}, {3, 4}};
    lana::matrix<int> b{{5, 6}, {7, 8}};
    lana::matrix<int> expected{{19, 22}, {43, 50}};

    EXPECT_TRUE(a * b == expected);
}

TEST(MatrixMultiplication, IdentityMatrix) {
    lana::matrix<int> a{{1, 2, 3}, {4, 5, 6}};
    lana::matrix<int> identity = lana::matrix<int>::identity(3);
    lana::matrix<int> expected = a;

    EXPECT_TRUE(a * identity == expected);
}

TEST(MatrixMultiplication, ZeroMatrix) {
    lana::matrix<int> a{{1, 2, 3}, {4, 5, 6}};
    lana::matrix<int> zero = lana::matrix<int>::zeros(3, 2);
    lana::matrix<int> expected = lana::matrix<int>::zeros(2, 2);
    EXPECT_TRUE((a * zero) == expected);
}

TEST(MatrixMultiplication, IncompatibleDimensions) {
    lana::matrix<int> a{{1, 2, 3}, {4, 5, 6}};
    lana::matrix<int> b{{1, 2}, {3, 4}};

    EXPECT_THROW((a * b), std::invalid_argument);
}

TEST(MatrixMultiplicationAssignment, CompatibleRectangularMatrices) {
    lana::matrix<int> a{{1, 2, 3}, {4, 5, 6}};
    lana::matrix<int> b{{7, 8}, {9, 10}, {11, 12}};
    lana::matrix<int> expected{{58, 64}, {139, 154}};

    a *= b;

    EXPECT_TRUE(a == expected);
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.columns(), 2);

    // b should remain the same
    lana::matrix<int> expected_b{{7, 8}, {9, 10}, {11, 12}};
    EXPECT_TRUE(b == expected_b);
}

TEST(MatrixMultiplicationAssignment, SquareMatrices) {
    lana::matrix<int> a{{1, 2}, {3, 4}};
    lana::matrix<int> b{{5, 6}, {7, 8}};
    lana::matrix<int> expected{{19, 22}, {43, 50}};

    a *= b;
    EXPECT_TRUE(a == expected);
}

TEST(MatrixMultiplicationAssignment, IdentityMatrix) {
    lana::matrix<int> a{{1, 2, 3}, {4, 5, 6}};
    lana::matrix<int> identity = lana::matrix<int>::identity(3);
    lana::matrix<int> expected = a;

    a *= identity;

    EXPECT_TRUE(a == expected);
}

TEST(MatrixMultiplicationAssignment, ZeroMatrix) {
    lana::matrix<int> a{{1, 2, 3}, {4, 5, 6}};
    lana::matrix<int> zero = lana::matrix<int>::zeros(3, 2);
    lana::matrix<int> expected = lana::matrix<int>::zeros(2, 2);
    a *= zero;
    EXPECT_TRUE(a == expected);
}

TEST(MatrixMultiplicationAssignment, IncompatibleDimensions) {
    lana::matrix<int> a{{1, 2, 3}, {4, 5, 6}};
    lana::matrix<int> b{{1, 2}, {3, 4}};

    EXPECT_THROW((a *= b), std::invalid_argument);
}

TEST(MatrixScalarMultiplication, IntMatrixTimesDouble) {
    lana::matrix<int> m{{1, 2}, {3, 4}};
    lana::matrix<double> expected{{0.5, 1.0}, {1.5, 2.0}};

    auto result = m * 0.5;

    EXPECT_TRUE(result == expected);
    EXPECT_TRUE((m == lana::matrix<int>{{1, 2}, {3, 4}}));
}

TEST(MatrixScalarMultiplication, DoubleMatrixTimesInt) {
    lana::matrix<double> m{{1.5, 2.5}, {3.5, 4.5}};
    lana::matrix<double> expected{{3.0, 5.0}, {7.0, 9.0}};

    auto result = m * 2;

    EXPECT_TRUE(result == expected);
}

TEST(MatrixScalarMultiplication, IntMatrixTimesInt) {
    lana::matrix<int> m{{1, 2}, {3, 4}};
    lana::matrix<int> expected{{2, 4}, {6, 8}};

    auto result = m * 2;

    EXPECT_TRUE(result == expected);
}

TEST(MatrixScalarMultiplication, RectangularMatrix) {
    lana::matrix<int> m{{1, 2, 3}, {4, 5, 6}};
    lana::matrix<double> expected{{0.5, 1.0, 1.5}, {2.0, 2.5, 3.0}};

    auto result = m * 0.5;

    EXPECT_TRUE(result == expected);
    EXPECT_EQ(result.rows(), 2);
    EXPECT_EQ(result.columns(), 3);
}

TEST(MatrixIterators, BeginEnd) {
    lana::matrix<int> m{{1, 2, 3}, {4, 5, 6}};
    auto it = m.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(*it, 4);
    EXPECT_NE(it, m.end());
    it += 3;
    EXPECT_EQ(it, m.end());
}

TEST(MatrixIterators, RangeBasedFor) {
    lana::matrix<int> m{{1, 2, 3}, {4, 5, 6}};

    int expected = 1;
    for (const int& value : m) {
        EXPECT_EQ(value, expected);
        ++expected;
    }
    EXPECT_EQ(expected, 7);
}

TEST(MatrixIterators, MutableIterator) {
    lana::matrix<int> m{{1, 2}, {3, 4}};

    for (auto it = m.begin(); it != m.end(); ++it) {
        *it *= 2;
    }
    EXPECT_EQ(m(0, 0), 2);
    EXPECT_EQ(m(0, 1), 4);
    EXPECT_EQ(m(1, 0), 6);
    EXPECT_EQ(m(1, 1), 8);
}

TEST(MatrixIterators, ConstIterator) {
    const lana::matrix<int> m{{1, 2}, {3, 4}};

    auto it = m.begin();

    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(*it, 4);
    ++it;
    EXPECT_EQ(it, m.end());
}

TEST(MatrixIterators, CbeginCend) {
    lana::matrix<int> m{{1, 2}, {3, 4}};

    auto it = m.cbegin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(*it, 4);
    ++it;
    EXPECT_EQ(it, m.cend());
}