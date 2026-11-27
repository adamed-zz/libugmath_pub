












#include <cstddef>

namespace UGS {
namespace Math {

struct Point3 {
    double x;
    double y;
    double z;

    Point3() = default;
    Point3(double a, double b, double c) : x(a), y(b), z(c) {}
};

class alignas(8) Box3D {
public:
    void* vftable;
    double matrix[9];
    Point3 origin;
    double length[3];
    unsigned char dirty;
    unsigned char pad0[7];
    Point3 xCornerCache;
    Point3 yCornerCache;
    Point3 zCornerCache;
    Point3 xyCornerCache;
    Point3 xzCornerCache;
    Point3 yzCornerCache;
    Point3 xyzCornerCache;
    unsigned char pad1[24];
    unsigned long long cached;



    Point3 GetXCorner() const {
        Point3 r;
        if (dirty) {
            r = xCornerCache;
        } else {
            r = Point3(length[0] * matrix[0] + origin.x,
                       length[0] * matrix[1] + origin.y,
                       length[0] * matrix[2] + origin.z);
        }
        return r;
    }
    Point3 GetYCorner() const {
        Point3 r;
        if (dirty) {
            r = yCornerCache;
        } else {
            r = Point3(length[1] * matrix[3] + origin.x,
                       length[1] * matrix[4] + origin.y,
                       length[1] * matrix[5] + origin.z);
        }
        return r;
    }
    Point3 GetZCorner() const {
        Point3 r;
        if (dirty) {
            r = zCornerCache;
        } else {
            r = Point3(length[2] * matrix[6] + origin.x,
                       length[2] * matrix[7] + origin.y,
                       length[2] * matrix[8] + origin.z);
        }
        return r;
    }


    bool ExpandToIncludePoint(const Point3& p);
    Point3 GetXYZCorner() const;
    Point3 GetXYCorner() const;
    Point3 GetXZCorner() const;
    Point3 GetYZCorner() const;
    bool IsBoxAligned(const Box3D& b) const;

    bool ExpandToIncludeBox(const Box3D& b);
};

static_assert(sizeof(Point3) == 24, "Point3 必须为 24 字节");
static_assert(sizeof(Box3D) == 336, "Box3D 必须为 336 字节");
static_assert(offsetof(Box3D, origin) == 80, "origin 位于 +80");
static_assert(offsetof(Box3D, length) == 104, "length 位于 +104");
static_assert(offsetof(Box3D, dirty) == 128, "dirty 位于 +128");
static_assert(offsetof(Box3D, xCornerCache) == 136, "xCornerCache 位于 +136");
static_assert(offsetof(Box3D, yCornerCache) == 160, "yCornerCache 位于 +160");
static_assert(offsetof(Box3D, zCornerCache) == 184, "zCornerCache 位于 +184");
static_assert(offsetof(Box3D, xyCornerCache) == 208, "xyCornerCache 位于 +208");
static_assert(offsetof(Box3D, xzCornerCache) == 232, "xzCornerCache 位于 +232");
static_assert(offsetof(Box3D, yzCornerCache) == 256, "yzCornerCache 位于 +256");
static_assert(offsetof(Box3D, xyzCornerCache) == 280, "xyzCornerCache 位于 +280");
static_assert(offsetof(Box3D, cached) == 328, "cached 位于 +328");

bool Box3D::ExpandToIncludeBox(const Box3D& b) {
    dirty = 0;
    int v5 = 0;

    {
        Point3 o = b.origin;
        if (ExpandToIncludePoint(o))
            v5 = 1;
    }

    if (ExpandToIncludePoint(b.GetXYZCorner()))
        ++v5;

    if (!IsBoxAligned(b)) {
        Point3 p;
        p = b.GetXCorner();
        if (ExpandToIncludePoint(p))
            ++v5;
        p = b.GetYCorner();
        if (ExpandToIncludePoint(p))
            ++v5;
        p = b.GetZCorner();
        if (ExpandToIncludePoint(p))
            ++v5;
        if (ExpandToIncludePoint(b.GetXYCorner()))
            ++v5;
        if (ExpandToIncludePoint(b.GetXZCorner()))
            ++v5;
        if (ExpandToIncludePoint(b.GetYZCorner()))
            ++v5;
    }

    return v5 != 0;
}

}
}
