
#include <cmath>
#include <cstddef>
#include <vector>













namespace UGS {
namespace Memory {

template <class T>
class SMAlloc {
public:
    using value_type = T;
    SMAlloc() = default;
    template <class U>
    SMAlloc(const SMAlloc<U>&) {}
    T* allocate(std::size_t n) { return static_cast<T*>(::operator new(n * sizeof(T))); }
    void deallocate(T* p, std::size_t) { ::operator delete(p); }
    template <class U>
    bool operator==(const SMAlloc<U>&) const { return true; }
    template <class U>
    bool operator!=(const SMAlloc<U>&) const { return false; }
};

}
}

namespace UGS {
namespace Math {

struct Point3 {
    double x, y, z;
};

bool IsPolylineArcColinear(const std::vector<Point3, UGS::Memory::SMAlloc<Point3>>& pts,
                           bool flag);

bool IsPolylineArcColinear(const std::vector<Point3, UGS::Memory::SMAlloc<Point3>>& pts,
                           bool flag)
{
    bool result = false;
    const int n = (int)pts.size();
    int i1 = n / 2;
    int i2 = n - 1;
    if (flag) {
        i1 = n / 3;
        i2 = 2 * (n / 3);
    }
    const Point3 p0 = pts[0];
    const Point3 a = pts[i1];
    const Point3 b = pts[i2];
    const double ax = a.x - p0.x;
    const double az = a.z - p0.z;
    const double bx = b.x - p0.x;
    const double bz = b.z - p0.z;
    const double ay = a.y - p0.y;
    const double by = b.y - p0.y;
    const double c1 = bx * az - bz * ax;
    const double c2 = bz * ay - by * az;
    const double c3 = by * ax - bx * ay;
    if (std::fabs(c1 * c1 + c2 * c2 + c3 * c3) < 1.0e-12) result = true;
    return result;
}

}
}
