







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






extern "C" unsigned int sub_18006B330(int* a1, int* a2, int* a3) {
    const long long n = a3 - a1;
    if (n <= 40) {
        unsigned int result = (unsigned int)*a2;
        if ((int)result < *a1) {
            *a2 = *a1;
            *a1 = (int)result;
            result = (unsigned int)*a2;
        }
        const int v21 = *a3;
        if (*a3 < (int)result) {
            *a3 = (int)result;
            *a2 = v21;
            result = (unsigned int)*a1;
            if (v21 < *a1) {
                *a2 = *a1;
                *a1 = v21;
            }
        }
        return result;
    }
    const long long k = (n + 1) >> 3;
    const long long i0 = 0;
    const long long i1 = k;
    const long long i2 = 2 * k;
    int t = a1[i1];
    if (t < a1[i0]) {
        a1[i1] = a1[i0];
        a1[i0] = t;
        t = a1[i1];
    }
    int u = a1[i2];
    if (u < t) {
        a1[i2] = t;
        a1[i1] = u;
        if (u < a1[i0]) {
            a1[i1] = a1[i0];
            a1[i0] = u;
        }
    }
    int v10 = *a2;
    int* const m1 = a2 - k;
    const int v12 = *m1;
    if (*a2 < v12) {
        *a2 = v12;
        *m1 = v10;
        v10 = *a2;
    }
    const int v13 = a2[k];
    if (v13 < v10) {
        a2[k] = v10;
        *a2 = v13;
        if (v13 < *m1) {
            *a2 = *m1;
            *m1 = v13;
        }
    }
    int* const m2 = a3 - i2;
    int* const m3 = a3 - i1;
    int v16 = *m3;
    if (v16 < *m2) {
        *m3 = *m2;
        *m2 = v16;
        v16 = *m3;
    }
    const int v17 = *a3;
    if (*a3 < v16) {
        *a3 = v16;
        *m3 = v17;
        if (v17 < *m2) {
            *m3 = *m2;
            *m2 = v17;
        }
    }
    int v18 = *a2;
    const int v19 = a1[i1];
    if (*a2 < v19) {
        *a2 = v19;
        a1[i1] = v18;
        v18 = *a2;
    }
    const int v20 = *m3;
    unsigned int result;
    if (v20 < v18) {
        *m3 = v18;
        *a2 = v20;
        result = (unsigned int)a1[i1];
        if (v20 < (int)result) {
            *a2 = (int)result;
            a1[i1] = v20;
        }
    } else {

        result = (unsigned int)(std::uintptr_t)m3;
    }
    return result;
}
