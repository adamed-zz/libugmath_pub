
































































#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <malloc.h>

#include "deps/impl_84f30.cpp"
#include "deps/impl_84bc0.cpp"
#include "deps/impl_82db0.cpp"


extern "C" void sub_180093FC0(__int64 a1, __int64 a2, __int64 a3, __int64 a4);

namespace {

struct Params {
    double* wA;
    double* wB;
    __int64 mc;
    __int64 unused;
    __int64 q;
};

}

extern "C" __int64 sub_180091A30(__int64 a1, __int64 a2, __int64 a3, double* a4, __int64 a5,
                                 double* a6, ...) {
    va_list va;
    va_start(va, a6);
    const __int64 strideB = va_arg(va, __int64);
    double* cBase = va_arg(va, double*);
    (void)va_arg(va, __int64);
    const __int64 ldc = va_arg(va, __int64);
    double* alphaPtr = va_arg(va, double*);
    Params* p = va_arg(va, Params*);
    va_end(va);

    const unsigned __int64* const Au = reinterpret_cast<const unsigned __int64*>(a4);
    const __int64 total = (a3 < a1) ? a3 : a1;
    const __int64 q = p->q;
    const __int64 mc = (p->mc < a1) ? p->mc : a1;
    const __int64 inner =
        (mc < q) ? ((mc < 8) ? mc : 8) : ((q < 8) ? q : 8);
    const __int64 countA = mc * q;
    const __int64 countB = a2 * q;
    if ((unsigned long long)countA > 0x1FFFFFFFFFFFFFFFULL) {
        sub_180093FC0(countA, a2, 0, 0);
        return 0;
    }


    double* bufA = p->wA;
    if (!bufA) {
        if (8 * countA > 0x20000) {
            bufA = static_cast<double*>(std::malloc(static_cast<size_t>(8 * countA)));
            if (!bufA) {
                sub_180093FC0(countA, a2, 0, 0);
                return 0;
            }
        } else {
            bufA = static_cast<double*>(_alloca(static_cast<size_t>(8 * countA)));
        }
    }
    if ((unsigned long long)countB > 0x1FFFFFFFFFFFFFFFULL) {
        sub_180093FC0(countB, 0, 0, 0);
        return 0;
    }

    double* bufB = p->wB;
    if (!bufB) {
        if (8 * countB > 0x20000) {
            bufB = static_cast<double*>(std::malloc(static_cast<size_t>(8 * countB)));
            if (!bufB) {
                sub_180093FC0(countB, 0, 0, 0);
                return 0;
            }
        } else {
            bufB = static_cast<double*>(_alloca(static_cast<size_t>(8 * countB)));
        }
    }



    unsigned __int64 tile[64];
    std::memset(tile, 0, 512);
    for (int i = 0; i < 8; ++i) tile[8 * i + i] = 0x3FF0000000000000ULL;


    auto alphaBits = [&]() -> unsigned __int64 {
        unsigned __int64 b;
        std::memcpy(&b, alphaPtr, sizeof b);
        return b;
    };


    __int64 result = reinterpret_cast<__int64>(tile);
    __int64 R = total;
    if (R > 0) {
        do {
            const __int64 W = (q < R) ? q : R;
            const __int64 S = R - W;
            __int64 descB[2] = {reinterpret_cast<__int64>(a6 + S), strideB};
            result = sub_180084F30(0, reinterpret_cast<__int64>(bufB), descB, W, a2);
            if (W > 0) {
                __int64 tileDesc[2] = {reinterpret_cast<__int64>(tile), 8};
                __int64 dpos = S;
                __int64 remain = W;
                double* cCur = cBase + S;
                do {
                    const __int64 w = (inner < remain) ? inner : remain;
                    const __int64 v44 = W - (dpos - S) - w;
                    if (w > 0) {


                        for (__int64 i = 0; i < w; ++i)
                            for (__int64 j = i + 1; j < w; ++j)
                                tile[8 * i + j] = Au[a5 * (dpos + i) + (dpos + j)];
                    }
                    sub_180084BC0(0, reinterpret_cast<__int64>(bufA), tileDesc, w, w);
                    __int64 cd1[2] = {reinterpret_cast<__int64>(cCur), ldc};
                    result = sub_180082DB0(0, cd1, reinterpret_cast<__int64>(bufA),
                                           reinterpret_cast<__int64>(bufB), w, w, a2,
                                           alphaBits(), w, W, 0, dpos - S);
                    if (v44 > 0) {

                        __int64 descA2[2] = {
                            reinterpret_cast<__int64>(a4 + a5 * dpos + (dpos + w)), a5};
                        sub_180084BC0(0, reinterpret_cast<__int64>(bufA), descA2, w, v44);
                        __int64 cd2[2] = {reinterpret_cast<__int64>(cCur + w), ldc};
                        result = sub_180082DB0(0, cd2, reinterpret_cast<__int64>(bufA),
                                               reinterpret_cast<__int64>(bufB), v44, w, a2,
                                               alphaBits(), w, W, 0, dpos - S);
                    }
                    remain -= inner;
                    dpos += inner;
                    cCur += inner;
                    result = -S;
                } while (dpos - S < W);
            }
            if (R < a1) {

                __int64 v64 = R;
                const __int64 rowOff = a5 * S;
                for (;;) {
                    const __int64 v67 = v64 + mc;
                    const __int64 v68 = (a1 < v67) ? a1 : v67;
                    const __int64 v69 = v68 - v64;
                    __int64 descAt[2] = {reinterpret_cast<__int64>(a4 + rowOff + v64), a5};
                    sub_180084BC0(0, reinterpret_cast<__int64>(bufA), descAt, W, v69);
                    __int64 cdT[2] = {reinterpret_cast<__int64>(cBase + v64), ldc};
                    result = sub_180082DB0(0, cdT, reinterpret_cast<__int64>(bufA),
                                           reinterpret_cast<__int64>(bufB), v69, W, a2,
                                           alphaBits(), -1, -1, 0, 0);
                    v64 = v67;
                    if (!(v67 < a1)) break;
                }
            }
            R -= q;
        } while (R > 0);
    }


    if (8 * countB > 0x20000) result = (p->wB ? 0 : 1);
    if (8 * countA > 0x20000) return (p->wA ? 0 : 1);
    return result;
}
