






















#pragma once

#include <cstddef>
#include <cstdint>

namespace UGS {
namespace Memory {


class CppMemory {
public:
    static void* allocate(std::size_t size);
    static void free(void* p);
};

}
}

namespace UGS {
namespace Math {

struct Point3 {
    double x, y, z;
};
static_assert(sizeof(Point3) == 24, "Point3 必须为 24 字节");

namespace Clip {

struct ClipBounds {
    double d[6];
    int flags;
    int dim;

    bool IsValid() const;
    bool IsClippingWithMultipleBounds() const;
};
static_assert(sizeof(ClipBounds) == 0x38, "ClipBounds 必须为 56 字节");
static_assert(offsetof(ClipBounds, flags) == 0x30);
static_assert(offsetof(ClipBounds, dim) == 0x34);

struct CurvePoint {
    double param;
    double pt[3];
    int status;

    CurvePoint();
    CurvePoint(const double* const pt, double param, int status);
};
static_assert(sizeof(CurvePoint) == 0x28, "CurvePoint 必须为 40 字节");
static_assert(offsetof(CurvePoint, pt) == 0x08);
static_assert(offsetof(CurvePoint, status) == 0x20);





inline CurvePoint::CurvePoint(const double* const p, double par, int st)
    : param(par), pt{0.0, 0.0, 0.0}, status(st) {
    if (p) {
        pt[0] = p[0];
        pt[1] = p[1];
        pt[2] = p[2];
    }
}

class Clipper {
public:

    static bool IsBoxClipped(const double* const box, const ClipBounds& bounds,
                             int& status);
    static bool IsPointVisible(const ClipBounds& bounds,
                               const double* const p);
    static void IsPolygonClipped(int count, const double* pts,
                                 const ClipBounds& bounds, bool& clipped,
                                 int& status);


    static void ClipPolygon(const ClipBounds& bounds, int count,
                            const double* const pts, const int* const pt_flags,
                            int flags, bool reverse, int& count_out,
                            double* const out_pts, int* const out_flags,
                            int& flags_out, int& status_out);

private:

    friend struct B23Access;
    static void ClipPolygonBySinglePlane(const ClipBounds& bounds, int count,
                                         const double* const pts,
                                         const int* const pt_flags, int plane,
                                         bool reverse, int& count_out,
                                         double* const out_pts,
                                         int* const out_flags, int& flags_out,
                                         int& status_out);
    static void ClipPolygonEdgeBySinglePlane(const ClipBounds& bounds,
                                             const double* const p1,
                                             const double* const p2,
                                             double* const out,
                                             int& status);

    static bool ComputeT(int plane, double den, double num, double& tmin,
                         double& num_min, double& den_min, double& tmax,
                         double& num_max, double& den_max, int& plane_min,
                         int& plane_max);
    static void ExactlyClipLineSegment(const ClipBounds& bounds, bool reverse,
                                       CurvePoint& p1, CurvePoint& p2,
                                       double* a, double* b, double* c,
                                       double* d2, int& f1, int& f2, int& f3,
                                       int& f4);
    static void FreePolygonMemory(const double* const pts,
                                  const int* const pt_flags,
                                  double*& out_pts, int*& out_flags);
};

}
}
}


namespace UGS {
namespace System {
namespace Loader {
class Module;
}

namespace L10N {
typedef void (*LocalizeCallback)(const char*, const char*, const char*, const char*,
                                 const char*);
const char* Localize(const char* file, const char* key, const char* msg,
                     const char* lang, LocalizeCallback cb);
}
}
}

namespace UGS {
namespace System {
namespace Loader {
class Module;
}
}
}

UGS::System::Loader::Module* LDR_load_image(const char* name, int flags);
void (*LDR_find_symbol(UGS::System::Loader::Module* module, const char* name))();
void ldr_unload_module(const char* name);

typedef const char* (*ERROR_decoder_fn)(int, void*);
void ERROR_register_decoder_fn(int base, int count, ERROR_decoder_fn fn, void* ctx);
const char* ERROR_decode_in_table(int code, void* ctx);


void GBSPLINE_loadModule();
bool GBSPLINE_moduleLoaded();
void GBSPLINE_unloadModule();


void MATH_errors_init();



namespace UGS {
namespace Math {
namespace Clip {

namespace {

int Abs32Neg(int v) {

    unsigned u = (unsigned)v;
    unsigned m = (u & 0x80000000u) ? (0u - u) : u;
    return (int)(0u - m);
}

}

void Clipper::ClipPolygonBySinglePlane(const ClipBounds& bounds, int count,
                                       const double* const pts,
                                       const int* const pt_flags, int plane,
                                       bool reverse, int& count_out,
                                       double* const out_pts,
                                       int* const out_flags, int& flags_out,
                                       int& status_out) {
    count_out = 0;
    status_out = 0;
    if (count < 2 || !pts) {
        status_out = 1;
        return;
    }
    if (!bounds.IsValid() || bounds.IsClippingWithMultipleBounds()) {
        status_out = 2;
        return;
    }
    const bool has_flags = (pt_flags != nullptr && out_flags != nullptr);
    const int dim = bounds.dim;
    const int last = count - 1;

    for (int i = 0; i < count; ++i) {
        double cz = 0.0;
        const double cx = pts[dim * i];
        const double cy = pts[dim * i + 1];
        if (dim != 2) cz = pts[dim * i + 2];
        const int next = (i == last) ? 0 : dim * (i + 1);
        double nz = 0.0;
        const double nx = pts[next];
        const double ny = pts[next + 1];
        if (dim != 2) nz = pts[next + 2];

        status_out = 0;
        if (!bounds.IsValid()) {
            status_out = 2;
            count_out = 0;
            return;
        }
        if (bounds.IsClippingWithMultipleBounds()) {
            status_out = 2;
            count_out = 0;
            return;
        }

        const double cpt[3] = {cx, cy, cz};
        const double npt[3] = {nx, ny, nz};
        const bool cur_visible = IsPointVisible(bounds, cpt);
        const bool next_visible = IsPointVisible(bounds, npt);

        if (cur_visible) {
            if (next_visible) {
                if (has_flags) out_flags[count_out] = pt_flags[i];
                if (dim == 2) {
                    out_pts[2 * count_out] = cx;
                    out_pts[2 * count_out + 1] = cy;
                } else {
                    out_pts[dim * count_out] = cx;
                    out_pts[dim * count_out + 1] = cy;
                    out_pts[dim * count_out + 2] = cz;
                }
                ++count_out;
                continue;
            }

            flags_out |= bounds.flags;
            status_out = 0;
            if (!bounds.IsValid() || bounds.IsClippingWithMultipleBounds()) {
                status_out = 2;
                count_out = 0;
                return;
            }
            CurvePoint a;
            a.param = 0.0;
            a.pt[0] = cx;
            a.pt[1] = cy;
            a.pt[2] = (dim == 2) ? 0.0 : cz;
            a.status = dim;
            CurvePoint b;
            b.param = 1.0;
            b.pt[0] = nx;
            b.pt[1] = ny;
            b.pt[2] = (dim == 2) ? 0.0 : nz;
            b.status = dim;
            int f1 = 0, f2 = 0, f3 = 0;
            ExactlyClipLineSegment(bounds, false, a, b, nullptr, nullptr,
                                   nullptr, nullptr, f1, f2, f3, status_out);
            double ix, iy, iz = 0.0;
            if ((f1 & 2) != 0) {
                ix = a.pt[0];
                iy = a.pt[1];
                if (dim != 2) iz = a.pt[2];
            } else {
                ix = b.pt[0];
                iy = b.pt[1];
                if (dim != 2) iz = b.pt[2];
            }
            if (status_out != 0) {
                count_out = 0;
                return;
            }
            if (dim == 2) {
                out_pts[2 * count_out] = cx;
                out_pts[2 * count_out + 1] = cy;
            } else {
                out_pts[dim * count_out] = cx;
                out_pts[dim * count_out + 1] = cy;
                out_pts[dim * count_out + 2] = cz;
            }
            if (has_flags) out_flags[count_out] = pt_flags[i];
            ++count_out;
            if (dim == 2) {
                out_pts[2 * count_out] = ix;
                out_pts[2 * count_out + 1] = iy;
            } else {
                out_pts[dim * count_out] = ix;
                out_pts[dim * count_out + 1] = iy;
                out_pts[dim * count_out + 2] = iz;
            }
            if (has_flags) out_flags[count_out] = plane;
            ++count_out;
        } else if (next_visible) {

            flags_out |= bounds.flags;
            status_out = 0;
            if (!bounds.IsValid() || bounds.IsClippingWithMultipleBounds()) {
                status_out = 2;
                count_out = 0;
                return;
            }
            CurvePoint a;
            a.param = 0.0;
            a.pt[0] = cx;
            a.pt[1] = cy;
            a.pt[2] = (dim == 2) ? 0.0 : cz;
            a.status = dim;
            CurvePoint b;
            b.param = 1.0;
            b.pt[0] = nx;
            b.pt[1] = ny;
            b.pt[2] = (dim == 2) ? 0.0 : nz;
            b.status = dim;
            int f1 = 0, f2 = 0, f3 = 0;
            ExactlyClipLineSegment(bounds, false, a, b, nullptr, nullptr,
                                   nullptr, nullptr, f1, f2, f3, status_out);
            double ix, iy, iz = 0.0;
            if ((f1 & 2) != 0) {
                ix = a.pt[0];
                iy = a.pt[1];
                if (dim != 2) iz = a.pt[2];
            } else {
                ix = b.pt[0];
                iy = b.pt[1];
                if (dim != 2) iz = b.pt[2];
            }
            if (status_out != 0) {
                count_out = 0;
                return;
            }
            if (has_flags) {
                int fi = pt_flags[i];
                if (reverse) fi = Abs32Neg(fi);
                out_flags[count_out] = fi;
            }
            if (dim == 2) {
                out_pts[2 * count_out] = ix;
                out_pts[2 * count_out + 1] = iy;
            } else {
                out_pts[dim * count_out] = ix;
                out_pts[dim * count_out + 1] = iy;
                out_pts[dim * count_out + 2] = iz;
            }
            ++count_out;
        } else {
            flags_out |= bounds.flags;
        }
    }
}

}
}
}
