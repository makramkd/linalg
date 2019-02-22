#include "linalg/matrix.hpp"

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
    const parmat::matrix<int> m(2, 2, {
      1, 0,
      0, 1
    });

    const auto m2 = m;

    EXPECT_EQ(1, m2(0, 0));
    EXPECT_EQ(0, m2(0, 1));
    EXPECT_EQ(0, m2(1, 0));
    EXPECT_EQ(1, m2(1, 1));
  }

  TEST(MatrixTest, MoveAssignmentOperator) {
    // TODO: how to test move?
    parmat::matrix<int> m(2, 2, {
      1, 0,
      0, 1
    });

    const auto m2 = std::move(m);

    EXPECT_EQ(1, m2(0, 0));
    EXPECT_EQ(0, m2(0, 1));
    EXPECT_EQ(0, m2(1, 0));
    EXPECT_EQ(1, m2(1, 1));
  }

  TEST(MatrixTest, PlusEqualsOperator) {
    parmat::matrix<int> m(2, 2, {
      1, 0,
      0, 1
    });

    parmat::matrix<int> m2(2, 2, {
      0, 1,
      1, 0
    });

    m += m2;

    EXPECT_EQ(1, m(0, 0));
    EXPECT_EQ(1, m(0, 1));
    EXPECT_EQ(1, m(1, 0));
    EXPECT_EQ(1, m(1, 1));
  }

  TEST(MatrixTest, MinusEqualsOperator) {
    parmat::matrix<int> m(2, 2, {
      1, 0,
      0, 1
    });

    parmat::matrix<int> m2(2, 2, {
      0, 1,
      1, 0
    });

    m -= m2;

    EXPECT_EQ(1, m(0, 0));
    EXPECT_EQ(-1, m(0, 1));
    EXPECT_EQ(-1, m(1, 0));
    EXPECT_EQ(1, m(1, 1));
  }

  TEST(MatrixTest, OperatorPlus) {
    parmat::matrix<int> m(2, 2, {
      1, 0,
      0, 1
    });

    parmat::matrix<int> m2(2, 2, {
      0, 1,
      1, 0
    });

    auto m3 = m + m2;

    EXPECT_EQ(1, m3(0, 0));
    EXPECT_EQ(1, m3(0, 1));
    EXPECT_EQ(1, m3(1, 0));
    EXPECT_EQ(1, m3(1, 1));
  }

  TEST(MatrixTest, OperatorMinus) {
    parmat::matrix<int> m(2, 2, {
      1, 0,
      0, 1
    });

    parmat::matrix<int> m2(2, 2, {
      0, 1,
      1, 0
    });

    auto m3 = m - m2;

    EXPECT_EQ(1, m3(0, 0));
    EXPECT_EQ(-1, m3(0, 1));
    EXPECT_EQ(-1, m3(1, 0));
    EXPECT_EQ(1, m3(1, 1));
  }

  TEST(MatrixTest, IndexOperator) {
    // "Complicated" test
    parmat::matrix<int> m(3, 4, {
      1, 0, 0, 1,
      0, 1, 0, 1,
      0, 0, 1, 0,
    });

    EXPECT_EQ(1, m(0, 0));
    EXPECT_EQ(0, m(0, 1));
    EXPECT_EQ(0, m(0, 2));
    EXPECT_EQ(1, m(0, 3));
    EXPECT_EQ(0, m(1, 0));
    EXPECT_EQ(1, m(1, 1));
    EXPECT_EQ(0, m(1, 2));
    EXPECT_EQ(1, m(1, 3));
    EXPECT_EQ(0, m(2, 0));
    EXPECT_EQ(0, m(2, 1));
    EXPECT_EQ(1, m(2, 2));
    EXPECT_EQ(0, m(2, 3));
  }

  TEST(MatrixTest, Identity) {
    auto i = parmat::identity<int>(32, 1);

    using size_type = typename parmat::matrix<int>::size_type;
    for (size_type j = 0; j < i.row_count(); ++j) {
      EXPECT_EQ(1, i(j, j));
    }
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
