
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

bool Sphere::operator==(const Sphere &sphere) const {
    return center == sphere.center && radius == sphere.radius;
}

Sphere Sphere::operator+(const Vector &vec) const {
    return Sphere(center + vec, radius);
}

Sphere& Sphere::operator+=(const math::Vector& vec) {
    this->center += vec;
    return *this;
}

bool Sphere::point_in_sphere(const Vector &point) const {
    return Vector::distance(center, point) <= radius;
}

}
