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
    ~Row();
    
    T operator[](ulong index);
    
    void set_length(ulong length);
    
};

template<typename T = double>
struct Matrix {
    
    ulong rows, columns;
    
    Row<T>* data;
    
    Matrix(ulong rows, ulong cols);
    Matrix(const Matrix& matrix);
    ~Matrix();
    
    Row<T>& operator[](ulong index);
    
    Matrix<T> operator*(const Matrix<T>& matrix);
    
};

}

#include "matrix.tpp"
