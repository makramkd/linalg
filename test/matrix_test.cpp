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

  TEST(MatrixTest, ScalarMultiplyOperator) {
    // "Complicated" test
    parmat::matrix<int> m(3, 4, {
      1, 2, 3, 1,
      1, 1, 2, 1,
      3, 4, 5, 6,
    });

    int scalar = 3;
    m *= scalar;

    EXPECT_EQ(3, m(0, 0));
    EXPECT_EQ(6, m(0, 1));
    EXPECT_EQ(9, m(0, 2));
    EXPECT_EQ(3, m(0, 3));
    EXPECT_EQ(3, m(1, 0));
    EXPECT_EQ(3, m(1, 1));
    EXPECT_EQ(6, m(1, 2));
    EXPECT_EQ(3, m(1, 3));
    EXPECT_EQ(9, m(2, 0));
    EXPECT_EQ(12, m(2, 1));
    EXPECT_EQ(15, m(2, 2));
    EXPECT_EQ(18, m(2, 3));
  }

  TEST(MatrixTest, MatrixMultiplication) {
    parmat::matrix<int> m(3, 4, {
      1, 2, 3, 1,
      1, 1, 2, 1,
      3, 4, 5, 6,
    });

    parmat::matrix<int> m2(4, 5, {
      1, 2, 3, 1, 3,
      1, 1, 2, 1, 3,
      3, 4, 5, 6, 3,
      3, 4, 5, 6, 3,
    });

    auto m3 = m * m2;
    parmat::matrix<int> expected(3, 5, {
      15, 20, 27, 27, 21,
      11, 15, 20, 20, 15,
      40, 54, 72, 73, 54,
    });

    ASSERT_EQ(expected, m3);
  }

  TEST(MatrixTest, MatrixEqualityOperator) {
    parmat::matrix<int> m(3, 4, {
      1, 2, 3, 1,
      1, 1, 2, 1,
      3, 4, 5, 6,
    });

    parmat::matrix<int> m2(3, 4, {
      1, 2, 3, 1,
      1, 2, 2, 1,
      3, 4, 5, 6,
    });

    ASSERT_NE(m, m2);
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
