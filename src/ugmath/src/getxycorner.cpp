





















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






namespace UGS {
namespace Math {

Point3 Box3D::GetXYCorner() const {
    Point3 p;
    if (dirty) {
        p = *(const Point3*)&corners[3][0];
        return p;
    }
    const double lx = length[0];
    const double ly = length[1];
    const double o0 = origin[0];
    const double o1 = origin[1];
    const double o2 = origin[2];
    p.x = ((ly * matrix[3] + o0) - o0) + (lx * matrix[0] + o0);
    p.y = ((ly * matrix[4] + o1) - o1) + (lx * matrix[1] + o1);
    p.z = ((ly * matrix[5] + o2) - o2) + (lx * matrix[2] + o2);
    return p;
}

}
}
