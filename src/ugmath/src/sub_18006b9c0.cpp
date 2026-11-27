







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






typedef unsigned char (*Cmp32)(const void*, const void*);

static void Swap32(unsigned char* x, unsigned char* y) {
    uint32_t t0, t1;
    memcpy(&t0, x, 4);
    memcpy(&t1, y, 4);
    memcpy(x, &t1, 4);
    memcpy(y, &t0, 4);
    unsigned char tmp[16];
    memcpy(tmp, x + 8, 16);
    memcpy(x + 8, y + 8, 16);
    memcpy(y + 8, tmp, 16);
    uint64_t q0, q1;
    memcpy(&q0, x + 0x18, 8);
    memcpy(&q1, y + 0x18, 8);
    memcpy(x + 0x18, &q1, 8);
    memcpy(y + 0x18, &q0, 8);
}

extern "C" unsigned char sub_18006B9C0(unsigned char* a1, unsigned char* a2,
                                       unsigned char* a3, Cmp32 cmp) {
    unsigned char result;
    if (cmp(a2, a1) && a2 != a1) Swap32(a1, a2);
    result = cmp(a3, a2);
    if (result) {
        if (a3 != a2) Swap32(a2, a3);
        result = cmp(a2, a1);
        if (result && a2 != a1) {
            uint32_t old_a1;
            memcpy(&old_a1, a1, 4);
            Swap32(a1, a2);
            return (unsigned char)old_a1;
        }
    }
    return result;
}
