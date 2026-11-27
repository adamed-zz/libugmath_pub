




























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
#include <cstring>

namespace UGS {
namespace Math {

bool Box3D::SetFromCorners(const Vector3* const corners8) {
    dirty = 0;
    const Vector3& o = corners8[7];
    const Vector3& c3 = corners8[3];
    const Vector3& c5 = corners8[5];
    const Vector3& c6 = corners8[6];

    Vector3 e0;
    e0.y = c3.y - o.y;
    e0.x = c3.x - o.x;
    e0.z = c3.z - o.z;
    Vector3 e1;
    e1.y = c5.y - o.y;
    e1.x = c5.x - o.x;
    e1.z = c5.z - o.z;
    Vector3 e2;
    e2.y = c6.y - o.y;
    e2.x = c6.x - o.x;
    e2.z = c6.z - o.z;

    const double len0 = std::sqrt(e0.y * e0.y + e0.x * e0.x + e0.z * e0.z);
    const double len1 = std::sqrt(e1.y * e1.y + e1.x * e1.x + e1.z * e1.z);
    const double len2 = std::sqrt(e2.y * e2.y + e2.x * e2.x + e2.z * e2.z);
    if (std::fabs(len0) <= 1.0e-10 || std::fabs(len1) <= 1.0e-10 ||
        std::fabs(len2) <= 1.0e-10)
        return false;

    Matrix3 m;
    m.m[0] = 1.0;
    m.m[1] = 0.0;
    m.m[2] = 0.0;
    m.m[3] = 0.0;
    m.m[4] = 1.0;
    m.m[5] = 0.0;
    m.m[6] = 0.0;
    m.m[7] = 0.0;
    m.m[8] = 1.0;
    if (!MTX3_init_x_y_z(&e0, &e1, &e2, &m)) {
        if (MACH__checking_level)
            ERROR_assertion_failed(
                "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\Math_Box3D.cxx", 181,
                "%s", "validMtx");
        return false;
    }

    origin[0] = o.x;
    origin[1] = o.y;
    origin[2] = o.z;
    dirty = 0;
    length[0] = len0;
    length[1] = len1;
    length[2] = len2;
    std::memcpy(&matrix[0], m.m, sizeof(matrix));
    sub_180068630((Matrix3*)&matrix[0]);
    return true;
}

}
}
