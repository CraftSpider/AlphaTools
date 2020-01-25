#pragma once

/**
 * \file vector.h
 * \brief Mathematical vector support
 */

namespace math {

/**
 * Class that represents a Mathematical vector with 3 elements. Useful for all sorts of geometric and physical things.
 * Provides all sorts of operators. | is overloaded for dot product, and ^ for cross product.
 */
struct Vector {
    
    static Vector zero_vec, one_vec, x_axis, y_axis, z_axis;
    
    double x, y, z;
    
    /**
     * Default construct a vector, with 0 for all its values
     */
    Vector() noexcept;
    
    /**
     * Construct a vector with the given scale, all values will be initialized to the scale
     *
     * \param scale Beginning vector value
     */
    explicit Vector(double scale) noexcept;
    
    /**
     * Construct a vector with the given values
     *
     * \param x X value to start with
     * \param y Y value to start with
     * \param z Z value to start with
     */
    Vector(double x, double y, double z) noexcept;
    
    /**
     * Copy-construct a vector from another vector
     *
     * \param vec Vector to copy
     */
    Vector(const Vector& vec) noexcept;
    
    /**
     * Compare whether two vectors are equal
     *
     * \param vec Vector to compare against
     * \return Whether vectors are equal
     */
    bool operator==(const Vector& vec) const;
    
    /**
     * Compare whether two vectors are not equal
     *
     * \param vec Vector to compare against
     * \return Whether vectors are not equal
     */
    bool operator!=(const Vector& vec) const;
    
    /**
     * Invert all components of a vector, effectively reversing its direction
     *
     * \return Flipped vector
     */
    Vector operator-() const;
    
    /**
     * Add a scalar to this vector, each component increased by the scalar
     *
     * \tparam T Type to scale by
     * \param scale Amount to scale
     * \return Scaled vector
     */
    template<typename T>
    Vector operator+(T scale) const;
    
    /**
     * Perform vector addition between this and another vector
     *
     * \param vec Vector to add
     * \return Summed vector
     */
    Vector operator+(const Vector& vec) const;
    
    /**
     * Subtract a scalar from this vector, each component decreased by the scalar
     *
     * \tparam T Type to scale by
     * \param scale Amount to scale
     * \return Scaled vector
     */
    template<typename T>
    Vector operator-(T scale) const;
    
    /**
     * Perform vector subtraction between this and another vector
     *
     * \param vec Vector to subtract
     * \return Vector difference
     */
    Vector operator-(const Vector& vec) const;
    
    /**
     * Multiply this vector by a scalar, each component multiplied by the scalar
     *
     * \tparam T Type to scale by
     * \param scale Amount to scale
     * \return Scaled vector
     */
    template<typename T>
    Vector operator*(T scale) const;
    
    /**
     * Perform component-wise vector multiplication
     *
     * \param vec Vector to multiply
     * \return Multiplied vector
     */
    Vector operator*(const Vector& vec) const;
    
    /**
     * Divide this vector by a scalar, each component divided by the scalar
     *
     * \tparam T Type to scale be
     * \param scale Amount to scale
     * \return Scaled vector
     */
    template<typename T>
    Vector operator/(T scale) const;
    
    /**
     * Perform component-wise vector division
     *
     * \param vec Vector to divide by
     * \return Divided vector
     */
    Vector operator/(const Vector& vec) const;
    
    /**
     * Get the dot product of this vector with another vector
     *
     * \param vec Vector to dot with
     * \return Vector dot product
     */
    double operator|(const Vector& vec) const;
    
    /**
     * Cross this vector with another vector
     *
     * \param vec Vector to cross
     * \return Vector cross product
     */
    Vector operator^(const Vector& vec) const;
    
    /**
     * Add a scalar to this vector in-place
     *
     * \tparam T Type to scale by
     * \param scale Amount to scale
     */
    template<typename T>
    Vector& operator+=(T scale);
    
    /**
     * Perform in-place vector addition with another vector
     *
     * \param vec Vector to add
     */
    Vector& operator+=(const Vector& vec);
    
    /**
     * Subtract a scalar from this vector in-place
     *
     * \tparam T Type to scale by
     * \param scale Amount to scale
     */
    template<typename T>
    Vector& operator-=(T scale);
    
    /**
     * Perform in-place vector subtraction with another vector
     *
     * \param vec Vector to subtract
     */
    Vector& operator-=(const Vector& vec);
    
    /**
     * Multiply a scalar with this vector in-place
     *
     * \tparam T Type to scale by
     * \param scale Amount to scale
     */
    template<typename T>
    Vector& operator*=(T scale);
    
    /**
     * Perform in-place component-wise vector multiplication with another vector
     *
     * \param vec Vector to multiply
     */
    Vector& operator*=(const Vector& vec);
    
    /**
     * Divide a scalar from this vector in-place
     *
     * \tparam T Type to scale by
     * \param scale Amount to scale
     */
    template<typename T>
    Vector& operator/=(T scale);
    
    /**
     * Perform in-place component-wise vector division with another vector
     *
     * \param vec Vector to divide by
     */
    Vector& operator/=(const Vector& vec);
    
    /**
     * Get the distance squared between two vectors. Skips a square root operation in normal
     * distance calculation
     *
     * \param a First vector
     * \param b Second vector
     * \return Squared distance between them
     */
    static double distance_sq(const Vector& a, const Vector& b);
    
    /**
     * Get the distance between two vectors
     *
     * \param a First vector
     * \param b Second vector
     * \return Distance between them
     */
    static double distance(const Vector& a, const Vector& b);
    
    /**
     * Get the dot-product of this vector with another vector
     *
     * \param vec Vector to dot with
     * \return Result of vector dot product
     */
    double dot(const Vector& vec) const;
    
    /**
     * Get the cross-product of this vector with another vector
     *
     * \param vec Vector to cross with
     * \return Result of vector cross product
     */
    Vector cross(const Vector& vec) const;
    
    /**
     * Get the distance squared between this vector and another vector. Skips a square root operation
     * in normal distance calculation
     *
     * \param vec Other vector
     * \return Squared distance from this to vec
     */
    double distance_sq(const Vector& vec) const;
    
    /**
     * Get the distance between this vector and another vector
     *
     * \param vec Other vector
     * \return Distance from this to vec
     */
    double distance(const Vector& vec) const;
    
    /**
     * Get the length of this vector, or distance from origin
     *
     * \return Length of this vector
     */
    double length() const;
    
    /**
     * Get the normalize form of this vector, the vector with the same direction but a length of 1
     *
     * \return Normal vector
     */
    Vector get_normalized() const;
    
    /**
     * Normalize this vector in-place, making the length one while keeping the same direction
     *
     * \return Reference to this
     */
    Vector& normalize();
    
};

}

#include "vector.tpp"
