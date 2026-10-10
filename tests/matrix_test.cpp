#include "matrix.hpp"

#include <gtest/gtest.h>

TEST(MatrixTranspose, RectangularMatrix) {
    lana::matrix<int> m(2, 3);
    m(0, 0) = 1;
    m(0, 1) = 2;
    m(0, 2) = 3;
    m(1, 0) = 4;
    m(1, 1) = 5;
    m(1, 2) = 6;

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