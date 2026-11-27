



























#include <cstddef>

namespace UGS {
namespace Math {

struct Point3 {
    double x, y, z;
    Point3() = default;
    Point3(double a, double b, double c) : x(a), y(b), z(c) {}
};

struct Vector3 {
    double x, y, z;
};

struct Matrix3 {
    double m[9];
};

}
}


struct PK_BOX_s {
    double xmin, ymin, zmin, xmax, ymax, zmax;
};

namespace UGS {
namespace Math {

class alignas(8) Box3D {
public:
    void* vftable;
    double matrix[9];
    double origin[3];
    double length[3];
    unsigned char dirty;
    unsigned char pad[7];
    double corners[8][3];
    unsigned long long cached;

    double GetMinPoint(int index) const;
    double GetRadius() const;

    Point3 GetXCorner() const;
    Point3 GetXYCorner() const;
    Point3 GetXYZCorner() const;
    Point3 GetXZCorner() const;
    Point3 GetYCorner() const;
    Point3 GetYZCorner() const;
    Point3 GetZCorner() const;

    bool IsBoxAligned(const Box3D& other) const;
    bool IsBoxInside(Box3D& other, double tol);
    bool IsBoxInsidePercent(Box3D& other, double tol);

    bool IsInteriorPoint(const Point3& p, double tol) const;
    bool IsPointCoincidentToBox(const Point3& p, double tol, bool& a4, bool& a5,
                                bool& a6, int& a7, int& a8, int& a9) const;
    bool IsPointInside(const Point3& p, double tol) const;
    bool IsPointInside(const Point3& p, double tol, bool& on_boundary) const;
    bool IsPointInsidePercent(const Point3& p, double tol) const;
    bool IsPointInsidePercent(const Point3& p, double tol, bool& on_boundary) const;

    bool SetFromCorners(const Vector3* const corners8);
    void SetFromParasolidBoundingBox(const PK_BOX_s& box);
    void SetMaxPoint(int index, double value);

private:
    void deriveData();
    static bool IsCoincidentToCorner(bool* const minFlags, bool* const maxFlags,
                                     int& faceA, int& faceB, int& corner);
    static bool IsCoincidentToEdge(bool* const minFlags, bool* const maxFlags,
                                   int& faceA, int& faceB);
    static bool IsCoincidentToFace(bool* const minFlags, bool* const maxFlags,
                                   int& faceA);
};

static_assert(sizeof(Box3D) == 336, "Box3D 必须为 336 字节");
static_assert(offsetof(Box3D, matrix) == 8, "matrix @ +8");
static_assert(offsetof(Box3D, origin) == 80, "origin @ +80");
static_assert(offsetof(Box3D, length) == 104, "length @ +104");
static_assert(offsetof(Box3D, dirty) == 128, "dirty @ +128");
static_assert(offsetof(Box3D, corners) == 136, "corners @ +136");
static_assert(offsetof(Box3D, cached) == 328, "cached @ +328");

}
}


__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_assertion_failed(const char* file, int line,
                                                  const char* fmt, ...);
__declspec(dllimport) void ERROR_raise(const char* file, int line, int code);
__declspec(dllimport) void ERROR_raise(const char* file, int line, int code,
                                       const char* fmt, ...);


bool MTX3_is_identity(const UGS::Math::Matrix3* m, double tol);
bool VEC3_is_parallel(const UGS::Math::Vector3* u, const UGS::Math::Vector3* v,
                      double tolerance);
int MTX3_init_x_y_z(const UGS::Math::Vector3* x, const UGS::Math::Vector3* y,
                    const UGS::Math::Vector3* z, UGS::Math::Matrix3* out);
extern "C" int sub_180068630(UGS::Math::Matrix3* m);






#include <cmath>

namespace UGS {
namespace Math {

static Point3 B21_CenterOf(Box3D& b) {
    Point3 c;
    if (b.dirty) {
        c.x = b.corners[7][0];
        c.y = b.corners[7][1];
        c.z = b.corners[7][2];
    } else {
        const Point3 xyz = b.GetXYZCorner();
        c.x = (xyz.x + b.origin[0]) * 0.5;
        c.y = (xyz.y + b.origin[1]) * 0.5;
        c.z = (xyz.z + b.origin[2]) * 0.5;
    }
    return c;
}

static Point3 B21_AxisCorner(Box3D& b, int k) {
    Point3 p;
    if (b.dirty) {
        p.x = b.corners[k][0];
        p.y = b.corners[k][1];
        p.z = b.corners[k][2];
    } else {
        const double l = b.length[k];
        p.x = l * b.matrix[3 * k + 0] + b.origin[0];
        p.y = l * b.matrix[3 * k + 1] + b.origin[1];
        p.z = l * b.matrix[3 * k + 2] + b.origin[2];
    }
    return p;
}

bool Box3D::IsBoxInside(Box3D& other, double tol) {
    deriveData();
    other.deriveData();

    const Point3 oc = B21_CenterOf(other);
    const Point3 tc = B21_CenterOf(*this);
    const double dy = tc.y - oc.y;
    const double dx = tc.x - oc.x;
    const double dz = tc.z - oc.z;
    const double d2 = dy * dy + dx * dx + dz * dz;
    const double dist = std::sqrt(d2);
    const double radiusSum = other.GetRadius() + GetRadius() + tol;
    if (dist > radiusSum) return false;

    const Point3 origin(other.origin[0], other.origin[1], other.origin[2]);
    if (!IsPointInside(origin, tol)) return false;

    const Point3 xyz = other.GetXYZCorner();
    if (!IsPointInside(xyz, tol)) return false;

    if (IsBoxAligned(other)) return true;

    if (!IsPointInside(B21_AxisCorner(other, 0), tol)) return false;
    if (!IsPointInside(B21_AxisCorner(other, 1), tol)) return false;
    if (!IsPointInside(B21_AxisCorner(other, 2), tol)) return false;

    const Point3 xy = other.GetXYCorner();
    if (!IsPointInside(xy, tol)) return false;
    const Point3 xz = other.GetXZCorner();
    if (!IsPointInside(xz, tol)) return false;
    const Point3 yz = other.GetYZCorner();
    if (!IsPointInside(yz, tol)) return false;
    return true;
}

}
}
