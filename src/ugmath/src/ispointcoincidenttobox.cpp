

























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

bool Box3D::IsPointCoincidentToBox(const Point3& p, double tol, bool& onCorner,
                                   bool& onEdge, bool& onFace, int& faceA,
                                   int& faceB, int& cornerIdx) const {
    bool minFlags[3];
    bool maxFlags[3];
    onCorner = false;
    onEdge = false;
    onFace = false;
    if (!IsPointInside(p, tol)) return false;

    minFlags[0] = tol >= std::fabs(p.x - origin[0]);
    maxFlags[0] = tol >= std::fabs(p.x - (origin[0] + length[0]));
    minFlags[1] = tol >= std::fabs(p.y - origin[1]);
    maxFlags[1] = tol >= std::fabs(p.y - (origin[1] + length[1]));
    minFlags[2] = tol >= std::fabs(p.z - origin[2]);
    maxFlags[2] = tol >= std::fabs(p.z - (origin[2] + length[2]));

    if (!minFlags[0] && !maxFlags[0] && !minFlags[1] && !maxFlags[1] &&
        !minFlags[2] && !maxFlags[2])
        return false;

    onCorner = IsCoincidentToCorner(minFlags, maxFlags, faceA, faceB, cornerIdx);
    if (onCorner) return true;
    onEdge = IsCoincidentToEdge(minFlags, maxFlags, faceA, faceB);
    if (onEdge) return true;

    if (minFlags[0]) {
        faceA = 0;
        onFace = true;
    } else if (maxFlags[0]) {
        faceA = 1;
        onFace = true;
    } else if (minFlags[1]) {
        faceA = 2;
        onFace = true;
    } else if (maxFlags[1]) {
        faceA = 3;
        onFace = true;
    } else if (minFlags[2]) {
        faceA = 4;
        onFace = true;
    } else if (maxFlags[2]) {
        faceA = 5;
        onFace = true;
    } else {
        onFace = false;
    }
    return onCorner || onEdge || onFace;
}

}
}
