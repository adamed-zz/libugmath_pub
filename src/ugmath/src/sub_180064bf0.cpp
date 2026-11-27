

















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

class Box3D {
public:
    double GetMaxPoint(int axis) const;
    double GetMinPoint(int axis) const;

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

}
}


__declspec(dllimport) bool MTX3_is_identity(const UGS::Math::Matrix3* mtx,
                                            double tolerance);
__declspec(dllimport) void ERROR_assertion_failed(const char* file, int line,
                                                  const char* fmt, ...);
__declspec(dllimport) void ERROR_raise(const char* file, int line, int code);

namespace UGS {
namespace Math {

double Box3D::GetMaxPoint(int axis) const {
    if (!MTX3_is_identity(&matrix, 1.0e-10)) {
        ERROR_assertion_failed(
            "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\Math_Box3D.cxx", 1458,
            "Never condition true: %s",
            "!MTX3_is_identity(&m_orientation, (1.0e-10))");
        return 0.0;
    }
    if (axis == 0) {
        return GetMinPoint(0) + length[0];
    }
    if (axis == 1) {
        return GetMinPoint(1) + length[1];
    }
    if (axis == 2) {
        return GetMinPoint(2) + length[2];
    }
    ERROR_raise("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\Math_Box3D.cxx", 1466,
                4360001);
    __debugbreak();
}

}
}
