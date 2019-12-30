#pragma once

#include "vector.h"

/**
 * \file sphere.h
 * \brief Mathematical sphere support
 */

namespace math {

struct Sphere {
    
    Vector center;
    double radius;
    
    Sphere();
    
    Sphere(const Vector& center, double radius);
    
    Sphere(const Sphere& sphere);
    
};

}
