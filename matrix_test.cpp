#include "matrix.hpp"

#include <gtest/gtest.h>

namespace {

  TEST(MatrixTest, DefaultConstructor) {
    const parmat::matrix<int> m;

    EXPECT_EQ(0, m.row_count());
    EXPECT_EQ(0, m.col_count());
  }

  TEST(MatrixTest, RowColConstructor) {
    const parmat::matrix<int> m(1, 1);

    EXPECT_EQ(1, m.row_count());
    EXPECT_EQ(1, m.col_count());

    const parmat::matrix<int> m2(2, 3);

    EXPECT_EQ(2, m2.row_count());
    EXPECT_EQ(3, m2.col_count());
  }

  TEST(MatrixTest, CopyConstructor) {
    const parmat::matrix<int> m(2, 2);

    EXPECT_EQ(2, m.row_count());
    EXPECT_EQ(2, m.col_count());

    const parmat::matrix<int> m2(m);

    EXPECT_EQ(2, m2.row_count());
    EXPECT_EQ(2, m2.col_count());
  }

  TEST(MatrixTest, MoveConstructor) {
    const parmat::matrix<int> m(2, 2);

    EXPECT_EQ(2, m.row_count());
    EXPECT_EQ(2, m.col_count());

    const parmat::matrix<int> m2(std::move(m));

    EXPECT_EQ(2, m2.row_count());
    EXPECT_EQ(2, m2.col_count());
  }

  TEST(MatrixTest, FillConstructor) {
    const parmat::matrix<int> m(2, 2, 1);

    EXPECT_EQ(1, m(0, 0));
    EXPECT_EQ(1, m(0, 1));
    EXPECT_EQ(1, m(1, 0));
    EXPECT_EQ(1, m(1, 1));
  }

  TEST(MatrixTest, MatrixLiteralConstructor) {
    const parmat::matrix<int> m(2, 2, {
      1, 0,
      0, 1
    });

    EXPECT_EQ(1, m(0, 0));
    EXPECT_EQ(0, m(0, 1));
    EXPECT_EQ(0, m(1, 0));
    EXPECT_EQ(1, m(1, 1));
  }

  TEST(MatrixTest, CopyAssigmentOperator) {

  }

  TEST(MatrixTest, MoveAssignmentOperator) {

  }

  TEST(MatrixTest, PlusEqualsOperator) {

  }

  TEST(MatrixTest, IndexOperator) {

  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
