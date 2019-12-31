
namespace math {

template<typename T>
Sphere Sphere::operator*(T scale) const {
    return Sphere(center, radius * scale);
}

template<typename T>
Sphere& Sphere::operator*=(T scale) {
    this->radius *= scale;
    return *this;
}

}
