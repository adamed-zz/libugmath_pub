#pragma once
#include "r7_iter.h"





namespace UGS {
namespace Math {

struct Vector3f {
    float x;
    float y;
    float z;

    Vector3f();
    Vector3f(float a, float b, float c);








    Vector3f(double a, double b, double c);
    Vector3f(float* p);
    Vector3f(double* v);

    Vector3f& operator=(const Vector3f& rhs);


    Vector3f(const Vector3f& o);
    float* c_array();
    Internals::ArrayIterator<float> begin();
    Internals::ArrayIterator<float> end();
    Internals::ArrayIterator<const float> begin() const;
    Internals::ArrayIterator<const float> cend() const;

    const float& operator[](int i) const;

    void Set(float a, float b, float c);
    void Set(const float* p);
    void Set(const double* p);
    void SetZero();

    int size() const;
    const float* data() const;

    bool Equals(const Vector3f& o, float tolerance) const;
    bool IsPreciseZero() const;
    bool IsZero(float tolerance) const;
    float Length() const;
    float LengthSquared() const;
    bool PreciseEquals(const Vector3f& o) const;

    Vector3f& Unitize();
    Vector3f Unitized() const;
};

static_assert(sizeof(Vector3f) == 12, "Vector3f 布局必须与 raw 一致（12 字节）");

}
}
