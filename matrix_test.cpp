#include "matrix.hpp"

#include <gtest/gtest.h>

namespace {

  TEST(MatrixTest, DefaultConstructor) {
    const parmat::matrix<int> m;

    EXPECT_EQ(0, m.row_count());
    EXPECT_EQ(0, m.col_count());
  }

  TEST(MatrixTest, RowColConstructor) {

  }

  TEST(MatrixTest, CopyConstructor) {

  }

  TEST(MatrixTest, MoveConstructor) {

  }

  TEST(MatrixTest, FillConstructor) {

  }

  TEST(MatrixTest, RowColCount) {

  }

  TEST(MatrixTest, CopyAssigmentOperator) {

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
