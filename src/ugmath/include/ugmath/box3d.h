#pragma once

#include <cstddef>

#include "ugmath/matrix3.h"
#include "ugmath/point3.h"
#include "ugmath/vector3.h"












namespace UGS {
namespace Math {



class alignas(8) Box3D {
public:
    void* vftable;
    double matrix[9];
    double origin[3];
    double length[3];
    unsigned char dirty;


    double corners[8][3];
    unsigned long long cached;

    double GetXLength() const;
    double GetYLength() const;
    double GetZLength() const;

    void GetLengths(double* const out) const;

    Vector3 GetXVector() const;
    Vector3 GetYVector() const;
    Vector3 GetZVector() const;


    void FitAroundBox(Box3D box);


    bool ExpandToIncludeBox(const Box3D& b);

    double GetMaxLength() const;
    double GetMinLength() const;
    double GetShortestLength() const;
    double GetVolume(double min_length) const;

    void SetLengths(double a, double b, double c);
    void SetXLength(double a);
    void SetYLength(double a);
    void SetZLength(double a);

    Point3 GetOrigin() const;


    Point3 GetXYZCorner() const;
    bool IsBoxAligned(const Box3D& other) const;
    void SetOrigin(const Point3& p);

    Matrix3 GetOrientation() const;
    void SetOrientation(const Matrix3& orientation);
};

static_assert(sizeof(Box3D) == 336, "Box3D 布局必须与 raw 一致（336 字节）");
static_assert(offsetof(Box3D, matrix) == 8, "Box3D::matrix 必须位于 +8");
static_assert(offsetof(Box3D, origin) == 80, "Box3D::origin 必须位于 +80");
static_assert(offsetof(Box3D, length) == 104, "Box3D::length 必须位于 +104");
static_assert(offsetof(Box3D, dirty) == 128, "Box3D::dirty 必须位于 +128");
static_assert(offsetof(Box3D, corners) == 136, "Box3D::corners 必须位于 +136");
static_assert(offsetof(Box3D, cached) == 328, "Box3D::cached 必须位于 +328");

}
}








extern "C" int sub_180068630(UGS::Math::Matrix3* m);
