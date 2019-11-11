
#include <sstream>
#include <system_error>

namespace math {

template<typename T>
Row<T>::Row() {
    this->length = 0;
    this->data = nullptr;
}

template<typename T>
Row<T>::Row(ulong length) {
    this->length = length;
    data = new T[length];
}

template<typename T>
Row<T>::Row(const Row &row) {
    length = row.length;
    
    data = new T[length]();
    for (ulong i = 0; i < length; ++i) {
        data[i] = row.data[i];
    }
}

template<typename T>
Row<T>::Row(Row&& row) noexcept {
    length = row.length;
    data = row.data;
    row.data = nullptr;
}

template<typename T>
Row<T>::~Row() {
    delete[] data;
}

template<typename T>
Row<T>& Row<T>::operator=(Row row) {
    length = row.length;
    
    data = new T[length]();
    for (ulong i = 0; i < length; ++i) {
        data[i] = row.data[i];
    }
    
    return *this;
}

template<typename T>
T& Row<T>::operator[](ulong index) {
    if (index >= length) {
        std::stringstream s;
        s << "Invalid column index " << index;
        throw std::out_of_range(s.str());
    }
    return data[index];
}

template<typename T>
const T& Row<T>::operator[](ulong index) const {
    if (index >= length) {
        std::stringstream s;
        s << "Invalid column index " << index;
        throw std::out_of_range(s.str());
    }
    return data[index];
}

template<typename T>
void Row<T>::set_length(ulong length) {
    delete[] data;
    this->length = length;
    data = new T[length]();
}

template<typename T>
Matrix<T>::Matrix(ulong rows, ulong cols, T** content) {
    this->rows = rows;
    this->columns = cols;
    
    data = new Row<T>[rows];
    for (ulong i = 0; i < rows; ++i) {
        data[i].set_length(cols);
        for (ulong j = 0; j < columns; ++j) {
            data[i][j] = content[i][j];
        }
    }
}

template<typename T>
Matrix<T>::Matrix(ulong rows, ulong cols, T* content) {
    this->rows = rows;
    this->columns = cols;
    
    data = new Row<T>[rows];
    for (ulong i = 0; i < rows; ++i) {
        data[i].set_length(cols);
        for (ulong j = 0; j < columns; ++j) {
            data[i][j] = content[columns*i + j];
        }
    }
}

template<typename T>
Matrix<T>::Matrix(ulong rows, ulong cols) {
    this->rows = rows;
    this->columns = cols;
    
    data = new Row<T>[rows];
    for (ulong i = 0; i < rows; ++i) {
        data[i].set_length(cols);
    }
}

template<typename T>
Matrix<T>::Matrix(const Matrix &matrix) {
    rows = matrix.rows;
    columns = matrix.columns;
    
    data = new Row<T>[rows];
    for (ulong i = 0; i < rows; ++i) {
        data[i] = matrix.data[i];
    }
}

template<typename T>
Matrix<T>::Matrix(Matrix&& matrix) noexcept {
    rows = matrix.rows;
    columns = matrix.columns;
    data = matrix.data;
    matrix.data = nullptr;
}

template<typename T>
Matrix<T>::~Matrix() {
    delete[] data;
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T>& matrix) const {
    if (this->rows != matrix.rows || this->columns != matrix.columns)
        return false;
    for (ulong i = 0; i < this->rows; ++i) {
        for (ulong j = 0; j < this->columns; ++j) {
            if ((*this)[i][j] != matrix[i][j])
                return false;
        }
    }
    return true;
}

template<typename T>
Row<T>& Matrix<T>::operator[](ulong index) {
    if (index >= rows) {
        std::stringstream s;
        s << "Invalid row index " << index;
        throw std::out_of_range(s.str());
    }
    return data[index];
}

template<typename T>
const Row<T>& Matrix<T>::operator[](ulong index) const {
    if (index >= rows) {
        std::stringstream s;
        s << "Invalid row index " << index;
        throw std::out_of_range(s.str());
    }
    return data[index];
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &matrix) const {
    if (this->rows != matrix.rows || this->columns != matrix.columns) {
        throw std::invalid_argument("Matrix addition requires matrices to be the same size");
    }
    
    Matrix<T> out = Matrix(this->rows, this->columns);
    
    for (ulong i = 0; i < this->rows; ++i) {
        for (ulong j = 0; j < this->columns; ++j) {
            out[i][j] = (*this)[i][j] + matrix[i][j];
        }
    }
    
    return out;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &matrix) const {
    if (this->columns != matrix.rows) {
        throw std::invalid_argument("Matrix A columns must match Matrix B rows");
    }
    
    Matrix<T> out = Matrix<T>(this->rows, matrix.columns);
    
    for (ulong i = 0; i < this->rows; ++i) {
        for (ulong j = 0; j < matrix.columns; ++j) {
            T val = 0;
            for (ulong k = 0; k < this->columns; ++k) {
                val += (*this)[i][k] * matrix[k][j];
            }
            out[i][j] = val;
        }
    }
    
    return out;
}

template<typename T>
template<typename M>
Matrix<T> Matrix<T>::operator*(const M scale) const {
    Matrix<T> out = Matrix<T>(this->rows, this->columns);
    for (ulong i = 0; i < this->rows; ++i) {
        for (ulong j = 0; j < this->columns; ++j) {
            out[i][j] == (*this)[i][j] * scale;
        }
    }
}

}
