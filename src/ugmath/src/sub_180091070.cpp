
































































#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <malloc.h>


extern "C" __int64 __fastcall sub_180084F30(__int64 a1, __int64 a2, __int64* a3, __int64 cols, __int64 rows);
extern "C" __int64 __fastcall sub_1800847E0(__int64 a1, __int64 a2, __int64* a3, __int64 cols, __int64 rows);
extern "C" __int64 __fastcall sub_180082DB0(__int64 a1, __int64* a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, unsigned __int64 a8, __int64 a9, __int64 a10, __int64 a11, __int64 a12);



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

extern "C" __int64 sub_180091070(__int64 a1, __int64 a2, __int64 a3, double* a4, __int64 a5,
                                 double* a6, ...) {
    va_list va;
    va_start(va, a6);
    const __int64 sB = va_arg(va, __int64);
    double* cBase = va_arg(va, double*);
    (void)va_arg(va, __int64);
    const __int64 ldc = va_arg(va, __int64);
    double* alphaPtr = va_arg(va, double*);
    Params* p = va_arg(va, Params*);
    va_end(va);

    const __int64 total = (a3 < a1) ? a3 : a1;
    const __int64 q = p->q;
    const __int64 mc = (p->mc < total) ? p->mc : total;
    const __int64 inner =
        (mc < q) ? ((mc < 8) ? mc : 8) : ((q < 8) ? q : 8);
    const __int64 countA = mc * q;
    const __int64 countB = a2 * q;
    const unsigned long long bytesA = (unsigned long long)8 * (unsigned long long)countA;
    const unsigned long long bytesB = (unsigned long long)8 * (unsigned long long)countB;

    if ((unsigned long long)countA > 0x1FFFFFFFFFFFFFFFULL) {
        sub_180093FC0(mc, q, 0, 0);
        return 0;
    }

    double* bufA = p->wA;
    if (!bufA) {
        if (bytesA > 0x20000) {
            bufA = static_cast<double*>(std::malloc(static_cast<size_t>(bytesA)));
            if (!bufA) {
                sub_180093FC0(mc, q, 0, 0);
                return 0;
            }
        } else {
            bufA = static_cast<double*>(_alloca(static_cast<size_t>(bytesA)));
        }
    }
    if ((unsigned long long)countB > 0x1FFFFFFFFFFFFFFFULL) {
        sub_180093FC0(a2, q, 0, 0);
        return 0;
    }

    double* bufB = p->wB;
    if (!bufB) {
        if (bytesB > 0x20000) {
            bufB = static_cast<double*>(std::malloc(static_cast<size_t>(bytesB)));
            if (!bufB) {
                sub_180093FC0(a2, q, 0, 0);
                return 0;
            }
        } else {
            bufB = static_cast<double*>(_alloca(static_cast<size_t>(bytesB)));
        }
    }


    unsigned __int64 v98[72];
    std::memset(v98, 0, 512);
    for (int i = 0; i < 8; ++i) v98[9 * i] = 0x3FF0000000000000ULL;

    const unsigned __int64* const Au = reinterpret_cast<const unsigned __int64*>(a4);


    auto alphaBits = [&]() -> unsigned __int64 {
        unsigned __int64 b;
        std::memcpy(&b, alphaPtr, sizeof b);
        return b;
    };


    __int64 result = reinterpret_cast<__int64>(v98);
    __int64 P = 0;
    __int64 v79 = 0;
    if (a3 > 0) {
        do {
            const __int64 W0 = a3 - P;
            __int64 W = (q < W0) ? q : W0;
            if (P < total && P + W > total) {
                W = total - P;
                v79 = total - q;
            }
            __int64 descB[2] = {reinterpret_cast<__int64>(a6 + P), sB};
            result = sub_180084F30(0, reinterpret_cast<__int64>(bufB), descB, W, a2);

            if (P < total && W > 0) {
                __int64 v43 = P;
                __int64 v46 = -P - 2;
                __int64 v103 = v46;
                const __int64 v85 = W + P + 2;
                __int64 v75 = reinterpret_cast<__int64>(cBase + P);
                __int64 v45 = inner;
                result = v85;
                do {
                    __int64 w = v85 + v46;
                    if (v45 < w) w = v45;
                    if (w > 0) {




                        for (__int64 col = 0; col < w; ++col) {
                            v98[9 * col] = Au[(v43 + col) + a5 * (v43 + col)];
                            for (__int64 row = 0; row < col; ++row)
                                v98[col + 8 * row] = Au[(v43 + col) + a5 * (v43 + row)];
                        }
                    }
                    __int64 descT[2] = {reinterpret_cast<__int64>(v98), 8};
                    sub_1800847E0(0, reinterpret_cast<__int64>(bufA), descT, w, w);
                    __int64 cd[2] = {v75, ldc};
                    const __int64 v64 = v43 - P;
                    result = sub_180082DB0(0, cd, reinterpret_cast<__int64>(bufA),
                                           reinterpret_cast<__int64>(bufB), w, w, a2,
                                           alphaBits(), w, W, 0, v64);
                    if (v64 > 0) {
                        __int64 descA2[2] = {
                            reinterpret_cast<__int64>(a4 + (v43 + a5 * P)), a5};
                        sub_1800847E0(0, reinterpret_cast<__int64>(bufA), descA2, w, v64);
                        __int64 cd2[2] = {reinterpret_cast<__int64>(cBase + P), ldc};
                        result = sub_180082DB0(0, cd2, reinterpret_cast<__int64>(bufA),
                                               reinterpret_cast<__int64>(bufB), v64, w, a2,
                                               alphaBits(), w, W, 0, v64);
                    }
                    v45 = inner;
                    v43 += inner;
                    v46 = v103 - inner;
                    v103 -= inner;
                    v75 += 8 * inner;
                    result = v85;
                } while (v43 - P < W);
            }


            const __int64 v66 = (total < P) ? total : P;
            __int64 v67 = 0;
            __int64 v69 = 0;
            if (v66 > 0) {
                do {
                    v69 = v67 + mc;
                    const __int64 v70 = (v66 < v67 + mc) ? v66 : (v67 + mc);
                    const __int64 v71 = v70 - v67;
                    __int64 descAt[2] = {
                        reinterpret_cast<__int64>(a4 + (P + a5 * v67)), a5};
                    sub_1800847E0(0, reinterpret_cast<__int64>(bufA), descAt, W, v71);
                    __int64 cd3[2] = {reinterpret_cast<__int64>(cBase + v67), ldc};
                    result = sub_180082DB0(0, cd3, reinterpret_cast<__int64>(bufA),
                                           reinterpret_cast<__int64>(bufB), v71, W, a2,
                                           alphaBits(), -1, -1, 0, 0);
                    v67 = v69;
                } while (v69 < v66);
            }
            P = q + v79;
            v79 = P;
        } while (P < a3);
    }



    if (bytesB > 0x20000) {
        std::free(p->wB ? nullptr : bufB);
        result = (p->wB ? 0 : 1);
    }
    if (bytesA > 0x20000) {
        std::free(p->wA ? nullptr : bufA);
        return (p->wA ? 0 : 1);
    }
    return result;
}
