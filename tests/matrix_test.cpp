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

TEST(MatrixAddition, SameSizeMatrices) {
    lana::matrix<int> a{{1, 2, 3}, {4, 5, 6}};
    lana::matrix<int> b{{6, 5, 4}, {3, 2, 1}};

    auto sum = a + b;

    EXPECT_EQ(sum.rows(), 2);
    EXPECT_EQ(sum.columns(), 3);
    EXPECT_EQ(sum(0, 0), 7);
    EXPECT_EQ(sum(0, 1), 7);
    EXPECT_EQ(sum(0, 2), 7);
    EXPECT_EQ(sum(1, 0), 7);
    EXPECT_EQ(sum(1, 1), 7);
    EXPECT_EQ(sum(1, 2), 7);

    EXPECT_EQ(a(0, 0), 1);
    EXPECT_EQ(b(0, 0), 6);
}

TEST(MatrixAddition, SquareMatrices) {
    lana::matrix<int> a{{1, 2}, {3, 4}};
    lana::matrix<int> b{{5, 6}, {7, 8}};

    auto sum = a + b;

    EXPECT_EQ(sum(0, 0), 6);
    EXPECT_EQ(sum(0, 1), 8);
    EXPECT_EQ(sum(1, 0), 10);
    EXPECT_EQ(sum(1, 1), 12);
}

TEST(MatrixAddition, ZeroMatrix) {
    lana::matrix<int> a{{1, 2}, {3, 4}};
    lana::matrix<int> zero{{0, 0}, {0, 0}};

    auto sum = a + zero;

    EXPECT_EQ(sum(0, 0), 1);
    EXPECT_EQ(sum(0, 1), 2);
    EXPECT_EQ(sum(1, 0), 3);
    EXPECT_EQ(sum(1, 1), 4);
}

TEST(MatrixAddition, DifferentSizes) {
    lana::matrix<int> a{{1, 2, 3}, {4, 5, 6}};
    lana::matrix<int> b{{1, 2}, {3, 4}};

    EXPECT_THROW((a + b), std::invalid_argument);
}

TEST(MatrixAdditionAssignment, SameSizeMatrices) {
    lana::matrix<int> a{{1, 2}, {3, 4}};
    lana::matrix<int> b{{5, 6}, {7, 8}};

    lana::matrix<int>& result = (a += b);

    EXPECT_EQ(a(0, 0), 6);
    EXPECT_EQ(a(0, 1), 8);
    EXPECT_EQ(a(1, 0), 10);
    EXPECT_EQ(a(1, 1), 12);
    EXPECT_EQ(&result, &a);
    EXPECT_EQ(b(0, 0), 5);
}

TEST(MatrixAdditionAssignment, DifferentSizes) {
    lana::matrix<int> a{{1, 2, 3}, {4, 5, 6}};
    lana::matrix<int> b{{1, 2}, {3, 4}};

    EXPECT_THROW((a += b), std::invalid_argument);
}

TEST(MatrixSubtraction, SameSizeMatrices) {
    lana::matrix<int> a{{7, 8, 9}, {6, 5, 4}};
    lana::matrix<int> b{{1, 2, 3}, {4, 5, 6}};

    auto difference = a - b;

    EXPECT_EQ(difference.rows(), 2);
    EXPECT_EQ(difference.columns(), 3);
    EXPECT_EQ(difference(0, 0), 6);
    EXPECT_EQ(difference(0, 1), 6);
    EXPECT_EQ(difference(0, 2), 6);
    EXPECT_EQ(difference(1, 0), 2);
    EXPECT_EQ(difference(1, 1), 0);
    EXPECT_EQ(difference(1, 2), -2);

    EXPECT_EQ(a(0, 0), 7);
    EXPECT_EQ(b(0, 0), 1);
}

TEST(MatrixSubtraction, DifferentSizes) {
    lana::matrix<int> a{{1, 2, 3}, {4, 5, 6}};
    lana::matrix<int> b{{1, 2}, {3, 4}};

    EXPECT_THROW((a - b), std::invalid_argument);
}

TEST(MatrixSubtractionAssignment, SameSizeMatrices) {
    lana::matrix<int> a{{7, 8}, {9, 10}};
    lana::matrix<int> b{{1, 2}, {3, 4}};

    lana::matrix<int>& result = (a -= b);

    EXPECT_EQ(a(0, 0), 6);
    EXPECT_EQ(a(0, 1), 6);
    EXPECT_EQ(a(1, 0), 6);
    EXPECT_EQ(a(1, 1), 6);
    EXPECT_EQ(&result, &a);
    EXPECT_EQ(b(0, 0), 1);
}

TEST(MatrixSubtractionAssignment, DifferentSizes) {
    lana::matrix<int> a{{1, 2, 3}, {4, 5, 6}};
    lana::matrix<int> b{{1, 2}, {3, 4}};

    EXPECT_THROW((a -= b), std::invalid_argument);
}
