

























#include <cmath>

namespace UGS {
namespace Math {

struct Matrix3 {
    double m[9];
};
struct Point3 {
    double x;
    double y;
    double z;
};
struct Point2 {
    double x;
    double y;
};

typedef void (*Point2DCallback)(const Point3&, void*, Point2&);

class Box3D {
public:
    void Get2DMinMax(Point2DCallback cb, void* ctx, double percent, Point2& min,
                     Point2& max) const;

    Point3 GetXYCorner() const;
    Point3 GetXZCorner() const;
    Point3 GetYZCorner() const;
    Point3 GetXYZCorner() const;

    void* vftable;
    Matrix3 matrix;
    Point3 origin;
    double length[3];
    unsigned char dirty;
    unsigned char pad[7];
    double cache[8][3];
    double radiusCache;
};

static_assert(sizeof(Box3D) == 336, "Box3D 必须为 336 字节");
static_assert(sizeof(Matrix3) == 72, "Matrix3 必须为 72 字节");
static_assert(sizeof(Point2) == 16, "Point2 必须为 16 字节");

}
}

namespace {

using UGS::Math::Box3D;
using UGS::Math::Point2;
using UGS::Math::Point3;


inline void MergePoint(Point2& min, Point2& max, const Point2& v) {
    min.x = (min.x < v.x) ? min.x : v.x;
    min.y = (min.y < v.y) ? min.y : v.y;
    max.x = (max.x > v.x) ? max.x : v.x;
    max.y = (max.y > v.y) ? max.y : v.y;
}


inline Point3 AxisCorner(const Box3D& b, int axis) {
    if (b.dirty) {
        Point3 p;
        p.x = b.cache[axis][0];
        p.y = b.cache[axis][1];
        p.z = b.cache[axis][2];
        return p;
    }
    Point3 p;
    p.x = b.length[axis] * b.matrix.m[axis * 3 + 0] + b.origin.x;
    p.y = b.length[axis] * b.matrix.m[axis * 3 + 1] + b.origin.y;
    p.z = b.length[axis] * b.matrix.m[axis * 3 + 2] + b.origin.z;
    return p;
}

}

namespace UGS {
namespace Math {

void Box3D::Get2DMinMax(Point2DCallback cb, void* ctx, double percent, Point2& min,
                        Point2& max) const {
    Point2 tmp;
    tmp.x = 0.0;
    tmp.y = 0.0;


    cb(origin, ctx, min);
    max = min;

    Point2 v;
    cb(AxisCorner(*this, 0), ctx, v);
    MergePoint(min, max, v);
    cb(GetXYCorner(), ctx, v);
    MergePoint(min, max, v);
    cb(AxisCorner(*this, 1), ctx, v);
    MergePoint(min, max, v);
    cb(AxisCorner(*this, 2), ctx, v);
    MergePoint(min, max, v);
    cb(GetXZCorner(), ctx, v);
    MergePoint(min, max, v);
    cb(GetYZCorner(), ctx, v);
    MergePoint(min, max, v);
    cb(GetXYZCorner(), ctx, v);
    MergePoint(min, max, v);


    const double magnitude = std::fabs(percent);
    if (!(1.0e-10 >= magnitude)) {
        const double k = percent * 0.01;
        const double dx = (max.x - min.x) * k;
        const double dy = (max.y - min.y) * k;
        min.x = min.x - dx;
        max.x = dx + max.x;
        min.y = min.y - dy;
        max.y = dy + max.y;
    }
}

}
}
