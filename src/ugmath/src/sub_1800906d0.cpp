



























































#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <malloc.h>


extern "C" __int64 __fastcall sub_180084F30(__int64 a1, __int64 a2, __int64* a3, __int64 cols, __int64 rows);
extern "C" __int64 __fastcall sub_180084BC0(__int64 a1, __int64 a2, __int64* a3, __int64 cols, __int64 rows);
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

extern "C" __int64 sub_1800906D0(__int64 a1, __int64 a2, __int64 a3, double* a4, __int64 a5,
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
        sub_180093FC0(mc, q, 0, 0);
        return 0;
    }


    double* bufA = p->wA;
    if (!bufA) {
        if (8 * countA > 0x20000) {
            bufA = static_cast<double*>(std::malloc(static_cast<size_t>(8 * countA)));
            if (!bufA) {
                sub_180093FC0(mc, q, 0, 0);
                return 0;
            }
        } else {
            bufA = static_cast<double*>(_alloca(static_cast<size_t>(8 * countA)));
        }
    }

    double* bufB = p->wB;
    if ((unsigned long long)countB > 0x1FFFFFFFFFFFFFFFULL) {
        sub_180093FC0(a2, q, 0, 0);
        return 0;
    }
    if (!bufB) {
        if (8 * countB > 0x20000) {
            bufB = static_cast<double*>(std::malloc(static_cast<size_t>(8 * countB)));
            if (!bufB) {
                sub_180093FC0(a2, q, 0, 0);
                return 0;
            }
        } else {
            bufB = static_cast<double*>(_alloca(static_cast<size_t>(8 * countB)));
        }
    }


    unsigned __int64 v93[72];
    std::memset(v93, 0, 512);
    for (int i = 0; i < 8; ++i) v93[9 * i] = 0x3FF0000000000000ULL;


    auto alphaBits = [&]() -> unsigned __int64 {
        unsigned __int64 b;
        std::memcpy(&b, alphaPtr, sizeof b);
        return b;
    };








    __int64 result = reinterpret_cast<__int64>(v93);
    __int64 v35 = total;
    __int64 v70 = total;
    if (v35 > 0) {
        __int64 v85[2];
        v85[1] = strideB;
        do {
            const __int64 v37 = (q < v35) ? q : v35;
            const __int64 v38 = v35 - v37;
            v85[0] = reinterpret_cast<__int64>(a6 + v38);
            result = sub_180084F30(0, reinterpret_cast<__int64>(bufB), v85, v37, a2);
            if (v37 > 0) {
                __int64 v86[2] = {reinterpret_cast<__int64>(v93), 8};
                __int64 v39 = v38;
                __int64 v40 = a5 * v38;
                __int64 v72 = a5 * v38;
                __int64 v41 = v37;
                __int64 v42 = inner;
                const __int64 v79 = a5 * inner;
                __int64 v73 = reinterpret_cast<__int64>(cBase + v39);
                const __int64 v69 = -v39;
                do {
                    const __int64 v43 = (v42 < v41) ? v42 : v41;
                    const __int64 v44 = v37 - (v39 + v69) - v43;
                    if (v43 > 0) {






                        __int64 v46 = 1;
                        __int64 v47 = v40;
                        __int64 trow = 0;
                        __int64 v49 = v43 - 1;
                        do {
                            const __int64 i = v46 - 1;
                            const __int64 rowbase = v47 + v39;
                            v93[trow] = Au[rowbase + i];
                            __int64 v51 = v46;
                            if (v46 < v43) {
                                if (v49 >= 4) {

                                    __int64 v58 =
                                        (__int64)(((unsigned __int64)(v43 - v46 - 4) >> 2) + 1);
                                    v51 = v46 + 4 * v58;
                                    __int64 s = rowbase + v46;
                                    __int64 d = 8 * i + v46;
                                    do {
                                        v93[d] = Au[s];
                                        v93[d + 1] = Au[s + 1];
                                        v93[d + 2] = Au[s + 2];
                                        v93[d + 3] = Au[s + 3];
                                        s += 4;
                                        d += 4;
                                        --v58;
                                    } while (v58);
                                }
                                if (v51 < v43) {
                                    __int64 s = rowbase + v51;
                                    __int64 d = 8 * i + v51;
                                    __int64 n = v43 - v51;
                                    do {
                                        v93[d] = Au[s];
                                        ++d;
                                        ++s;
                                        --n;
                                    } while (n);
                                }
                            }
                            --v49;
                            v47 += a5;
                            trow += 9;
                            ++v46;
                        } while (v46 - 1 < v43);
                    }
                    sub_180084BC0(0, reinterpret_cast<__int64>(bufA), v86, v43, v43);


                    __int64 v87[2] = {v73, ldc};
                    result = sub_180082DB0(0, v87, reinterpret_cast<__int64>(bufA),
                                           reinterpret_cast<__int64>(bufB), v43, v43, a2,
                                           alphaBits(), v43, v37, 0, v39 + v69);
                    if (v44 > 0) {
                        const __int64 v61 = v38 + v43 + v39 + v69;
                        __int64 v88[2] = {reinterpret_cast<__int64>(a4 + (v61 + a5 * v39)), a5};
                        sub_180084BC0(0, reinterpret_cast<__int64>(bufA), v88, v43, v44);
                        __int64 v89[2] = {reinterpret_cast<__int64>(cBase + v61), ldc};
                        result = sub_180082DB0(0, v89, reinterpret_cast<__int64>(bufA),
                                               reinterpret_cast<__int64>(bufB), v44, v43, a2,
                                               alphaBits(), v43, v37, 0, v39 + v69);
                    }
                    v42 = inner;
                    v41 -= inner;
                    v39 += inner;
                    v73 += 8 * inner;
                    v40 = v79 + v72;
                    v72 += v79;
                    result = -v38;
                } while (v39 + v69 < v37);
            }
            if (v70 < a1) {

                __int64 v63 = v70;
                const __int64 v65 = a5 * v38;
                __int64 v66;
                do {
                    v66 = v63 + mc;
                    const __int64 v67 = (a1 < v63 + mc) ? a1 : v63 + mc;
                    const __int64 v68 = v67 - v63;
                    __int64 v90[2] = {reinterpret_cast<__int64>(a4 + (v63 + v65)), a5};
                    sub_180084BC0(0, reinterpret_cast<__int64>(bufA), v90, v37, v68);
                    __int64 v91[2] = {reinterpret_cast<__int64>(cBase + v63), ldc};
                    result = sub_180082DB0(0, v91, reinterpret_cast<__int64>(bufA),
                                           reinterpret_cast<__int64>(bufB), v68, v37, a2,
                                           alphaBits(), -1, -1, 0, 0);
                    v63 = v66;
                } while (v66 < a1);
            }
            v35 = v70 - q;
            v70 = v35;
        } while (v35 > 0);
    }



    if (8 * countB > 0x20000) result = (p->wB ? 0 : 1);
    if (8 * countA > 0x20000) return (p->wA ? 0 : 1);
    return result;
}
