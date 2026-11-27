#include "ugmath/vector3f.h"

#include <cmath>
#include <cstring>










namespace UGS {
namespace Math {

Vector3f::Vector3f() {
    x = y = z = 0.0f;
}

Vector3f::Vector3f(float a, float b, float c) {
    x = a;
    y = b;
    z = c;
}




Vector3f::Vector3f(double a, double b, double c) {
    x = a;
    y = b;
    z = c;
}


Vector3f::Vector3f(float* p) {
    x = p[0];
    y = p[1];
    z = p[2];
}



Vector3f::Vector3f(double* v)
    : x(static_cast<float>(v[0]))
    , y(static_cast<float>(v[1]))
    , z(static_cast<float>(v[2]))
{
}





Vector3f& Vector3f::operator=(const Vector3f& rhs) {
    std::memcpy(this, &rhs, sizeof(*this));
    return *this;
}




const float& Vector3f::operator[](int i) const {
    return reinterpret_cast<const float*>(this)[i];
}

void Vector3f::Set(float a, float b, float c) {
    x = a;
    y = b;
    z = c;
}

void Vector3f::Set(const float* p) {
    x = p[0];
    y = p[1];
    z = p[2];
}

void Vector3f::Set(const double* p) {
    x = static_cast<float>(p[0]);
    y = static_cast<float>(p[1]);
    z = static_cast<float>(p[2]);
}

void Vector3f::SetZero() {
    x = y = z = 0.0f;
}

int Vector3f::size() const {
    return 3;
}

const float* Vector3f::data() const {
    return &x;
}

bool Vector3f::Equals(const Vector3f& o, float tolerance) const {
    float dx = x - o.x;
    float dy = y - o.y;
    float dz = z - o.z;
    return tolerance >= sqrtf(dx * dx + dy * dy + dz * dz);
}

bool Vector3f::IsPreciseZero() const {
    return x == 0.0f && y == 0.0f && z == 0.0f;
}

bool Vector3f::IsZero(float tolerance) const {
    float r = x * x;
    r += y * y;
    r += z * z;
    return tolerance >= sqrtf(r);
}

float Vector3f::Length() const {
    float r = x * x;
    r += y * y;
    r += z * z;
    return sqrtf(r);
}

float Vector3f::LengthSquared() const {
    float r = x * x;
    r += y * y;
    r += z * z;
    return r;
}

bool Vector3f::PreciseEquals(const Vector3f& o) const {
    return x == o.x && y == o.y && z == o.z;
}

Vector3f& Vector3f::Unitize() {
    float len2 = x * x;
    len2 += y * y;
    len2 += z * z;
    float len = sqrtf(len2);
    if (len != 0.0f) {
        x /= len;
        y /= len;
        z /= len;
    }
    return *this;
}

Vector3f Vector3f::Unitized() const {



    float xx = x;
    float yy = y;
    float zz = z;
    float len2 = xx * xx;
    len2 += yy * yy;
    len2 += zz * zz;
    float len = sqrtf(len2);
    Vector3f out;
    if (len != 0.0f) {
        out.x = xx / len;
        out.y = yy / len;
        out.z = zz / len;
    } else {
        out.x = xx;
        out.y = yy;
        out.z = zz;
    }
    return out;
}

}
}
