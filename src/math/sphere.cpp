
#include "math/sphere.h"

namespace math {

Sphere::Sphere() {
    center = Vector::zero_vec;
    radius = 0;
}

Sphere::Sphere(const Vector& center, double radius) {
    this->center = center;
    this->radius = radius;
}

Sphere::Sphere(const math::Sphere& sphere) {
    center = sphere.center;
    radius = sphere.radius;
}

}
