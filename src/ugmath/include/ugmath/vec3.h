#pragma once



namespace ugmath {

struct Vec3 {
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    constexpr Vec3() = default;
    constexpr Vec3(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

    constexpr Vec3& operator+=(const Vec3& rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    constexpr Vec3& operator-=(const Vec3& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    constexpr Vec3& operator*=(double scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }


    constexpr Vec3& operator/=(double scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }
};

constexpr Vec3 operator+(Vec3 lhs, const Vec3& rhs) {
    return lhs += rhs;
}

constexpr Vec3 operator-(Vec3 lhs, const Vec3& rhs) {
    return lhs -= rhs;
}

constexpr Vec3 operator-(const Vec3& v) {
    return Vec3(-v.x, -v.y, -v.z);
}

constexpr Vec3 operator*(Vec3 v, double scalar) {
    return v *= scalar;
}

constexpr Vec3 operator*(double scalar, Vec3 v) {
    return v *= scalar;
}

constexpr Vec3 operator/(Vec3 v, double scalar) {
    return v /= scalar;
}

constexpr double dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

constexpr Vec3 cross(const Vec3& a, const Vec3& b) {
    return Vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x);
}

constexpr double lengthSquared(const Vec3& v) {
    return dot(v, v);
}

double length(const Vec3& v);


Vec3 normalized(const Vec3& v, double eps = 1e-12);


bool normalize(Vec3& v, double eps = 1e-12);


bool approxEquals(const Vec3& a, const Vec3& b, double eps = 1e-12);

}
