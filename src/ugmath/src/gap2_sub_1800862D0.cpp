







#include <cstddef>
#include <cstdint>
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

namespace PointCloudUtils {

std::uint64_t FindClosestPoint(const Point3& p,
                               const std::vector<Point3, UGS::Memory::SMAlloc<Point3>>& points);

std::uint64_t FindClosestPoint(const Point3& p,
                               const std::vector<Point3, UGS::Memory::SMAlloc<Point3>>& points) {
    const double* const begin = reinterpret_cast<const double*>(points.data());
    const double* const end = begin + 3 * points.size();
    const double* best = begin;
    if (begin != end) {
        for (const double* i = begin + 3; i != end; i += 3) {
            const double dxBest = p.x - best[0];
            const double dyBest = p.y - best[1];
            const double dzBest = p.z - best[2];
            const double dxCand = p.x - i[0];
            const double dyCand = p.y - i[1];
            const double dzCand = p.z - i[2];

            if (dyBest * dyBest + dxBest * dxBest + dzBest * dzBest >
                dxCand * dxCand + dyCand * dyCand + dzCand * dzCand)
                best = i;
        }
    }
    return static_cast<std::uint64_t>(
        (reinterpret_cast<const char*>(best) - reinterpret_cast<const char*>(begin)) / 24);
}

}
}
}
