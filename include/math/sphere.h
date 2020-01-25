#pragma once

#include "vector.h"

/**
 * \file sphere.h
 * \brief Mathematical sphere support
 */

namespace math {

/**
 * Class that represents a Sphere. Supports various geometric operations, and can be translated or scaled easily.
 */
struct Sphere {
    
    Vector center;
    double radius;
    
    /**
     * Construct a degenerate sphere. Center at origin, radius of 0
     */
    Sphere();
    
    /**
     * Construct a sphere with the given center and radius
     *
     * \param center Center of the sphere in 3D space
     * \param radius Radius of the sphere
     */
    Sphere(const Vector& center, double radius);
    
    /**
     * Copy construct a sphere from another sphere
     *
     * \param sphere Sphere to copy
     */
    Sphere(const Sphere& sphere);
    
    /**
     * Check if this sphere is equal to another sphere
     *
     * \param sphere Sphere to check against
     * \return Whether the spheres are equal
     */
    bool operator==(const Sphere& sphere) const;
    
    /**
     * Check if this sphere is not equal to another sphere
     *
     * \param sphere Sphere to check against
     * \return Whether the spheres are not equal
     */
    bool operator!=(const Sphere& sphere) const;
    
    /**
     * Get a sphere translated by a vector
     *
     * \param vec Vector to translate by
     * \return Translated sphere
     */
    Sphere operator+(const Vector& vec) const;
    
    /**
     * Get a sphere with radius scaled by a scalar
     *
     * \tparam T Type to scale by
     * \param scale Amount to scale radius by
     * \return Scaled sphere
     */
    template<typename T>
    Sphere operator*(T scale) const;
    
    /**
     * Translate this sphere by a vector
     *
     * \param vec Vector to translate by
     * \return Reference to this
     */
    Sphere& operator+=(const Vector& vec);
    
    /**
     * Scale this sphere's radius by a scalar
     *
     * \tparam T Type to scale by
     * \param scale Amount to scale radius by
     * \return Reference to this
     */
    template<typename T>
    Sphere& operator*=(T scale);
    
    /**
     * Check whether a point lies inside this sphere
     *
     * \param point Point in space to check
     * \return Whether the point is inside the sphere
     */
    bool point_in_sphere(const Vector& point) const;
    
};

}

#include "sphere.tpp"
