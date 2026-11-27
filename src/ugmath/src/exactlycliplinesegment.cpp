





















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



namespace UGS {
namespace Math {
namespace Clip {

void Clipper::ExactlyClipLineSegment(const ClipBounds& bounds, bool reverse,
                                     CurvePoint& p1, CurvePoint& p2, double* a,
                                     double* b, double* c, double* d2, int& f1,
                                     int& f2, int& f3, int& status) {
    status = 0;
    if (!bounds.IsValid()) {
        status = 2;
        return;
    }
    f2 = 0;
    f3 = 0;
    f1 = 0;
    const int dim = bounds.dim;


    bool swapped = false;
    double sx, sy, sz, ex, ey, ez;
    double s_par, e_par, e_par_orig;
    if (p2.pt[0] > p1.pt[0]) {
        swapped = true;
    } else {
        double adx = p2.pt[0] - p1.pt[0];
        if (adx < 0.0) adx = -adx;
        if (!(adx < 1.0e-12)) {

        } else if (p2.pt[1] > p1.pt[1]) {
            swapped = true;
        } else {
            double ady = p2.pt[1] - p1.pt[1];
            if (ady < 0.0) ady = -ady;
            if (!(ady < 1.0e-12)) {

            } else if (p2.pt[2] > p1.pt[2]) {
                swapped = true;
            }
        }
    }
    if (swapped) {
        sx = p2.pt[0];
        sy = p2.pt[1];
        sz = (dim == 2) ? 0.0 : p2.pt[2];
        ex = p1.pt[0];
        ey = p1.pt[1];
        ez = (dim == 2) ? 0.0 : p1.pt[2];
        if (!reverse) {
            s_par = p2.param;
            e_par = p1.param;
            e_par_orig = e_par;
        } else {
            s_par = 0.0;
            e_par = 0.0;
            e_par_orig = 0.0;
        }
    } else {
        sx = p1.pt[0];
        sy = p1.pt[1];
        sz = (dim == 2) ? 0.0 : p1.pt[2];
        ex = p2.pt[0];
        ey = p2.pt[1];
        ez = (dim == 2) ? 0.0 : p2.pt[2];
        if (!reverse) {
            s_par = p1.param;
            e_par = p2.param;
            e_par_orig = e_par;
        } else {
            s_par = 0.0;
            e_par = 0.0;
            e_par_orig = 0.0;
        }
    }


    int code_s = 0;
    int code_e = 0;
    if (bounds.IsValid()) {
        const int f = bounds.flags;
        if (f & 1) code_s = sx > bounds.d[0];
        if ((f & 2) != 0 && bounds.d[1] > sx) code_s |= 2;
        if ((f & 4) != 0 && sy > bounds.d[2]) code_s |= 4;
        if ((f & 8) != 0 && bounds.d[3] > sy) code_s |= 8;
        if (dim == 3) {
            if ((f & 0x10) != 0 && sz > bounds.d[4]) code_s |= 0x10;
            if ((f & 0x20) != 0 && bounds.d[5] > sz) code_s |= 0x20;
        }
    }
    if (bounds.IsValid()) {
        const int f = bounds.flags;
        if ((f & 1) != 0 && ex > bounds.d[0]) code_e = 1;
        if ((f & 2) != 0 && bounds.d[1] > ex) code_e |= 2;
        if ((f & 4) != 0 && ey > bounds.d[2]) code_e |= 4;
        if ((f & 8) != 0 && bounds.d[3] > ey) code_e |= 8;
        if (dim == 3) {
            if ((f & 0x10) != 0 && ez > bounds.d[4]) code_e |= 0x10;
            if ((f & 0x20) != 0 && bounds.d[5] > ez) code_e |= 0x20;
        }
    }

    if (code_s == 0 && code_e == 0) return;
    if ((code_e & code_s) != 0) {
        f1 = 1;
        return;
    }


    double dz = ez - sz;
    double dy = ey - sy;
    double dx = ex - sx;
    double t_enter = 0.0, num_enter = 0.0, den_enter = 1.0, den_enter_keep = 1.0;
    double t_leave = 1.0, num_leave = 1.0, den_leave = 1.0;
    const int flags = bounds.flags;


    if ((flags & 1) != 0) {
        const double den = -dx;
        const double num = sx - bounds.d[0];
        if (den > 0.0) {
            const double t = num / den;
            if (t > 1.0) {
                f1 = 1;
                return;
            }
            if (t > 0.0) {
                num_enter = num;
                den_enter_keep = den;
                den_enter = den;
                f2 = 1;
                t_enter = t;
            } else {
                den_enter = 1.0;
            }
        } else if (den < 0.0) {
            const double t = num / den;
            if (t < 0.0) {
                f1 = 1;
                return;
            }
            if (t < 1.0) {
                den_leave = den;
                t_leave = t;
                num_leave = num;
                f3 = 1;
            }
            den_enter = 1.0;
        } else {
            den_enter = 1.0;
        }
    }


    if ((flags & 2) != 0) {
        const double num = bounds.d[1] - sx;
        if (!(dx > 0.0)) {
            if (dx < 0.0) {
                const double t = num / dx;
                if (t_enter > t) {
                    f1 = 1;
                    return;
                }
                if (t_leave > t) {
                    den_leave = dx;
                    t_leave = t;
                    num_leave = num;
                    f3 = 2;
                }
            }
        } else {
            const double t = num / dx;
            if (t > t_leave) {
                f1 = 1;
                return;
            }
            if (t > t_enter) {
                den_enter = dx;
                den_enter_keep = dx;
                t_enter = t;
                num_enter = num;
                f2 = 2;
            }
        }
    }


    if ((flags & 4) != 0) {
        const double den = -dy;
        const double num = sy - bounds.d[2];
        if (den > 0.0) {
            const double t = num / den;
            if (t > t_leave) {
                f1 = 1;
                return;
            }
            if (t > t_enter) {
                num_enter = num;
                den_enter_keep = den;
                den_enter = den;
                f2 = 4;
                t_enter = t;
            }
        } else if (den < 0.0) {
            const double t = num / den;
            if (t_enter > t) {
                f1 = 1;
                return;
            }
            if (t_leave > t) {
                den_leave = den;
                t_leave = t;
                num_leave = num;
                f3 = 4;
            }
        }
        den_enter = den_enter_keep;
    }


    if ((flags & 8) != 0) {
        const double num = bounds.d[3] - sy;
        if (dy > 0.0) {
            const double t = num / dy;
            if (t > t_leave) {
                f1 = 1;
                return;
            }
            if (t > t_enter) {
                den_enter = dy;
                den_enter_keep = dy;
                t_enter = t;
                num_enter = num;
                f2 = 8;
            }
        } else if (dy < 0.0) {
            const double t = num / dy;
            if (t_enter > t) {
                f1 = 1;
                return;
            }
            if (t_leave > t) {
                den_leave = dy;
                t_leave = t;
                num_leave = num;
                f3 = 8;
            }
        }
    }


    if ((flags & 0x10) != 0) {
        const double den = -dz;
        const double num = sz - bounds.d[4];
        if (den > 0.0) {
            const double t = num / den;
            if (t > t_leave) {
                f1 = 1;
                return;
            }
            if (t > t_enter) {
                num_enter = num;
                f2 = 0x10;
                den_enter = den;
                t_enter = t;
            } else {
                den_enter = den_enter_keep;
            }
        } else {
            if (den < 0.0) {
                const double t = num / den;
                if (t_enter > t) {
                    f1 = 1;
                    return;
                }
                if (t_leave > t) {
                    den_leave = den;
                    t_leave = t;
                    num_leave = num;
                    f3 = 0x10;
                }
            }
            den_enter = den_enter_keep;
        }
    }


    if ((flags & 0x20) != 0) {
        const double num = bounds.d[5] - sz;
        if (dz > 0.0) {
            const double t = num / dz;
            if (t > t_leave) {
                f1 = 1;
                return;
            }
            if (t > t_enter) {
                t_enter = t;
                f2 = 0x20;
                num_enter = num;
                den_enter = dz;
            }
        } else if (dz < 0.0) {
            const double t = num / dz;
            if (t_enter > t) {
                f1 = 1;
                return;
            }
            if (t_leave > t) {
                den_leave = dz;
                t_leave = t;
                num_leave = num;
                f3 = 0x20;
            }
        }
    }


    double new_par;
    if (!(t_leave < 1.0)) {
        new_par = e_par;
    } else {
        ex = dx * t_leave + sx;
        ey = dy * t_leave + sy;
        ez = dz * t_leave + sz;
        if (reverse) {
            f1 |= 4;
            if (swapped) {
                new_par = 1.0 - t_leave;
                num_leave = den_leave - num_leave;
            } else {
                new_par = t_leave;
            }
        } else {
            f1 |= 4;
            new_par = (e_par - s_par) * t_leave + s_par;
        }
    }
    if (t_enter > 0.0) {
        sx = sx + dx * t_enter;
        sy = sy + dy * t_enter;
        sz = sz + dz * t_enter;
        if (reverse) {
            if (swapped) {
                s_par = 1.0 - t_enter;
                num_enter = den_enter - num_enter;
            } else {
                s_par = t_enter;
            }
        } else {
            s_par = s_par + (e_par_orig - s_par) * t_enter;
        }
        f1 |= 2;
    }

    if (swapped) {
        p1.pt[0] = ex;
        p1.pt[1] = ey;
        if (dim != 2) p1.pt[2] = ez;
        p1.param = new_par;
        p2.pt[0] = sx;
        p2.pt[1] = sy;
        if (dim != 2) p2.pt[2] = sz;
        p2.param = s_par;
        if (reverse && a && c && b && d2) {
            *a = num_leave;
            *b = den_leave;
            *c = num_enter;
            *d2 = den_enter;
        }


        const int tmp = f3;
        f3 = f2;
        f2 = tmp;
        if (f1 == 4) {
            f1 = 2;
        } else if (f1 == 2) {
            f1 = 4;
        }
    } else {
        p1.pt[0] = sx;
        p1.pt[1] = sy;
        if (dim != 2) p1.pt[2] = sz;
        p1.param = s_par;
        p2.pt[0] = ex;
        p2.pt[1] = ey;
        if (dim != 2) p2.pt[2] = ez;
        p2.param = new_par;
        if (reverse && a && c && b && d2) {
            *a = num_enter;
            *b = den_enter;
            *c = num_leave;
            *d2 = den_leave;
        }
    }

    double gap = t_enter - t_leave;
    if (gap < 0.0) gap = -gap;
    if (gap < 1.0e-12) f1 = 8;
}

}
}
}
