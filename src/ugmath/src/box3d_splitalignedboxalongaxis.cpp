



































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

const char* const kFile =
    "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\Math_Box3D.cxx";
const char* const kNotIdentity = "!MTX3_is_identity(&m_orientation, (1.0e-10))";

inline bool IsIdentity(const Box3D& b)
{
    return MTX3_is_identity(reinterpret_cast<const Matrix3*>(b.matrix), 1.0e-10);
}


__forceinline double GetMaxPointInline(const Box3D& b, int index)
{
    if (!IsIdentity(b)) {
        ERROR_assertion_failed(kFile, 1458, "Never condition true: %s",
                               kNotIdentity);
        return 0.0;
    }
    return b.GetMinPoint(index) + b.length[index];
}


__forceinline void SetMaxPointInline(Box3D& b, int index, double value)
{
    if (!IsIdentity(b)) {
        ERROR_assertion_failed(kFile, 1479, "Never condition true: %s",
                               kNotIdentity);
        return;
    }
    switch (index) {
    case 0: b.length[0] = value - b.GetMinPoint(0); break;
    case 1: b.length[1] = value - b.GetMinPoint(1); break;
    case 2: b.length[2] = value - b.GetMinPoint(2); break;
    default: break;
    }
    b.dirty = 0;
}

}



__declspec(noinline) void Box3D::SetMinPoint(int index, double value)
{
    if (!MTX3_is_identity(reinterpret_cast<const Matrix3*>(matrix), 1.0e-10)) {
        ERROR_assertion_failed(kFile, 1441, "Never condition true: %s",
                               kNotIdentity);
        return;
    }
    Point3 tmp;
    tmp = *reinterpret_cast<const Point3*>(origin);
    dirty = 0;
    reinterpret_cast<double*>(&tmp)[index] = value;
    *reinterpret_cast<Point3*>(origin) = tmp;
}

void Box3D::SplitAlignedBoxAlongAxis(AXIS axis, Box3D& alignedBox,
                                     Box3D& otherBox) const
{
    Box3D aligned;
    if (!IsBoxAligned(aligned)) {
        ERROR_assertion_failed(kFile, 1495, "Never condition true: %s",
                               "!this->IsBoxAligned(alignedBox)");
        return;
    }

    switch (axis) {
    case AXIS_X:
        alignedBox.SetMinPoint(0, GetMinPoint(0));
        alignedBox.SetMinPoint(1, GetMinPoint(1));
        alignedBox.SetMinPoint(2, GetMinPoint(2));
        SetMaxPointInline(alignedBox, 0, GetMinPoint(0) + length[0] * 0.5);
        SetMaxPointInline(alignedBox, 1, GetMaxPointInline(*this, 1));
        SetMaxPointInline(alignedBox, 2, GetMaxPointInline(*this, 2));
        otherBox.SetMinPoint(0, GetMinPoint(0) + length[0] * 0.5);
        otherBox.SetMinPoint(1, GetMinPoint(1));
        otherBox.SetMinPoint(2, GetMinPoint(2));
        break;
    case AXIS_Y:
        alignedBox.SetMinPoint(0, GetMinPoint(0));
        alignedBox.SetMinPoint(1, GetMinPoint(1));
        alignedBox.SetMinPoint(2, GetMinPoint(2));
        SetMaxPointInline(alignedBox, 0, GetMaxPointInline(*this, 0));
        SetMaxPointInline(alignedBox, 1, GetMinPoint(1) + length[1] * 0.5);
        SetMaxPointInline(alignedBox, 2, GetMaxPointInline(*this, 2));
        otherBox.SetMinPoint(0, GetMinPoint(0));
        otherBox.SetMinPoint(1, GetMinPoint(1) + length[1] * 0.5);
        otherBox.SetMinPoint(2, GetMinPoint(2));
        break;
    case AXIS_Z:
        alignedBox.SetMinPoint(0, GetMinPoint(0));
        alignedBox.SetMinPoint(1, GetMinPoint(1));
        alignedBox.SetMinPoint(2, GetMinPoint(2));
        SetMaxPointInline(alignedBox, 0, GetMaxPointInline(*this, 0));
        SetMaxPointInline(alignedBox, 1, GetMaxPointInline(*this, 1));
        SetMaxPointInline(alignedBox, 2, GetMinPoint(2) + length[2] * 0.5);
        otherBox.SetMinPoint(0, GetMinPoint(0));
        otherBox.SetMinPoint(1, GetMinPoint(1));
        otherBox.SetMinPoint(2, GetMinPoint(2) + length[2] * 0.5);
        break;
    default:
        return;
    }

    SetMaxPointInline(otherBox, 0, GetMaxPointInline(*this, 0));
    SetMaxPointInline(otherBox, 1, GetMaxPointInline(*this, 1));
    SetMaxPointInline(otherBox, 2, GetMaxPointInline(*this, 2));
}

}
}
