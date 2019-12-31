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
    
    Sphere();
    
    Sphere(const Vector& center, double radius);
    
    Sphere(const Sphere& sphere);
    
    bool operator==(const Sphere& sphere) const;
    
    Sphere operator+(const Vector& vec) const;
    
    template<typename T>
    Sphere operator*(T scale) const;
    
    Sphere& operator +=(const Vector& vec);
    
    template<typename T>
    Sphere& operator *=(T scale);
    
    bool point_in_sphere(const Vector& point) const;
    
};

}

#include "sphere.tpp"
