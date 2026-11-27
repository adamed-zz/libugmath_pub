
#include <cstddef>
#include <new>
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

namespace Math {

struct Point3 {
    double x, y, z;
};

void FindCircleFrom3Points(const double* const pa, const double* const pb,
                           const double* const pc, bool& ok, double* const center,
                           double* const normal, double& radius);

void FindCircleFromPolyline(const std::vector<Point3, UGS::Memory::SMAlloc<Point3>>& pts,
                            bool flag, bool& ok, double* const center,
                            double* const normal, double& radius);

void FindCircleFromPolyline(const std::vector<Point3, UGS::Memory::SMAlloc<Point3>>& pts,
                            bool flag, bool& ok, double* const center,
                            double* const normal, double& radius)
{
    ok = false;
    center[2] = 0.0;
    center[1] = 0.0;
    center[0] = 0.0;
    normal[1] = 0.0;
    normal[0] = 0.0;
    normal[2] = 1.0;
    radius = 1.0;

    const int n = (int)pts.size();
    int i1 = n / 2;
    int i2 = n - 1;
    if (flag) {
        i1 = n / 3;
        i2 = 2 * (n / 3);
    }

    const Point3 a = pts[0];
    const Point3 b = pts[i1];
    const Point3 c = pts[i2];
    FindCircleFrom3Points(&a.x, &b.x, &c.x, ok, center, normal, radius);
}

}
}
