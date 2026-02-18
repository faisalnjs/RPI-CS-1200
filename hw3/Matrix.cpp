#include "Matrix.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

Matrix::Matrix() {  // Default constructor
  rows = 0;         // Sets rows 0
  cols = 0;         // Sets cols to 0
  data = NULL;      // Sets data to NULL
}

Matrix::Matrix(unsigned int n_rows, unsigned int n_cols, double value) {  // Constructor with params
  rows = n_rows;                                                          // Set the number of rows
  cols = n_cols;                                                          // Set the number of columns
  data = new double*[rows];                                               // Set the data
  for (unsigned int i = 0; i < rows; i++) {                               // For each row...
    data[i] = new double[cols];                                           // Allocate memory for the columns
    for (unsigned int j = 0; j < cols; j++) data[i][j] = value;           // For each column, set the value
  }
}

Matrix::Matrix(const Matrix& otherMatrix) {                                       // Copy constructor creates a deep copy of the given matrix
  rows = otherMatrix.rows;                                                        // Set the number of rows
  cols = otherMatrix.cols;                                                        // Set the number of columns
  data = new double*[rows];                                                       // Set the data
  for (unsigned int i = 0; i < rows; i++) {                                       // For each row...
    data[i] = new double[cols];                                                   // Allocate memory for the columns
    for (unsigned int j = 0; j < cols; j++) data[i][j] = otherMatrix.data[i][j];  // For each column, copy the value from the original matrix
  }
}

Matrix::~Matrix() {                                          // Destructor
  for (unsigned int i = 0; i < rows; i++) delete[] data[i];  // For each row, delete the columns
  delete[] data;                                             // Delete the data from heap
}

bool Matrix::set(unsigned int row, unsigned int col, double value) {  // Set the value at the given row and column
  if ((row >= rows) || (col >= cols)) return false;                   // Out of bounds
  data[row][col] = value;                                             // Set the value
  return true;
}

bool Matrix::get(unsigned int row, unsigned int col, double& value) const {  // Get the value at the given row and column
  if ((row >= rows) || (col >= cols)) return false;                          // Out of bounds
  value = data[row][col];                                                    // Set the value
  return true;
}

unsigned int Matrix::num_rows() const { return rows; }  // Get the number of rows

unsigned int Matrix::num_cols() const { return cols; }  // Get the number of cols

void Matrix::multiply_by_coefficient(double coefficient) {              // Multiplies the matrix by a coefficient
  for (unsigned int i = 0; i < rows; i++) {                             // For each row...
    for (unsigned int j = 0; j < cols; j++) data[i][j] *= coefficient;  // For each column, multiply the value by coefficient
  }
}

bool Matrix::swap_row(unsigned int row1, unsigned int row2) {  // Swap the two given rows
  if ((row1 >= rows) || (row2 >= rows)) return false;          // Out of bounds
  double* temp = data[row1];                                   // row1 -> temp
  data[row1] = data[row2];                                     // row2 -> row1
  data[row2] = temp;                                           // temp -> row2
  return true;
}

void Matrix::transpose() {                                                    // Flip/transpose matrix
  unsigned int old_rows = rows;                                               // Original number of rows
  unsigned int old_cols = cols;                                               // Original number of columns
  if ((old_rows == 0) || (old_cols == 0)) return;                             // Empty matrix
  double** new_data = new double*[old_cols];                                  // Flip dimensions
  for (unsigned int i = 0; i < old_cols; i++) {                               // For each row...
    new_data[i] = new double[old_rows];                                       // Allocate memory for the columns
    for (unsigned int j = 0; j < old_rows; j++) new_data[i][j] = data[j][i];  // For each column, set the value to the flipped value from the original matrix
  }
  clear();          // Clear the original data
  data = new_data;  // Set the data to the new data
  rows = old_cols;  // Update rows
  cols = old_rows;  // Update columns
}

void Matrix::clear() {                                       // Destructor but does not destroy
  for (unsigned int i = 0; i < rows; i++) delete[] data[i];  // For each row, delete the columns
  delete[] data;                                             // Delete the data from heap
  rows = 0;                                                  // Set rows to 0
  cols = 0;                                                  // Set cols to 0
}

bool Matrix::add(const Matrix& B) {                                      // Add the matrix B to this matrix
  if ((rows != B.rows) || (cols != B.cols)) return false;                // Dimensions don't match
  for (unsigned int i = 0; i < rows; i++) {                              // For each row...
    for (unsigned int j = 0; j < cols; j++) data[i][j] += B.data[i][j];  // For each column, add the value from matrix B to this matrix
  }
  return true;
}

bool Matrix::subtract(const Matrix& B) {                                 // Subtract the matrix B from this matrix
  if ((rows != B.rows) || (cols != B.cols)) return false;                // Dimensions don't match
  for (unsigned int i = 0; i < rows; i++) {                              // For each row...
    for (unsigned int j = 0; j < cols; j++) data[i][j] -= B.data[i][j];  // For each column, subtract the value from matrix B from this matrix
  }
  return true;
}

double* Matrix::get_row(unsigned int row) const {                      // Get the given row || NULL
  if (row >= rows) return NULL;                                        // Out of bounds
  double* row_data = new double[cols];                                 // Create new array for the row data
  for (unsigned int i = 0; i < cols; i++) row_data[i] = data[row][i];  // For each column, set the value from the original matrix to the new array
  return row_data;
}

double* Matrix::get_col(unsigned int col) const {                      // Get the given column || NULL
  if (col >= cols) return NULL;                                        // Out of bounds
  double* col_data = new double[rows];                                 // Create new array for the column data
  for (unsigned int i = 0; i < rows; i++) col_data[i] = data[i][col];  // For each row, set the value from the original matrix to the new array
  return col_data;
}

Matrix* Matrix::quarter() const {                                                                                                        // Get the 4 quarters of the matrix
  unsigned int half_rows = std::ceil(rows / 2.0);                                                                                        // Get half the number of rows, rounded up
  unsigned int half_cols = std::ceil(cols / 2.0);                                                                                        // Get half the number of columns, rounded up
  Matrix* quadrants = new Matrix[4];                                                                                                     // Create new Matrix quadrants
  quadrants[0] = Matrix(half_rows, half_cols, 0);                                                                                        // Initialize UL Matrix
  quadrants[1] = Matrix(half_rows, half_cols, 0);                                                                                        // Initialize UR Matrix
  quadrants[2] = Matrix(half_rows, half_cols, 0);                                                                                        // Initialize LL Matrix
  quadrants[3] = Matrix(half_rows, half_cols, 0);                                                                                        // Initialize LR Matrix
  unsigned int row_start_bottom = (rows >= half_rows) ? (rows - half_rows) : 0;                                                          // Start row for the bottom quadrants
  unsigned int col_start_right = (cols >= half_cols) ? (cols - half_cols) : 0;                                                           // Start column for the right quadrants
  for (unsigned int i = 0; i < rows; i++) {                                                                                              // For each row...
    for (unsigned int j = 0; j < cols; j++) {                                                                                            // For each column...
      if ((i < half_rows) && (j < half_cols)) quadrants[0].data[i][j] = data[i][j];                                                      // Set the value in UL
      if ((i < half_rows) && (j >= col_start_right)) quadrants[1].data[i][j - col_start_right] = data[i][j];                             // Set the value in UR
      if ((i >= row_start_bottom) && (j < half_cols)) quadrants[2].data[i - row_start_bottom][j] = data[i][j];                           // Set the value in LL
      if ((i >= row_start_bottom) && (j >= col_start_right)) quadrants[3].data[i - row_start_bottom][j - col_start_right] = data[i][j];  // Set the value in LR
    }
  }
  return quadrants;
}

bool Matrix::operator==(const Matrix& otherMatrix) const {                     // Equality operator
  if ((rows != otherMatrix.rows) || (cols != otherMatrix.cols)) return false;  // Dimensions don't match
  for (unsigned int i = 0; i < rows; ++i) {                                    // For each row...
    for (unsigned int j = 0; j < cols; ++j) {                                  // For each column...
      if (data[i][j] != otherMatrix.data[i][j]) return false;                  // Any value doesn't match
    }
  }
  return true;
}

bool Matrix::operator!=(const Matrix& otherMatrix) const { return !(*this == otherMatrix); }  // Inequality operator

std::ostream& operator<<(std::ostream& out, const Matrix& m) {  // Overload output operator
  out << "\n"
      << m.rows << " x " << m.cols << " matrix:\n";  // Print the dimensions
  if ((m.rows == 0) || (m.cols == 0)) {              // Empty matrix
    out << "[ ]\n";
    return out;
  }
  out << "[ ";                                   // Not empty matrix
  for (unsigned int i = 0; i < m.rows; ++i) {    // For each row...
    if (i > 0) out << "  ";                      // Required space to match sample output
    for (unsigned int j = 0; j < m.cols; ++j) {  // For each column...
      out << m.data[i][j];                       // Print value
      if ((j + 1) < m.cols) out << " ";          // Add a space if not the last column
    }
    out << (((i + 1) < m.rows) ? "\n" : " ");  // New line if not the last row, else a space
  }
  out << "]\n";
  return out;
}

Matrix& Matrix::operator=(const Matrix& otherMatrix) {                            // Set operator
  if (this == &otherMatrix) return *this;                                         // Is itself
  for (unsigned int i = 0; i < rows; i++) delete[] data[i];                       // For each row, delete the columns
  delete[] data;                                                                  // Delete the data from heap
  rows = otherMatrix.rows;                                                        // Set the number of rows
  cols = otherMatrix.cols;                                                        // Set the number of columns
  data = new double*[rows];                                                       // Set the data
  for (unsigned int i = 0; i < rows; i++) {                                       // For each row...
    data[i] = new double[cols];                                                   // Allocate memory for the columns
    for (unsigned int j = 0; j < cols; j++) data[i][j] = otherMatrix.data[i][j];  // For each column, set the value
  }
  return *this;
}