#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

class Matrix {
 private:
  unsigned int rows;  // Number of rows in the Matrix
  unsigned int cols;  // Number of columns in the Matrix
  double** data;      // Data in the Matrix

 public:
  Matrix();                                                                       // Default constructor
  Matrix(unsigned int n_rows, unsigned int n_cols, double value);                 // Constructor with params
  Matrix(const Matrix& otherMatrix);                                              // Copy constructor
  ~Matrix();                                                                      // Destructor
  bool set(unsigned int row, unsigned int col, double value);                     // Set the value at the given row and column
  bool get(unsigned int row, unsigned int col, double& value) const;              // Get the value at the given row and column
  unsigned int num_rows() const;                                                  // Get the number of rows
  unsigned int num_cols() const;                                                  // Get the number of columns
  void multiply_by_coefficient(double coefficient);                               // Multiplies the matrix by a coefficient
  bool swap_row(unsigned int row1, unsigned int row2);                            // Swap the two given rows
  void transpose();                                                               // Flip/transpose matrix
  void clear();                                                                   // Destructor but does not destroy
  bool add(const Matrix& B);                                                      // Add the matrix B to this matrix
  bool subtract(const Matrix& B);                                                 // Subtract the matrix B from this matrix
  double* get_row(unsigned int row) const;                                        // Get the given row || NULL
  double* get_col(unsigned int col) const;                                        // Get the given column || NULL
  Matrix* quarter() const;                                                        // Get the 4 quarters of the matrix
  bool operator==(const Matrix& otherMatrix) const;                               // Equality operator
  bool operator!=(const Matrix& otherMatrix) const;                               // Inequality operator
  friend std::ostream& operator<<(std::ostream& out, const Matrix& otherMatrix);  // Overload output operator
  Matrix& operator=(const Matrix& otherMatrix);                                   // Set operator
};

#endif