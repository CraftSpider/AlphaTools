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
    
    /**
     * Construct a matrix with the given number of rows and columns, with data initialized from the given 2D array
     *
     * \param rows Number of rows in the matrix
     * \param cols Number of columns in the matrix
     * \param content Data to initialize the matrix with
     */
    Matrix(ulong rows, ulong cols, T** content);
    
    /**
     * Construct a matrix with the given number of rows and columns, with data initialized from the given array
     *
     * \param rows Number of rows in the matrix
     * \param cols Number of columns in the matrix
     * \param content Data to initialize the array with.
     */
    Matrix(ulong rows, ulong cols, T* content);
    
    /**
     * Construct a matrix with the given number of rows and columns, with data initialized to the default constructor
     *
     * \param rows Number of rows in the matrix
     * \param cols Number of columns in the matrix
     */
    Matrix(ulong rows, ulong cols);
    
    /**
     * Copy constructor for a matrix, copies the data array
     *
     * \param matrix Matrix to copy
     */
    Matrix(const Matrix& matrix);
    
    /**
     * Move constructor for a matrix, moves the data array
     *
     * \param matrix Matrix to move
     */
    Matrix(Matrix&& matrix) noexcept;
    
    /**
     * Matrix destructor, ensures that the matrix data is deleted
     */
    ~Matrix();
    
    /**
     * Compare this matrix to another matrix. Matrices are defined as equal only if all
     * of their elements are equal
     *
     * \param matrix Matrix to compare against
     * \return Whether matrices are identical
     */
    bool operator==(const Matrix<T>& matrix) const;
    
    /**
     * Element access on the matrix. Returns a mutable reference to a row from the matrix, with bounds checking
     *
     * \param index Index of row to access
     * \return reference to the row
     */
    Row<T>& operator[](ulong index);
    
    /**
     * Element access on the matrix. Return a const reference to a row from the matrix, with bounds checking
     *
     * \param index Index of row to access
     * \return const reference to the row
     */
    const Row<T>& operator[](ulong index) const;
    
    /**
     * Add another matrix to this matrix. Can only be done if the number of rows and columns on both matrices are
     * the same
     *
     * \param matrix Matrix to add
     * \return New matrix, with summed elements
     */
    Matrix<T> operator+(const Matrix<T>& matrix) const;
    
    /**
     * Multiply another matrix with this matrix. Does cross-multiplication, and as such can only be done if the
     * number of columns on this matrix matches the number of rows on the other.
     *
     * \param matrix Matrix to multiply
     * \return New matrix, of size (this->rows, matrix.columns)
     */
    Matrix<T> operator*(const Matrix<T>& matrix) const;
    
    /**
     * Multiply a scalar with this matrix. Does element-wise multiplication, so each element is multiplied by the scale
     *
     * \tparam M Type of the scale
     * \param scale Amount to scale by
     * \return New matrix, with element scaled
     */
    template<typename M>
    Matrix<T> operator*(const M scale) const;
    
    /**
     * Get the number of rows in this matrix
     *
     * \return Number of rows
     */
    ulong get_rows();
    
    /**
     * Get the number of columns in this matrix
     *
     * \return Number of columns
     */
    ulong get_columns();
    
    /**
     * Checks whether this matrix is invertable
     *
     * \return Invertability of matrix
     */
    bool invertable() const; // TODO: This and lower
    
    /**
     * Get the inverted form of this matrix, if it is invertable
     *
     * \return Inverted matrix
     */
    Matrix<T> get_invert() const;
    
    /**
     * Invert the matrix in-place, if it is invertable
     */
    void invert();
    
    /**
     * Get the row-reduced form of this matrix
     *
     * \return Reduced matrix
     */
    Matrix<T> get_reduced() const;
    
    /**
     * Row-reduce this matrix in-place
     */
    void reduce();
    
    /**
     * Calculate the determinant of this matrix. *does not* use a naive algorithm with explosive complexity
     *
     * \return Determinant of the matrix
     */
    T determinant();
    
};

}

#include "matrix.tpp"
