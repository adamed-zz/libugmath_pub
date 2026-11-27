#include <cmath>
#include <cstddef>
#include <emmintrin.h>
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

void FindCircleFromPolyline(const std::vector<Point3, UGS::Memory::SMAlloc<Point3>>& pts,
                            bool flag, bool& ok, double* const center,
                            double* const normal, double& radius);
bool NormalizeVector(const double* const v, int n, double* const out);
__declspec(noinline) double VectorMagnitude(const double* const v, int n);

inline double Minsd(double a, double b) {
    return _mm_cvtsd_f64(_mm_min_sd(_mm_set_sd(a), _mm_set_sd(b)));
}

}
}

struct EVC_arc_s {
    unsigned long long flags;
    double angle;
    double center[3];
    double radius;
    double v0[3];
    double axis[3];
};

namespace UGS {
namespace Math {

void FindArcFromPolyline(const std::vector<Point3, UGS::Memory::SMAlloc<Point3>>& pts,
                         bool& ok1, bool& ok2, EVC_arc_s& arc);

void FindArcFromPolyline(const std::vector<Point3, UGS::Memory::SMAlloc<Point3>>& pts,
                         bool& ok1, bool& ok2, EVC_arc_s& arc)
{
    ok1 = false;
    ok2 = false;
    unsigned char* raw = reinterpret_cast<unsigned char*>(&arc);
    for (int i = 0; i < 96; ++i) raw[i] = 0;

    const int n = (int)pts.size();
    if (n < 3) {
        ok2 = true;
        return;
    }
    const Point3 p0 = pts[0];
    const Point3 pn = pts[n - 1];
    const double dx = p0.x - pn.x;
    const double dz = p0.z - pn.z;
    const double dy = p0.y - pn.y;
    const double chord = std::sqrt(((dy * dy + dx * dx) + dz * dz));
    ok1 = (9.999999974752427e-07 >= chord);

    double normal[3];
    FindCircleFromPolyline(pts, ok1, ok2, arc.center, normal, arc.radius);
    if (ok2) return;

    arc.v0[0] = p0.x - arc.center[0];
    arc.v0[1] = p0.y - arc.center[1];
    arc.v0[2] = p0.z - arc.center[2];
    ok2 = NormalizeVector(arc.v0, 3, arc.v0);
    if (ok2) return;

    arc.axis[0] = arc.v0[2] * normal[1] - arc.v0[1] * normal[2];
    arc.axis[1] = arc.v0[0] * normal[2] - arc.v0[2] * normal[0];
    arc.axis[2] = arc.v0[1] * normal[0] - arc.v0[0] * normal[1];
    arc.flags = 0;

    if (ok1) {
        arc.angle = 6.283185307179586;
        return;
    }

    double vx = pn.x - arc.center[0];
    double vy = pn.y - arc.center[1];
    double vz = pn.z - arc.center[2];
    double s = ((vx * vx + 0.0) + vy * vy) + vz * vz;
    double d = 1.0 - s;
    if (d < 0.0) d = -d;
    if (!(d < 1.0e-14)) {
        const double vv[3] = {vx, vy, vz};
        const double len = VectorMagnitude(vv, 3);
        if (!(len > 1.0e-14)) {
            ok2 = true;
            return;
        }
        vx /= len;
        vy /= len;
        vz /= len;
    }
    const double dot = ((vx * arc.v0[0] + vy * arc.v0[1]) + vz * arc.v0[2]);
    double t = dot;
    if (!(-1.0 > dot)) t = Minsd(1.0, dot);
    const double angle = std::acos(t);
    const double sin2 = ((vy * arc.axis[1] + vx * arc.axis[0]) + vz * arc.axis[2]);
    arc.angle = angle;
    if (0.0 > sin2) arc.angle = 6.283185307179586 - angle;
}

}
}
