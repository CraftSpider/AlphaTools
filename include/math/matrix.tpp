
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
Row<T>::Row(const math::Row<T> &row) {
    length = row.length;
    
    data = new T[length];
    for (ulong i = 0; i < length; ++i) {
        data[i] = row.data[i];
    }
}

template<typename T>
Row<T>::~Row() {
    delete[] data;
}

template<typename T>
T Row<T>::operator[](ulong index) {
    if (index > length) {
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
    data = new T[length];
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
Matrix<T>::Matrix(const math::Matrix<T> &matrix) {
    rows = matrix.rows;
    columns = matrix.columns;
    
    data = new Row<T>[rows];
    for (ulong i = 0; i < rows; ++i) {
        data[i] = matrix.data[i];
    }
}

template<typename T>
Matrix<T>::~Matrix() {
    delete[] data;
}

template<typename T>
Row<T>& Matrix<T>::operator[](ulong index) {
    if (index > rows) {
        std::stringstream s;
        s << "Invalid row index " << index;
        throw std::out_of_range(s.str());
    }
    return data[index];
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const math::Matrix<T> &matrix) {
    if (this->columns != matrix.rows) {
        throw std::invalid_argument("Matrix A columns must match Matrix B rows");
    }
    
    Matrix<T> out = Matrix<T>(this->rows, matrix.columns);
    
    for (ulong i = 0; i < this->rows; ++i) {
        for (ulong j = 0; j < matrix.columns; ++j) {
            // TODO
        }
    }
}

}
