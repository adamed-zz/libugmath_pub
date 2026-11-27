


















#include <cstring>

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
struct Vector3 {
    double x;
    double y;
    double z;
};

class Box3D {
public:
    Box3D(const Matrix3& mtx, const Point3& org, const double* const len);

    void* vftable;
    double matrix[9];
    Point3 origin;
    double length[3];
    unsigned char dirty;
    unsigned char pad[7];
    double cache[8][3];
    double radiusCache;
};

static_assert(sizeof(Box3D) == 336, "Box3D 必须为 336 字节");
static_assert(sizeof(Matrix3) == 72, "Matrix3 必须为 72 字节");

}
}


__declspec(dllimport) int MTX3_init_x_y_z(const UGS::Math::Vector3* x,
                                           const UGS::Math::Vector3* y,
                                           const UGS::Math::Vector3* z,
                                           UGS::Math::Matrix3* out);
extern __declspec(dllimport) int MACH__checking_level;
__declspec(dllimport) void ERROR_assertion_failed(const char* file, int line,
                                                  const char* fmt, ...);

namespace {
void* g_box3d_vtable[2] = {nullptr, nullptr};
}

namespace UGS {
namespace Math {


static void NormalizeOrientation(double* m) {
    Vector3 x;
    Vector3 y;
    Vector3 z;
    x.x = m[0];
    x.y = m[1];
    x.z = m[2];
    y.x = m[3];
    y.y = m[4];
    y.z = m[5];
    z.x = m[6];
    z.y = m[7];
    z.z = m[8];
    if (!MTX3_init_x_y_z(&x, &y, &z, reinterpret_cast<Matrix3*>(m))) {
        if (MACH__checking_level != 0) {
            ERROR_assertion_failed(
                "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\Math_Box3D.cxx", 1351,
                "%s", "validMtx");
        }
        m[0] = 1.0;
        m[1] = 0.0;
        m[2] = 0.0;
        m[3] = 0.0;
        m[4] = 1.0;
        m[5] = 0.0;
        m[6] = 0.0;
        m[7] = 0.0;
        m[8] = 1.0;
    }
}

Box3D::Box3D(const Matrix3& mtx, const Point3& org, const double* const len) {
    vftable = g_box3d_vtable;
    std::memcpy(matrix, mtx.m, sizeof(matrix));
    origin = org;
    dirty = 0;
    for (int i = 0; i < 8; ++i) {
        cache[i][0] = 0.0;
        cache[i][1] = 0.0;
        cache[i][2] = 0.0;
    }
    radiusCache = 0.0;
    NormalizeOrientation(matrix);
    length[0] = len[0];
    length[1] = len[1];
    length[2] = len[2];
    for (int i = 0; i < 8; ++i) {
        cache[i][0] = 0.0;
        cache[i][1] = 0.0;
        cache[i][2] = 0.0;
    }
    radiusCache = 0.0;
}

}
}
