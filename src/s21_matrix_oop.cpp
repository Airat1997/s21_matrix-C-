#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  rows_ = 3;
  cols_ = 3;
  MemoryAllocation();
}

S21Matrix::S21Matrix(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  MemoryAllocation();
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : S21Matrix(other.rows_, other.cols_) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  cols_ = other.cols_;
  rows_ = other.rows_;
  matrix_ = other.matrix_;
  other.cols_ = 0;
  other.rows_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

void S21Matrix::MemoryAllocation() {
  if (rows_ < 1 || cols_ < 1)
    throw invalid_argument("Incorrect matrix");
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  if (cols_ == other.cols_ && rows_ == other.rows_) {
    for (int i = 0; i < rows_; i++) {
      for (int k = 0; k < cols_; k++) {
        if (fabs(matrix_[i][k] - other.matrix_[i][k]) > 1e-7) {
          return false;
        }
      }
    }
  } else {
    return false;
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (cols_ != other.cols_ || rows_ != other.rows_)
    throw "Different matrix dimensions";
  for (int i = 0; i < rows_; i++) {
    for (int k = 0; k < cols_; k++) {
      matrix_[i][k] = matrix_[i][k] + other.matrix_[i][k];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (cols_ != other.cols_ || rows_ != other.rows_)
    throw "Different matrix dimensions";
  for (int i = 0; i < rows_; i++) {
    for (int k = 0; k < cols_; k++) {
      matrix_[i][k] = matrix_[i][k] - other.matrix_[i][k];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int k = 0; k < cols_; k++) {
      matrix_[i][k] = matrix_[i][k] * num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_)
    throw "The number of columns of the first matrix is ​​not equal to the "
          "number of rows of the second matrix";
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this=result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (cols_ != rows_)
    throw "The matrix is ​​not square";
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] = pow(-1, (i + j)) * Minor(i, j).Determinant();
    }
  }
  return result;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::Minor(int i_rows, int i_cols) {
  S21Matrix minor(rows_ - 1, cols_ - 1);
  int minor_rows = 0;
  for (int i = 0; i < rows_; i++) {
    if (i == i_rows)
      continue;
    int minor_cols = 0;
    for (int j = 0; j < cols_; j++) {
      if (j == i_cols)
        continue;
      minor.matrix_[minor_rows][minor_cols] = matrix_[i][j];
      minor_cols++;
    }
    minor_rows++;
  }
  return minor;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_)
    throw "The matrix is ​​not square";
  double det = Determinant();
  if (fabs(det) < 1e-7)
    throw "Determinant is zero";
  S21Matrix inverse(rows_, cols_);
  inverse = CalcComplements().Transpose();
  inverse.MulNumber(1 / det);

  return inverse;
}

double S21Matrix::Determinant() {
  if (cols_ != rows_)
    throw "The matrix is ​​not square";
  double result = 0;
  if (rows_ == 1)
    result = matrix_[0][0];
  else if (rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    int sign = 1;
    for (int i = 0; i < cols_; i++) {
      result += matrix_[0][i] * Minor(0, i).Determinant() * sign;
      sign = -sign;
    }
  }
  return result;
}
S21Matrix S21Matrix::operator=(const S21Matrix &other) {
  S21Matrix(other.rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int k = 0; k < cols_; k++) {
      matrix_[i][k] = other.matrix_[i][k];
    }
  }
  return *this;
}
S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result = *this;
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result = *this;
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result = *this;
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) {
  MulNumber(num);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

void S21Matrix::operator+=(const S21Matrix &other) { SumMatrix(other); }

void S21Matrix::operator-=(const S21Matrix &other) { SubMatrix(other); }

void S21Matrix::operator*=(const S21Matrix &other) { MulMatrix(other); }

void S21Matrix::operator*=(const double num) { MulNumber(num); }

double &S21Matrix::operator()(int i, int j) {
  if (i < 0 || j < 0)
    throw "invalid size";
  return matrix_[i][j];
}

int S21Matrix::GetRows() { return rows_; }

int S21Matrix::GetCols() { return cols_; }

void S21Matrix::SetRows(int rows) {
  double **new_matrix;
  MemoryAllocation(&new_matrix, rows, cols_);
  if (rows > rows_) {
    for (int i = rows_; i < rows; i++) {
      for (int j = 0; j < cols_; j++) {
        new_matrix[i][j] = 0;
      }
    }
  } else if (rows < rows_) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols_; j++) {
        new_matrix[i][j] = matrix_[i][j];
      }
    }
  }
  this->~S21Matrix();
  rows_ = rows;
  matrix_ = new_matrix;
}
void S21Matrix::SetCols(int cols) {
  double **new_matrix;
  MemoryAllocation(&new_matrix, rows_, cols);
  if (cols > cols_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = cols_; j < cols; j++) {
        new_matrix[i][j] = 0;
      }
    }
  } else if (cols < cols_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols; j++) {
        new_matrix[i][j] = matrix_[i][j];
      }
    }
  }
  this->~S21Matrix();
  cols_ = cols;
  matrix_ = new_matrix;
}
void S21Matrix::MemoryAllocation(double ***matrix, int rows, int cols) {
  if (rows < 1 || cols < 1)
    throw "Incorrect matrix";
  *matrix = new double *[rows]();
  for (int i = 0; i < rows; i++) {
    (*matrix)[i] = new double[cols]();
  }
}