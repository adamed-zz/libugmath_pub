





























#include <cstddef>
#include <cstdint>
#include <memory>
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

struct Matrix3 {
    double m[9];
};

struct Point3 {
    double x, y, z;
};

static_assert(sizeof(Matrix3) == 72, "Matrix3 必须为 72 字节");
static_assert(sizeof(Point3) == 24, "Point3 必须为 24 字节");


enum AXIS {
    AXIS_X = 0,
    AXIS_Y = 1,
    AXIS_Z = 2
};

class Box3D {
public:




    virtual ~Box3D();

    double matrix[9];
    double origin[3];
    double length[3];
    unsigned char dirty;
    double corners[8][3];
    unsigned long long cached;

    Box3D();
    double GetMinPoint(int index) const;
    double GetMaxPoint(int index) const { return origin[index] + length[index]; }
    void SetMaxPoint(int index, double value);
    Point3 GetXYCorner() const;
    Point3 GetXZCorner() const;
    Point3 GetYZCorner() const;
    Point3 GetXYZCorner() const;
    double GetRadius() const;
    bool IsBoxAligned(const Box3D& other) const;


    void SetMinPoint(int index, double value);
    void SplitAlignedBoxAlongAxis(AXIS axis, Box3D& b1, Box3D& b2) const;
    void TransformAndAlign(double* const m);
    void WrapPoints(const std::vector<Point3, UGS::Memory::SMAlloc<Point3>>& v);

private:
    void deriveData();
    bool getIntersectStatus(const Box3D& other, double tol) const;
    void getPointStatus(const Point3& p, int& st0, int& st1, int& st2,
                        double tol) const;
    bool isInteriorPoint(const Point3& p, double* const tol) const;
    bool isPointInside(const Point3& p, double* const tol) const;
};

static_assert(sizeof(Box3D) == 0x150, "Box3D 必须为 336 字节");
static_assert(offsetof(Box3D, matrix) == 0x08);
static_assert(offsetof(Box3D, origin) == 0x50);
static_assert(offsetof(Box3D, length) == 0x68);
static_assert(offsetof(Box3D, dirty) == 0x80);
static_assert(offsetof(Box3D, corners) == 0x88);
static_assert(offsetof(Box3D, cached) == 0x148);

class Clip {
public:
    struct ClipBounds {
        double d[6];
        int flags;
        int dim;

        ClipBounds();
        ClipBounds(const float* const d, int dim, int flags);
        ClipBounds(const double* const d, int dim, int flags);
        ClipBounds& operator=(ClipBounds&& rhs);
        ClipBounds& operator=(const ClipBounds& rhs);

        bool IsValid() const;
    };

    struct CurvePoint {
        double param;
        double pt[3];
        int status;

        CurvePoint();
        CurvePoint(const float* const pt, float param, int status);
        CurvePoint(const double* const pt, double param, int status);
        CurvePoint& operator=(CurvePoint&& rhs);
        CurvePoint& operator=(const CurvePoint& rhs);
    };

    struct Clipper {

        static void ClipPoint(const ClipBounds& bounds, const double* const p,
                              int& flags_out, int& status_out);
        static void ClipLineSegment(const ClipBounds& bounds, CurvePoint& p1,
                                    CurvePoint& p2, int& f1, int& f2, int& f3,
                                    int& f4);
        static void ClipPolygon(const ClipBounds& bounds, int count,
                                const double* const pts, const int* const pt_flags,
                                int flags, bool reverse, int& count_out,
                                double* const out_pts, int* const out_flags,
                                int& flags_out, int& status_out);

    private:
        static void AllocatePolygonMemory(bool flags_valid, int count, int dim,
                                          double* const pts,
                                          int* const pt_flags,
                                          double*& out_pts, int*& out_flags);
        static int ClassifySegmentClipStatus(const ClipBounds& bounds,
                                             const double* const p1,
                                             const double* const p2,
                                             int& status_out);

        static void ClipPolygonBySinglePlane(const ClipBounds& bounds, int count,
                                             const double* const pts,
                                             const int* const pt_flags, int plane,
                                             bool reverse, int& count_out,
                                             double* const out_pts,
                                             int* const out_flags,
                                             int& flags_out, int& status_out);

    public:
        static bool IsPointVisible(const ClipBounds& bounds,
                                   const double* const p);

        static void ExactlyClipLineSegment(const ClipBounds& bounds, bool flag,
                                           CurvePoint& p1, CurvePoint& p2,
                                           double* a, double* b, double* c,
                                           double* d2, int& f1, int& f2, int& f3,
                                           int& f4);
    };
};

static_assert(sizeof(Clip::ClipBounds) == 0x38, "ClipBounds 必须为 56 字节");
static_assert(offsetof(Clip::ClipBounds, flags) == 0x30);
static_assert(offsetof(Clip::ClipBounds, dim) == 0x34);
static_assert(sizeof(Clip::CurvePoint) == 0x28, "CurvePoint 必须为 40 字节");
static_assert(offsetof(Clip::CurvePoint, pt) == 0x08);
static_assert(offsetof(Clip::CurvePoint, status) == 0x20);

}
}


bool MTX3_is_identity(const UGS::Math::Matrix3* m, double tol);




#if defined(B22_ASSERT_DLLIMPORT)
__declspec(dllimport)
#endif
void ERROR_assertion_failed(const char* file, int line, const char* fmt, ...);


namespace UGS {
namespace Math {

namespace {

inline Point3 SubPoints(const Point3& a, const Point3& b)
{
    Point3 r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    r.z = a.z - b.z;
    return r;
}


inline Point3 ComputedCorner(const Box3D& b, int row)
{
    const double l = b.length[row];
    Point3 q;
    q.x = l * b.matrix[row * 3 + 0] + b.origin[0];
    q.y = l * b.matrix[row * 3 + 1] + b.origin[1];
    q.z = l * b.matrix[row * 3 + 2] + b.origin[2];
    return q;
}

}

bool Box3D::getIntersectStatus(const Box3D& other, double tol) const
{
    const Point3 d = SubPoints(*reinterpret_cast<const Point3*>(other.origin),
                               *reinterpret_cast<const Point3*>(origin));

    const double lx = d.x * matrix[0] + d.y * matrix[1] + d.z * matrix[2];
    const double ly = d.x * matrix[3] + d.y * matrix[4] + d.z * matrix[5];
    const double lz = d.x * matrix[6] + d.y * matrix[7] + d.z * matrix[8];

    const double scale = tol * 0.01;
    const double t0 = (tol == 1.0e-10) ? 1.0e-10 : scale * length[0];
    const double t1 = (tol == 1.0e-10) ? 1.0e-10 : scale * length[1];
    const double t2 = (tol == 1.0e-10) ? 1.0e-10 : scale * length[2];

    int st0;
    int st1;
    int st2;
    if (0.0 - t0 <= lx) {
        st0 = 4;
        if (lx > t0 + length[0]) {
            st0 = 2;
        }
    } else {
        st0 = 1;
    }
    if (0.0 - t1 <= ly) {
        if (ly <= t1 + length[1]) {
            st1 = 4;
        } else {
            st1 = 2;
        }
    } else {
        st1 = 1;
    }
    if (0.0 - t2 <= lz) {
        if (lz <= t2 + length[2]) {
            st2 = 4;
        } else {
            st2 = 2;
        }
    } else {
        st2 = 1;
    }

    int acc0 = st0;
    int acc1 = st1;
    int acc2 = st2;

    Point3 p;

    if (other.dirty) {
        p = *reinterpret_cast<const Point3*>(other.corners[0]);
    } else {
        p = ComputedCorner(other, 0);
    }
    getPointStatus(p, st0, st1, st2, tol);
    acc0 |= st0;
    acc1 |= st1;
    acc2 |= st2;

    if (other.dirty) {
        p = *reinterpret_cast<const Point3*>(other.corners[1]);
    } else {
        p = ComputedCorner(other, 1);
    }
    getPointStatus(p, st0, st1, st2, tol);
    acc0 |= st0;
    acc1 |= st1;
    acc2 |= st2;

    if (other.dirty) {
        p = *reinterpret_cast<const Point3*>(other.corners[2]);
    } else {
        p = ComputedCorner(other, 2);
    }
    getPointStatus(p, st0, st1, st2, tol);
    acc0 |= st0;
    acc1 |= st1;
    acc2 |= st2;

    getPointStatus(other.GetXYCorner(), st0, st1, st2, tol);
    acc0 |= st0;
    acc1 |= st1;
    acc2 |= st2;

    getPointStatus(other.GetXZCorner(), st0, st1, st2, tol);
    acc0 |= st0;
    acc1 |= st1;
    acc2 |= st2;

    getPointStatus(other.GetYZCorner(), st0, st1, st2, tol);
    acc0 |= st0;
    acc1 |= st1;
    acc2 |= st2;

    getPointStatus(other.GetXYZCorner(), st0, st1, st2, tol);
    acc0 |= st0;
    acc1 |= st1;
    acc2 |= st2;

    const bool x_ok = ((acc0 & 3) == 3) || ((acc0 & 4) != 0);
    const bool y_ok = ((acc1 & 3) == 3) || ((acc1 & 4) != 0);
    const bool z_ok = ((acc2 & 3) == 3) || ((acc2 & 4) != 0);
    return x_ok && y_ok && z_ok;
}

}
}
