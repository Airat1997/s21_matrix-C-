#include "s21_matrix_oop.h"
#include "gtest/gtest.h"

void initialization(S21Matrix &other, const double *value) {
  int n = 0;
  for (int i = 0; i < other.GetRows(); i++) {
    for (int j = 0; j < other.GetCols(); j++) {
      other(i, j) = value[n++];
    }
  }
}

TEST(MatrixConstructor, DefaultConstructor) { EXPECT_NO_THROW(S21Matrix A); }

TEST(MatrixConstructor, ParameterizedConstructor) {
  EXPECT_NO_THROW(S21Matrix A(5, 7));
  EXPECT_ANY_THROW(S21Matrix A(-5, 7));
  EXPECT_ANY_THROW(S21Matrix A(5, -7));
  EXPECT_ANY_THROW(S21Matrix A(-5, -7));
}

TEST(MatrixConstructor, CopyConstructor) {
  S21Matrix A(5, 5);
  double a[] = {3.14,   5.23114,  2.123,       0,  23124.5433456,
                3.14,   -5.23114, -2.123,      0,  -23124.5433456,
                63.423, 54,       34333333333, 81, 66,
                39.4,   76,       25,          42, 82,
                14,     59,       14.2304,     44, 66.02};
  initialization(A, a);
  S21Matrix B(A);
  ASSERT_EQ(A, B);
}

TEST(MatrixConstructor, TransferConstructor) {
  S21Matrix A(5, 5);
  double a[] = {3.14,   5.23114,  2.123,       0,  23124.5433456,
                3.14,   -5.23114, -2.123,      0,  -23124.5433456,
                63.423, 54,       34333333333, 81, 66,
                39.4,   76,       25,          42, 82,
                14,     59,       14.2304,     44, 66.02};
  initialization(A, a);
  S21Matrix B(A);
  S21Matrix T(std::move(B));
  ASSERT_EQ(A, T);
}

TEST(MatrixOperator, Plus1) {
  S21Matrix A(3, 3);
  double a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  initialization(A, a);
  S21Matrix B(A);
  S21Matrix S(3, 3);
  S = A + B;
  S21Matrix Z(3, 3);
  double z[] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
  initialization(Z, z);
  ASSERT_EQ(S, Z);
}
TEST(MatrixOperator, Plus2) {
  S21Matrix A(3, 3);
  double a[] = {-1, -2, -3, -4, -5, -6, -7, -8, -9};
  initialization(A, a);
  S21Matrix B(A);
  S21Matrix S(3, 3);
  S = A + B;
  S21Matrix Z(3, 3);
  double z[] = {-2, -4, -6, -8, -10, -12, -14, -16, -18};
  initialization(Z, z);
  ASSERT_EQ(S, Z);
}

TEST(MatrixOperator, PlusError) {
  S21Matrix A(3, 3);
  S21Matrix Z(4, 3);
  EXPECT_ANY_THROW(A + Z);
}

TEST(MatrixOperator, Minus1) {
  S21Matrix A(3, 3);
  double a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  initialization(A, a);
  S21Matrix B(A);
  S21Matrix S(3, 3);
  S = A - B;
  S21Matrix Z(3, 3);
  double z[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  initialization(Z, z);
  ASSERT_EQ(S, Z);
}

TEST(MatrixOperator, Minus2) {
  S21Matrix A(3, 3);
  double a[] = {-1, -2, -3, -4, -5, -6, -7, -8, -9};
  initialization(A, a);
  S21Matrix B(A);
  S21Matrix S(3, 3);
  S = A - B;
  S21Matrix Z(3, 3);
  double z[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  initialization(Z, z);
  ASSERT_EQ(S, Z);
}

TEST(MatrixOperator, MinusError) {
  S21Matrix A(3, 3);
  S21Matrix Z(4, 3);
  EXPECT_ANY_THROW(A - Z);
}

TEST(MatrixOperator, Appropriation) {
  S21Matrix A(3, 3);
  double a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  initialization(A, a);
  S21Matrix B(3, 3);
  B = A;
  ASSERT_EQ(B, A);
}

TEST(MatrixOperator, MulMatrix) {
  S21Matrix A(2, 2);
  double a[] = {1, 2, 3, 4};
  initialization(A, a);
  S21Matrix B(2, 2);
  double b[] = {1, 2, 3, 4};
  initialization(B, b);
  B = A * B;
  S21Matrix Z(2, 2);
  double z[] = {7, 10, 15, 22};
  initialization(Z, z);
  ASSERT_TRUE(B == Z);
}

TEST(MatrixOperator, MulNum) {
  S21Matrix A(2, 2);
  double a[] = {2, 2, 2, 2};
  initialization(A, a);
  S21Matrix S(2, 2);
  S = A + A;
  S21Matrix Z(2, 2);
  Z = A * 2;
  ASSERT_EQ(S, Z);
}

TEST(MatrixOperator, Index) {
  S21Matrix A(2, 2);
  double a[] = {2, 2, 2, 2};
  initialization(A, a);
  ASSERT_EQ(A.operator()(0, 0), 2);
  ASSERT_EQ(A.operator()(0, 1), 2);
  ASSERT_EQ(A.operator()(1, 0), 2);
}

TEST(MatrixOperator, Equals) {
  S21Matrix A(2, 2);
  double a[] = {2, 2, 2, 2};
  initialization(A, a);
  S21Matrix B(A);
  ASSERT_EQ(true, B == A);
}

TEST(MatrixOperator, Equals2) {
  S21Matrix A(2, 2);
  S21Matrix B(4, 4);
  ASSERT_EQ(false, B == A);
}

TEST(MatrixOperator, SumMatrix) {
  S21Matrix A(2, 2);
  double a[] = {2, 2, 2, 2};
  initialization(A, a);
  S21Matrix B(A);
  B += A;
  S21Matrix Z(2, 2);
  double z[] = {4, 4, 4, 4};
  initialization(Z, z);
  ASSERT_EQ(B, Z);
}

TEST(MatrixOperator, SumMatrixError) {
  S21Matrix A(2, 2);
  S21Matrix B(3, 4);
  EXPECT_ANY_THROW(B += A);
}

TEST(MatrixOperator, SubMatrix) {
  S21Matrix A(2, 2);
  double a[] = {2, 2, 2, 2};
  initialization(A, a);
  S21Matrix B(A);
  B -= A;
  S21Matrix Z(2, 2);
  double z[] = {0, 0, 0, 0};
  initialization(Z, z);
  ASSERT_EQ(B, Z);
}

TEST(MatrixOperator, SubMatrixError) {
  S21Matrix A(2, 2);
  S21Matrix B(3, 4);
  EXPECT_ANY_THROW(B -= A);
}

TEST(MatrixOperator, EqMulNum) {
  S21Matrix A(2, 2);
  double a[] = {2, 2, 2, 2};
  initialization(A, a);
  S21Matrix S(2, 2);
  S = A + A;
  A *= 2;
  ASSERT_EQ(S, A);
}

TEST(MatrixMethods, EqMatrix1) {
  S21Matrix A(2, 2);
  double a[] = {2, 2, 2, 2};
  initialization(A, a);
  S21Matrix B(2, 2);
  ASSERT_EQ(false, A.EqMatrix(B));
}

TEST(MatrixMethods, EqMatrix2) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  ASSERT_EQ(true, A.EqMatrix(B));
}

TEST(MatrixMethods, EqMatrix3) {
  S21Matrix A(5, 2);
  S21Matrix B(2, 2);
  ASSERT_EQ(false, A.EqMatrix(B));
}

TEST(MatrixMethods, SumMatrix) {
  S21Matrix A(2, 2);
  double a[] = {2, 2, 2, 2};
  initialization(A, a);
  S21Matrix B(A);
  B.SumMatrix(A);
  S21Matrix Z(2, 2);
  double z[] = {4, 4, 4, 4};
  initialization(Z, z);
  ASSERT_EQ(B, Z);
}

TEST(MatrixMethods, SumMatrixError) {
  S21Matrix A(2, 2);
  S21Matrix B(4, 3);
  EXPECT_ANY_THROW(B.SumMatrix(A));
}

TEST(MatrixMethods, SubMatrix) {
  S21Matrix A(2, 2);
  double a[] = {2, 2, 2, 2};
  initialization(A, a);
  S21Matrix B(A);
  B.SubMatrix(A);
  S21Matrix Z(2, 2);
  double z[] = {0, 0, 0, 0};
  initialization(Z, z);
  ASSERT_EQ(B, Z);
}

TEST(MatrixMethods, SubMatrixError) {
  S21Matrix A(2, 2);
  S21Matrix B(4, 3);
  EXPECT_ANY_THROW(B.SubMatrix(A));
}

TEST(MatrixMethods, MulNum) {
  S21Matrix A(2, 2);
  double a[] = {2, 2, 2, 2};
  initialization(A, a);
  S21Matrix S(2, 2);
  S = A + A;
  A.MulNumber(2);
  ASSERT_EQ(S, A);
}
TEST(MatrixMethods, MulMatrix) {}


TEST(Matrix, InverseMatrix) {
  S21Matrix R(2, 2);
  double R_1[] = {1, 2, 3, 4};
  initialization(R, R_1);
  S21Matrix R2(2, 2);
  S21Matrix A(2, 2);
  double A_1[] = {-2, 1, 1.5, -0.5};
  initialization(A, A_1);
  R2 = A.InverseMatrix();
  ASSERT_TRUE(R2 == R);
}

TEST(Matrix, InverseMatrixError) {
  S21Matrix R(2, 8);
  EXPECT_ANY_THROW(R.InverseMatrix(););
}

TEST(Matrix, SetGetAdd) {
  S21Matrix one(3, 3);
  EXPECT_EQ(one.GetRows(), 3);
  EXPECT_EQ(one.GetCols(), 3);
  one.SetRows(1);
  EXPECT_EQ(one.GetRows(), 1);
  one.SetCols(10);
  EXPECT_EQ(one.GetCols(), 10);
  S21Matrix two(20, 20);
  two.SetRows(30);
  EXPECT_EQ(two.GetRows(), 30);
  two.SetCols(30);
  EXPECT_EQ(two.GetCols(), 30);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
