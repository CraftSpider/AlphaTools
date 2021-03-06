
namespace math {

template<typename T>
Vector Vector::operator+(T scale) const {
    return Vector(x + scale, y + scale, z + scale);
}

template<typename T>
Vector Vector::operator-(T scale) const {
    return Vector(x - scale, y - scale, z - scale);
}

template<typename T>
Vector Vector::operator*(T scale) const {
    return Vector(x * scale, y * scale, z * scale);
}

template<typename T>
Vector Vector::operator/(T scale) const {
    return Vector(x / scale, y / scale, z / scale);
}

template<typename T>
Vector& Vector::operator+=(T scale) {
    x += scale;
    y += scale;
    z += scale;
    return *this;
}

template<typename T>
Vector& Vector::operator-=(T scale) {
    x -= scale;
    y -= scale;
    z -= scale;
    return *this;
}

template<typename T>
Vector& Vector::operator*=(T scale) {
    x *= scale;
    y *= scale;
    z *= scale;
    return *this;
}

template<typename T>
Vector& Vector::operator/=(T scale) {
    x /= scale;
    y /= scale;
    z /= scale;
    return *this;
}

}
