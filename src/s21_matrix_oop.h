#ifndef __S21MATRIX_OOP_H__
#define __S21MATRIX_OOP_H__
#include <iostream>
#include <math.h>
using namespace std;


class S21Matrix {
    private:
        // Attributes
        int rows_, cols_;         // Rows and columns
        double **matrix_;         // Pointer to the memory where the matrix is allocated
        void MemoryAllocation();  // Memory allocation
        void MemoryAllocation(double*** matrix, int rows, int cols);
    public:
        S21Matrix();              // Default constructor
        S21Matrix(int rows, int cols); // Parameterized constructor
        S21Matrix(const S21Matrix& other); // Copy constructor
        S21Matrix(S21Matrix&& other); // Transfer constructor
        ~S21Matrix();             // Destructor
        
        // Operators
        S21Matrix operator+(const S21Matrix& other);
        S21Matrix operator-(const S21Matrix& other);
        S21Matrix operator=(const S21Matrix& other);
        S21Matrix operator*(const S21Matrix& other);
        S21Matrix operator*(const double num);
        double& operator()(int i, int j);
        bool operator==(const S21Matrix& other) const;
        void operator+=(const S21Matrix& other);
        void operator-=(const S21Matrix& other);
        void operator*=(const S21Matrix& other);
        void operator*=(const double num);

        // Other methods..
        S21Matrix CalcComplements();
        S21Matrix Transpose();
        S21Matrix Minor(int rows, int cols);
        S21Matrix InverseMatrix();
        double Determinant();
        bool EqMatrix(const S21Matrix& other) const;
        void SumMatrix(const S21Matrix& other);
        void SubMatrix(const S21Matrix& other); 
        void MulNumber(const double num);
        void MulMatrix(const S21Matrix& other);

        // Accesors
        int GetRows();
        int GetCols();
        
        // Mutators
        void SetRows(int rows);
        void SetCols(int cols);
        
};

#endif //__S21MATRIX_OOP_H__