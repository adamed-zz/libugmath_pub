















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

class Box3D {
public:
    bool DoesBoxSurround(Box3D& other);
    bool IsBoxInside(Box3D& other, double tolerance);

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

namespace {
inline double Span(double v) { return std::fmax(v, 1.0e-10); }
inline double Volume(const Box3D& b) {

    return Span(b.length[1]) * Span(b.length[0]) * Span(b.length[2]);
}
}

bool Box3D::DoesBoxSurround(Box3D& other) {
    if (Volume(other) > Volume(*this) + 1.0e-10) {
        return other.IsBoxInside(*this, 1.0e-10);
    }
    return false;
}

}
}
