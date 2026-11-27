







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





struct E24 { std::uint64_t beg, end, cap; };

static void CopyElem(E24* dst, const E24* src) {
    dst->beg = dst->end = dst->cap = 0;
    if (src->beg != src->end) {
        const std::size_t n = (std::size_t)(src->end - src->beg) >> 2;
        std::uint64_t* p = n ? (std::uint64_t*)Mem::allocate(4 * n) : nullptr;
        if (n) memcpy(p, (const void*)src->beg, 4 * n);
        dst->beg = (std::uint64_t)p;
        dst->end = (std::uint64_t)((unsigned char*)p + 4 * n);
        dst->cap = dst->end;
    }
}

static void MoveRange(E24* dst, E24* first, E24* last) {
    while (first != last) {
        dst->beg = first->beg;
        dst->end = first->end;
        dst->cap = first->cap;
        first->beg = 0;
        first->end = 0;
        first->cap = 0;
        ++dst;
        ++first;
    }
}

static void DestroyFree(unsigned char* buf, std::size_t nelem) {
    if (!buf) return;
    E24* p = (E24*)buf;
    for (std::size_t i = 0; i < nelem; ++i) {
        if (p[i].beg) {
            Mem::free((void*)p[i].beg);
            p[i].beg = p[i].end = p[i].cap = 0;
        }
    }
    Mem::free(buf);
}

extern "C" void* sub_18006B150(void* vecp, void* pos, const void* value) {
    E24** vec = (E24**)vecp;
    E24* const b = vec[0];
    const std::size_t idx = (std::size_t)((E24*)pos - b);
    const std::size_t size = (std::size_t)(vec[1] - b);
    const std::size_t kMax = 0xAAAAAAAAAAAAAAAull;
    if (size == kMax) std::_Xlength_error("vector too long");
    const std::size_t newsize = size + 1;
    const std::size_t cap =
        (std::size_t)((unsigned char*)vec[2] - (unsigned char*)b) / 24;
    const std::size_t nc = Grow(cap, newsize, kMax);
    E24* const buf = nc ? (E24*)Mem::allocate(24 * nc) : nullptr;
    E24* const at = buf + idx;
    CopyElem(at, (const E24*)value);
    E24* const e = vec[1];
    if ((E24*)pos == e) {
        MoveRange(buf, b, e);
    } else {
        MoveRange(buf, b, (E24*)pos);
        MoveRange(at + 1, (E24*)pos, e);
    }
    DestroyFree((unsigned char*)b, size);
    vec[0] = buf;
    vec[1] = buf + newsize;
    vec[2] = (E24*)((unsigned char*)buf + 24 * nc);
    return at;
}
