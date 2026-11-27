







#include <cstddef>
#include <cstdint>
#include <cstring>
#include <stdexcept>










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



inline CurvePoint::CurvePoint() : param(0.0), pt{0.0, 0.0, 0.0}, status(0) {}
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



namespace {
typedef UGS::Memory::CppMemory Mem;

inline std::size_t Grow(std::size_t cap, std::size_t need, std::size_t maxv) {
    if (cap > maxv - (cap >> 1)) return maxv;
    std::size_t nc = cap + (cap >> 1);
    return nc < need ? need : nc;
}
}








struct V4 { unsigned int* b; unsigned int* e; unsigned int* c; };

extern "C" unsigned long long sub_18006B480(void* vecp, unsigned int* pos,
                                            const unsigned int* first,
                                            const unsigned int* last) {
    V4* const v = (V4*)vecp;
    const std::size_t n = (std::size_t)(last - first);
    const std::size_t tail = (std::size_t)(v->c - v->e);
    if (n == 0) return (unsigned long long)tail;
    const std::size_t kMax = 0x3FFFFFFFFFFFFFFFull;
    if (n <= tail) {
        const std::size_t after = (std::size_t)(v->e - pos);
        if (n >= after) {
            unsigned int* d = pos + n;
            for (unsigned int* s = pos; s != v->e; ++s) *d++ = *s;
            v->e = d;
            unsigned int* w = pos;
            unsigned int lastv = 0;
            for (const unsigned int* s = first; s != last; ++s) {
                lastv = *s;
                *w++ = lastv;
            }
            return (unsigned long long)lastv;
        }
        const std::size_t lenB = (std::size_t)((v->e - n) - pos) * 4;
        unsigned int* s0 = v->e - n;
        unsigned int* d = v->e;
        while (s0 != v->e) *d++ = *s0++;
        v->e = d;
        memmove(pos + n, pos, lenB);
        unsigned int* w = pos;
        unsigned int lastv = 0;
        for (const unsigned int* s = first; s != last; ++s) {
            lastv = *s;
            *w++ = lastv;
        }
        return (unsigned long long)lastv;
    }
    const std::size_t size = (std::size_t)(v->e - v->b);
    if (n > kMax - size) std::_Xlength_error("vector too long");
    const std::size_t newsize = size + n;
    const std::size_t cap = (std::size_t)(v->c - v->b);
    const std::size_t nc = Grow(cap, newsize, kMax);
    unsigned int* const buf = nc ? (unsigned int*)Mem::allocate(4 * nc) : nullptr;
    const std::size_t idx = (std::size_t)(pos - v->b);
    {
        unsigned int* d = buf + idx;
        for (const unsigned int* s = first; s != last; ++s) *d++ = *s;
    }
    if (n == 1 && pos == v->e) {
        unsigned int* d = buf;
        for (unsigned int* s = v->b; s != v->e; ++s) *d++ = *s;
    } else {
        unsigned int* d = buf;
        for (unsigned int* s = v->b; s != pos; ++s) *d++ = *s;
        if (pos != v->e) {
            unsigned int* d2 = buf + idx + n;
            for (unsigned int* s = pos; s != v->e; ++s) *d2++ = *s;
        }
    }
    if (v->b) Mem::free(v->b);
    v->b = buf;
    v->e = buf + newsize;
    v->c = buf + nc;
    return (unsigned long long)(uintptr_t)v->c;
}
