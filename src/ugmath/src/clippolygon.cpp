













































#include <cstddef>
#include <cstring>
#include <intrin.h>





#pragma once

#include <cstddef>
#include <cstdint>

namespace UGS {
namespace Math {

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
                                             int& flags_out,
                                             int& status_out);


        static void ExactlyClipLineSegment(const ClipBounds& bounds, bool flag,
                                           CurvePoint& p1, CurvePoint& p2,
                                           double* a, double* b, double* c,
                                           double* d2, int& f1, int& f2, int& f3,
                                           int& f4);

    public:
        static bool IsPointVisible(const ClipBounds& bounds,
                                   const double* const p);
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



extern "C" void* B22RawAlloc(std::size_t n);
extern "C" void B22RawFree(void* p);

namespace UGS {
namespace Math {

namespace {


inline std::size_t ScaleSat(int n, unsigned elem)
{
    const unsigned long long un =
        static_cast<unsigned long long>(static_cast<long long>(n));
    unsigned long long hi;
    const unsigned long long lo = _umul128(un, elem, &hi);
    return hi ? static_cast<std::size_t>(-1) : static_cast<std::size_t>(lo);
}

inline int Mul32(int a, int b)
{
    return static_cast<int>(static_cast<unsigned>(a) * static_cast<unsigned>(b));
}

}

void Clip::Clipper::ClipPolygon(const ClipBounds& bounds, int count,
                                const double* const pts,
                                const int* const pt_flags, int flags,
                                bool reverse, int& count_out,
                                double* const out_pts, int* const out_flags,
                                int& flags_out, int& status_out)
{
    count_out = 0;
    flags_out = 0;
    status_out = 0;
    if (count < 2 || pts == nullptr) {
        status_out = 1;
        return;
    }
    if (pt_flags != nullptr) {
        if (out_flags == nullptr) {
            status_out = 1;
            return;
        }
    } else if (out_flags != nullptr) {
        status_out = 1;
        return;
    }
    if (!bounds.IsValid()) {
        status_out = 2;
        return;
    }

    double dbuf_stack[1800];
    int ibuf_stack[600];
    double* dbuf = dbuf_stack;
    int* ibuf = ibuf_stack;
    try {
        const int dim = bounds.dim;
        const int nd = Mul32(dim, count);
        if (Mul32(nd, 2) > 1800) {
            dbuf = static_cast<double*>(B22RawAlloc(ScaleSat(Mul32(nd, 2), 8)));
        }
        if (pt_flags != nullptr && Mul32(count, 2) > 600) {
            ibuf = static_cast<int*>(B22RawAlloc(ScaleSat(Mul32(count, 2), 4)));
        }

        bool alt = true;
        std::memcpy(out_pts, pts,
                    static_cast<std::size_t>(static_cast<std::ptrdiff_t>(nd) * 8));
        if (pt_flags != nullptr && out_flags != nullptr) {
            std::memcpy(out_flags, pt_flags,
                        static_cast<std::size_t>(static_cast<std::ptrdiff_t>(count) * 4));
        }



        alignas(8) unsigned char lbuf[sizeof(ClipBounds)];
        std::memcpy(lbuf, &bounds, sizeof(ClipBounds));
        ClipBounds* const local = reinterpret_cast<ClipBounds*>(lbuf);
        const int limit = Mul32(dim, 2);
        if (limit > 0) {
            int idx = 0;
            unsigned bit = 1;
            do {
                const double* src_pts = dbuf;
                double* dst_pts = out_pts;
                const int* src_flags = ibuf;
                int* dst_flags = out_flags;
                if (alt) {
                    src_pts = out_pts;
                    dst_pts = dbuf;
                    src_flags = out_flags;
                    dst_flags = ibuf;
                }
                local->flags = static_cast<int>(bit);
                if ((bit & static_cast<unsigned>(bounds.flags)) != 0) {
                    ClipPolygonBySinglePlane(*local, count, src_pts, src_flags, flags,
                                             reverse, count_out, dst_pts, dst_flags,
                                             flags_out, status_out);
                    if (status_out != 0) {
                        count_out = 0;
                        break;
                    }
                    count = count_out;
                    if (count == 0) {
                        break;
                    }
                    alt = !alt;
                }
                ++idx;
                bit = (bit << 1) | (bit >> 31);
            } while (idx < limit);
        }

        if (!alt && count_out > 0) {
            const int cd = Mul32(count_out, dim);
            std::memcpy(out_pts, dbuf,
                        static_cast<std::size_t>(static_cast<std::ptrdiff_t>(cd) * 8));
            if (ibuf != nullptr && out_flags != nullptr) {
                std::memcpy(out_flags, ibuf,
                            static_cast<std::size_t>(
                                static_cast<std::ptrdiff_t>(count_out) * 4));
            }
        }


        if (dbuf != nullptr && dbuf != dbuf_stack) {
            B22RawFree(dbuf);
        }
        if (ibuf != nullptr && ibuf != ibuf_stack) {
            B22RawFree(ibuf);
        }
    } catch (...) {
        status_out = 3;
        count_out = 0;
    }
}

}
}
