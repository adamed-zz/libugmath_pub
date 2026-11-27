






#include <cstddef>

namespace UGS {
namespace Math {

struct Point3 { double x, y, z; };
struct Vector3 { double x, y, z; };
struct Matrix3 { double m[9]; };
struct Triple { double v[3]; };

class alignas(8) Box3D {
public:
    virtual ~Box3D();

    Matrix3 matrix;
    Point3 origin;
    Vector3 length;
    unsigned char dirty;
    Triple corners[8];
    unsigned long long cached;

    Box3D();
    Box3D(const Box3D& other);
    Box3D& operator=(const Box3D& other);
};

static_assert(sizeof(Box3D) == 0x150, "Box3D 必须为 336 字节");
static_assert(offsetof(Box3D, matrix) == 0x08);
static_assert(offsetof(Box3D, origin) == 0x50);
static_assert(offsetof(Box3D, length) == 0x68);
static_assert(offsetof(Box3D, dirty) == 0x80);
static_assert(offsetof(Box3D, corners) == 0x88);
static_assert(offsetof(Box3D, cached) == 0x148);

}
}
namespace UGS {
namespace Math {

Box3D& Box3D::operator=(const Box3D& o)
{
    matrix = o.matrix;
    origin = o.origin;
    length.x = o.length.x;
    length.y = o.length.y;
    length.z = o.length.z;
    dirty = o.dirty;
    for (int i = 0; i < 8; ++i)
        corners[i] = o.corners[i];
    cached = o.cached;
    return *this;
}

}
}
