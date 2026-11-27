



























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


__declspec(noinline) double* TransformPoint(double* dst, const double* pt,
                                            const double* mtx)
{
    const double x = pt[0];
    const double y = pt[1];
    const double z = pt[2];
    const double r0 = x * mtx[0] + y * mtx[1] + z * mtx[2] + mtx[3];
    const double r1 = x * mtx[4] + y * mtx[5] + z * mtx[6] + mtx[7];
    const double r2 = x * mtx[8] + y * mtx[9] + z * mtx[10] + mtx[11];
    double w = x * mtx[12] + y * mtx[13] + z * mtx[14] + mtx[15];
    if (w < 1.0e-19) {
        if (w < 0.0) {
            w = (w < -1.0e-19) ? w : -1.0e-19;
        } else {
            w = 1.0e-19;
        }
    }
    dst[0] = r0 / w;
    dst[1] = r1 / w;
    dst[2] = r2 / w;
    return dst;
}

const char* const kFile = "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\Math_Box3D.cxx";
const char* const kNotIdentity = "!MTX3_is_identity(&m_orientation, (1.0e-10))";

}

void Box3D::TransformAndAlign(double* const m)
{
    if (!MTX3_is_identity(reinterpret_cast<const Matrix3*>(matrix), 1.0e-10)) {
        ERROR_assertion_failed(kFile, 1364, "Never condition true: %s", kNotIdentity);
        return;
    }

    deriveData();

    double mtx[16];
    const double* const src = m;
    for (int i = 0; i < 16; ++i) {
        mtx[i] = src[i];
    }


    double t[3];
#define B22_TP(k)                                                       \
    TransformPoint(t, reinterpret_cast<const double*>(k), mtx);         \
    *reinterpret_cast<double*>(k) = t[0];                               \
    *(reinterpret_cast<double*>(k) + 1) = t[1];                         \
    *(reinterpret_cast<double*>(k) + 2) = t[2]

    B22_TP(origin);
    B22_TP(corners[0]);
    B22_TP(corners[1]);
    B22_TP(corners[2]);
    B22_TP(corners[3]);
    B22_TP(corners[4]);
    B22_TP(corners[5]);
    B22_TP(corners[6]);
#undef B22_TP

    double mn[3];
    double mx[3];
    for (int j = 0; j < 3; ++j) {
        mn[j] = origin[j];
        mx[j] = origin[j];
    }
    for (int j = 0; j < 3; ++j) {
        double lo = mn[j];
        for (int i = 0; i < 7; ++i) {
            const double v = corners[i][j];
            if (lo - 1.0e-10 > v) {
                lo = v;
            }
        }
        mn[j] = lo;
        double hi = mx[j];
        for (int i = 0; i < 7; ++i) {
            const double v = corners[i][j];
            hi = (v > hi + 1.0e-10) ? v : hi;
        }
        mx[j] = hi;
    }

    *reinterpret_cast<Point3*>(origin) = *reinterpret_cast<const Point3*>(mn);
    dirty = 0;
    length[0] = mx[0] - mn[0];
    length[1] = mx[1] - mn[1];
    length[2] = mx[2] - mn[2];
}

}
}
