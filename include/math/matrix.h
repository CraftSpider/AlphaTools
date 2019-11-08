#pragma once

#include "types.h"

namespace math {

template<typename T = double>
struct Row {
    
    ulong length{};
    
    T* data;
    
    Row();
    explicit Row(ulong length);
    Row(const Row& row);
    Row(Row&& row) noexcept;
    ~Row();
    
    Row<T>& operator=(Row row);
    T& operator[](ulong index);
    const T& operator[](ulong index) const;
    
    void set_length(ulong length);
    
};

template<typename T = double>
struct Matrix {
    
    ulong rows, columns;
    
    Row<T>* data;
    
    Matrix(ulong rows, ulong cols, T** content);
    Matrix(ulong rows, ulong cols, T* content);
    Matrix(ulong rows, ulong cols);
    Matrix(const Matrix& matrix);
    Matrix(Matrix&& matrix) noexcept;
    ~Matrix();
    
    Row<T>& operator[](ulong index);
    const Row<T>& operator[](ulong index) const;
    
    Matrix<T> operator*(const Matrix<T>& matrix);
    
};

}

#include "matrix.tpp"
