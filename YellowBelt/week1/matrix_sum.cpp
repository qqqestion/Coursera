#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;


class Matrix {
private:
    int num_rows;
    int num_cols;
    int **data = nullptr;

    void reallocate(int num_rows_, int num_cols_);

public:
    Matrix();
    Matrix(int num_rows_, int num_cols_); // throw out_of_range if num_rows | num_cols < 0

    void Reset(int num_rows_, int num_cols_); // throw out_of_range if num_rows | num_cols < 0
    int At(int row, int col) const;
    int& At(int row, int col);

    int GetNumRows() const;
    int GetNumColumns() const;

    friend istream& operator>>(istream &in, Matrix &matrix);
    friend ostream& operator<<(ostream &out, const Matrix &matrix);
    friend bool operator==(const Matrix &lhs, const Matrix &rhs);
    friend Matrix operator+(const Matrix &lhs, const Matrix &rhs); // throw invalid_argument if sizes are different
};

void Matrix::reallocate(int num_rows_, int num_cols_) {
    for (int i = 0; i < num_rows; ++i) {
        delete[] data;
    }
    delete[] data;
    num_rows = num_rows_;
    num_cols = num_cols_;
    for (int i = 0; i < num_cols; ++i) {
        data[i] = new int[num_cols];
    }
}

Matrix::Matrix() : num_rows(0), num_cols(0), data(nullptr)
{}

Matrix::Matrix(int num_rows_, int num_cols_) : num_rows(0), num_cols(0){
    if (num_rows_ < 0 or num_cols < 0) {
        throw out_of_range("Passed negative number in constructor");
    }
    reallocate(num_rows_, num_cols_);
} // throw out_of_range if num_rows | num_cols < 0

void Matrix::Reset(int num_rows_, int num_cols_) {
    if (num_rows_ < 0 or num_cols < 0) {
        throw out_of_range("Passed negative number in Reset");
    }
    reallocate(num_rows_, num_cols_);
    for (int i = 0; i < num_cols; ++i) {
        for (int j = 0; j < num_cols; ++j) {
            data[i][j] = 0;
        }
    }
} // throw out_of_range if num_rows | num_cols < 0

int Matrix::At(int row, int col) const {
    if (row < 0 or row >= num_rows or col < 0 or col >= num_cols) {
        throw out_of_range("Passed negative number in At");
    }
    return data[row][col];
}
int& Matrix::At(int row, int col) {
    if (row < 0 or row >= num_rows or col < 0 or col >= num_cols) {
        throw out_of_range("Passed negative number in At");
    }
    return data[row][col];
}

int Matrix::GetNumRows() const {
    return num_rows;
}
int Matrix::GetNumColumns() const {
    return num_cols;
}

istream& operator>>(istream &in, Matrix &matrix) {
    in >> matrix.num_rows >> matrix.num_cols;
    matrix.data = 
}
ostream& operator<<(ostream &out, const Matrix &matrix);
bool operator==(const Matrix &lhs, const Matrix &rhs);
Matrix operator+(const Matrix &lhs, const Matrix &rhs); // throw invalid_argument if sizes are different


int main() {
  Matrix one;
  Matrix two;

  cin >> one >> two;
  cout << one + two << endl;
  return 0;
}