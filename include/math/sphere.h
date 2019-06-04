#pragma once

#include "vector.h"

namespace math {

struct Sphere {
    
    Vector center;
    double radius;
    
    Sphere();
    
    Sphere(const Vector& center, double radius);
    
    Sphere(const Sphere& sphere);
    
};

}
