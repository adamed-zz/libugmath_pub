

















#include <cstddef>
#include <vector>

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

}

namespace Memory {

template <class T>
class SMAlloc {
public:
    using value_type = T;
    SMAlloc() noexcept = default;
    template <class U>
    SMAlloc(const SMAlloc<U>&) noexcept {}
    T* allocate(std::size_t n) {
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }
    void deallocate(T* p, std::size_t) noexcept { ::operator delete(p); }
    template <class U>
    bool operator==(const SMAlloc<U>&) const noexcept {
        return true;
    }
    template <class U>
    bool operator!=(const SMAlloc<U>&) const noexcept {
        return false;
    }
};

}

namespace Math {

using PointVector = std::vector<Point3, UGS::Memory::SMAlloc<Point3>>;

class Box3D {
public:
    bool ExpandToIncludePoints(const PointVector& points);

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

bool Box3D::ExpandToIncludePoints(const PointVector& points) {
    bool result = false;
    for (const Point3& point : points) {
        if (result) {
            result = true;
            continue;
        }
        dirty = 0;
        bool shifted = false;
        double nx = 0.0;
        double ny = 0.0;
        double nz = 0.0;

        const double dx = point.x - origin.x;
        const double dy = point.y - origin.y;
        const double dz = point.z - origin.z;
        const double lx = (matrix.m[1] * dy + matrix.m[0] * dx) + matrix.m[2] * dz;
        const double ly = (matrix.m[3] * dx + matrix.m[4] * dy) + matrix.m[5] * dz;
        const double lz = (matrix.m[6] * dx + matrix.m[7] * dy) + matrix.m[8] * dz;

        if (!(lx < 0.0)) {
            if (lx > length[0]) {
                length[0] = lx;
                result = true;
            }
        } else {
            shifted = true;
            result = true;
            nx = lx;
            length[0] = length[0] - lx;
        }
        if (!(ly < 0.0)) {
            if (ly > length[1]) {
                length[1] = ly;
                result = true;
            }
        } else {
            shifted = true;
            result = true;
            ny = ly;
            length[1] = length[1] - ly;
        }
        if (lz < 0.0) {


            result = true;
            shifted = true;
            nz = lz;
            length[2] = length[2] - lz;
        } else if (lz > length[2]) {
            length[2] = lz;
            result = true;
        }

        if (shifted) {
            const double ox = ((matrix.m[3] * ny + matrix.m[0] * nx) +
                               matrix.m[6] * nz) + origin.x;
            const double oy = ((matrix.m[4] * ny + matrix.m[1] * nx) +
                               matrix.m[7] * nz) + origin.y;
            const double oz = ((matrix.m[5] * ny + matrix.m[2] * nx) +
                               matrix.m[8] * nz) + origin.z;
            origin.x = ox;
            origin.y = oy;
            origin.z = oz;
        }
    }
    return result;
}

}
}
