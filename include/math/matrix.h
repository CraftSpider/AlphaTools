#pragma once

#include "types.h"

/**
 * \file matrix.h
 * \brief Mathematical matrix support
 */

namespace math {

/**
 * Class that represents a single row of a matrix. Used to allow bounds-checked and type-safe double-indexing of the
 * matrix. Is templated, see below for the type rules
 *
 * \tparam T Type to store in this row
 */
template<typename T = double>
class Row {
    
    ulong length;
    
    T* data;
    
public:
    
    /**
     * Default constructor for a Row, initializes with an empty data pointer
     */
    Row();
    
    /**
     * Create a new row with a starting length for the data array, initializes the backing array
     *
     * \param length Length of this Row
     */
    explicit Row(ulong length);
    
    /**
     * Copy constructor for this row, copies the data array
     *
     * \param row Row to copy
     */
    Row(const Row& row);
    
    /**
     * Move constructor for this row, moves the data array
     *
     * \param row Row to move
     */
    Row(Row&& row) noexcept;
    
    /**
     * Destruct this row, deleting the backing array safely
     */
    ~Row();
    
    /**
     * Copy assignment operator, copies the data array
     *
     * \param row Row to copy
     * \return Reference to this Row
     */
    Row<T>& operator=(const Row& row);
    
    /**
     * Index operator for this row. Returns a mutable reference to the backing
     * data at this index. Does bounds checking on the index.
     *
     * \param index Index to retrieve
     * \return Reference to data at the index
     */
    T& operator[](ulong index);
    
    /**
     * const Index operator for this row. Return a const reference to the backing
     * data at this index. Does bounds checking on the index
     *
     * \param index Index to retrieve
     * \return const Reference to data at the index
     */
    const T& operator[](ulong index) const;
    
    /**
     * Get the length of a row
     *
     * \return length of this row
     */
    ulong get_length();
    
    /**
     * Set the length of a row, empties the row and re-initializes the backing array
     *
     * \param length new length of this row
     */
    void set_length(ulong length);
    
};

/**
 * Class that represents a mathematical matrix. Useful for many kinds of algebra. The value stored is templated,
 * all that's required is that it define +, *, ==, !=, and support default construction.
 *
 * \tparam T Type to store in this matrix
 */
template<typename T = double>
class Matrix {
    
    ulong rows, columns;
    
    Row<T>* data;
    
public:
    
    Matrix(ulong rows, ulong cols, T** content);
    Matrix(ulong rows, ulong cols, T* content);
    Matrix(ulong rows, ulong cols);
    Matrix(const Matrix& matrix);
    Matrix(Matrix&& matrix) noexcept;
    ~Matrix();
    
    bool operator==(const Matrix<T>& matrix) const;
    
    Row<T>& operator[](ulong index);
    const Row<T>& operator[](ulong index) const;
    
    Matrix<T> operator+(const Matrix<T>& matrix) const;
    Matrix<T> operator*(const Matrix<T>& matrix) const;
    template<typename M>
    Matrix<T> operator*(const M scale) const;
    
    ulong get_rows();
    
    ulong get_columns();
    
    bool invertable() const; // TODO: This and lower
    
    Matrix<T> get_invert() const;
    void invert();
    
    Matrix<T> get_reduced() const;
    void reduce();
    
    T determinant();
    
};

}

#include "matrix.tpp"
