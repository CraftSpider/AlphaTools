#pragma once

namespace math {

struct Vector {
    
    static Vector zero_vec, one_vec, x_axis, y_axis, z_axis;
    
    double x, y, z;
    
    Vector() noexcept;
    
    explicit Vector(double scale) noexcept;
    
    Vector(double x, double y, double z) noexcept;
    
    Vector(const Vector& vec) noexcept;
    
    template<typename T>
    Vector operator+(T scale) const;
    
    Vector operator+(const Vector& vec) const;
    
    template<typename T>
    Vector operator-(T scale) const;
    
    Vector operator-(const Vector& vec) const;
    
    template<typename T>
    Vector operator*(T scale) const;
    
    Vector operator*(const Vector& vec) const;
    
    template<typename T>
    Vector operator/(T scale) const;
    
    Vector operator/(const Vector& vec) const;
    
    double operator|(const Vector& vec) const;
    
    Vector operator^(const Vector& vec) const;
    
    template<typename T>
    void operator+=(T scale);
    
    void operator+=(const Vector& vec);
    
    template<typename T>
    void operator-=(T scale);
    
    void operator-=(const Vector& vec);
    
    template<typename T>
    void operator*=(T scale);
    
    void operator*=(const Vector& vec);
    
    template<typename T>
    void operator/=(T scale);
    
    void operator/=(const Vector& vec);
    
    double dot(const Vector& vec) const;
    
    Vector cross(const Vector& vec) const;
    
    double distance_sq(const Vector& vec) const;
    
    double distance(const Vector& vec) const;
    
    double length() const;
    
    Vector get_normalized() const;
    
    Vector& normalize();
    
    static double distance_sq(const Vector& a, const Vector& b);
    
    static double distance(const Vector& a, const Vector& b);
    
};

}

#include "vector.tpp"
