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