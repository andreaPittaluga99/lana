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

TEST(IsUpperTriangular, Affermative) {
    lana::matrix<int> m({{2, 10, -1}, {0, 1, 0}, {0, 0, 3}});
    EXPECT_TRUE(m.is_upper_triangular());
}

TEST(IsUpperTriangular, Negative) {
    lana::matrix<int> m({{0, 0, -1}, {1, 1, 0}, {0, 0, 0}});
    EXPECT_FALSE(m.is_upper_triangular());
}