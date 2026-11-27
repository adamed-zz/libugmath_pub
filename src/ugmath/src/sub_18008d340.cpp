








































#include <cstdarg>
#include <cstdlib>
#include <cstring>
#include <malloc.h>
















#include <cstdint>

extern "C" __int64 __fastcall sub_180084BC0(__int64 a1, __int64 a2, __int64* a3, __int64 cols,
                                            __int64 rows) {
    (void)a1;
    const double* src = reinterpret_cast<const double*>(a3[0]);
    const __int64 stride = a3[1];
    double* dst = reinterpret_cast<double*>(a2);

    __int64 v6 = 0;
    __int64 v9 = 0;

    const __int64 v8 = (((rows >> 63) & 3) + rows) & ~static_cast<__int64>(3);
    const __int64 v11 = v8 + 2 * ((rows % 4) / 2);


    if (((rows >> 63) & 3) + rows >= 0 && v8 != 0) {
        do {
            for (__int64 i = 0; i < cols; ++i) {
                const double* s = src + v9 + stride * i;
                dst[v6] = s[0];
                dst[v6 + 1] = s[1];
                dst[v6 + 2] = s[2];
                dst[v6 + 3] = s[3];
                v6 += 4;
            }
            v9 += 4;
        } while (v9 < v8);
    }


    for (; v9 < v11; v9 += 2) {
        for (__int64 j = 0; j < cols; v6 += 2) {
            const double* s = src + v9 + stride * j;
            dst[v6] = s[0];
            dst[v6 + 1] = s[1];
            ++j;
        }
    }


    for (; v9 < rows; ++v9) {
        for (__int64 j = 0; j < cols; ++v6) {
            dst[v6] = src[v9 + stride * j];
            ++j;
        }
    }


    if (rows > 0 && cols > 0) return reinterpret_cast<__int64>(src);
    return (rows % 4) / 2;
}



















#include <cstdint>

extern "C" __int64 __fastcall sub_180084D90(__int64 a1, __int64 a2, __int64* a3, __int64 cols,
                                            __int64 rows) {
    (void)a1;
    const double* src = reinterpret_cast<const double*>(a3[0]);
    const __int64 stride = a3[1];
    double* dst = reinterpret_cast<double*>(a2);

    __int64 v6 = 0;
    __int64 v8 = 0;
    __int64 result = rows;
    const __int64 v9 = (rows >> 63) & 3;
    __int64 v11 = (v9 + rows) & ~static_cast<__int64>(3);


    if (v9 + rows >= 0 && v11 != 0) {
        do {
            if (cols > 0) {
                __int64 j = 0;
                do {
                    const __int64 v16 = v8 + stride * j;
                    dst[v6] = src[v16];
                    dst[v6 + 1] = src[v16 + 1];
                    dst[v6 + 2] = src[v16 + 2];
                    result = *reinterpret_cast<const __int64*>(src + v16 + 3);
                    dst[v6 + 3] = src[v16 + 3];
                    v6 += 4;
                    ++j;
                } while (j < cols);
            }
            v8 += 4;
        } while (v8 < v11);
    }


    for (; v11 < rows; ++v11) {
        __int64 j = 0;
        if (cols >= 4) {
            double* p = dst + v6;
            v6 += 4 * ((static_cast<unsigned __int64>(cols) - 4) >> 2) + 4;
            __int64 k = 2;
            do {
                p[0] = src[v11 + stride * j];
                p[1] = src[v11 + stride * (k - 1)];
                p[2] = src[v11 + stride * k];
                result = reinterpret_cast<__int64>(src);
                p[3] = src[v11 + stride * (k + 1)];
                p += 4;
                j += 4;
                k += 4;
            } while (j < cols - 3);
        }
        for (; j < cols; ++v6) {
            result = reinterpret_cast<__int64>(src);
            dst[v6] = src[v11 + stride * j];
            ++j;
        }
    }
    return result;
}
































#include <cstdint>
#include <cstring>
#include <emmintrin.h>

namespace {

struct Obj {
    double* c;
    __int64 ldc;
};




__declspec(noinline) double MulA(double a, double b) {
    return _mm_cvtsd_f64(_mm_mul_pd(_mm_set_sd(a), _mm_set_sd(b)));
}
__declspec(noinline) double MulB(double a, double b) {
    return _mm_cvtsd_f64(_mm_mul_pd(_mm_set_sd(b), _mm_set_sd(a)));
}
__declspec(noinline) double AddAcc(double acc, double p) {
    return _mm_cvtsd_f64(_mm_add_sd(_mm_set_sd(acc), _mm_set_sd(p)));
}
__declspec(noinline) double AddW(double p, double c) {
    return _mm_cvtsd_f64(_mm_add_sd(_mm_set_sd(p), _mm_set_sd(c)));
}
__declspec(noinline) double WmulS(double s, double alpha) {
    return _mm_cvtsd_f64(_mm_mul_pd(_mm_set_sd(s), _mm_set_sd(alpha)));
}
__declspec(noinline) double WmulA(double alpha, double s) {
    return _mm_cvtsd_f64(_mm_mul_pd(_mm_set_sd(alpha), _mm_set_sd(s)));
}


inline double madd_seqA(const double* ap, __int64 sa, const double* bp, __int64 sb, __int64 K) {
    double s = 0.0;
    for (__int64 k = 0; k < K; ++k) s = AddAcc(s, MulA(ap[k * sa], bp[k * sb]));
    return s;
}
inline double madd_seqB(const double* ap, __int64 sa, const double* bp, __int64 sb, __int64 K) {
    double s = 0.0;
    for (__int64 k = 0; k < K; ++k) s = AddAcc(s, MulB(ap[k * sa], bp[k * sb]));
    return s;
}

}




extern "C" __int64 __fastcall sub_180082DB0(__int64 a1, __int64* a2, __int64 a3, __int64 a4,
                                            __int64 a5, __int64 a6, __int64 a7, unsigned __int64 a8,
                                            __int64 a9, __int64 a10, __int64 a11, __int64 a12);





extern "C" void sub_180093FC0(__int64 a1, __int64 a2, __int64 a3, __int64 a4);

namespace {

struct Params {
    double* wA;
    double* wB;
    __int64 mc;
    __int64 nc;
    __int64 kc;
};

}

extern "C" __int64 sub_18008D340(__int64 a1, __int64 a2, __int64 a3, double* a4, __int64 a5,
                                 double* a6, __int64 a7, double* a8, ...) {
    va_list va;
    va_start(va, a8);
    const __int64 unused1 = va_arg(va, __int64);
    const __int64 ldc = va_arg(va, __int64);
    const __int64 alpha_bits = va_arg(va, __int64);
    Params* p = va_arg(va, Params*);
    va_end(va);
    (void)unused1;

    const __int64 m = a1;
    const __int64 n = a2;
    const __int64 k = a3;
    const __int64 lda = a5;
    const __int64 ldb = a7;
    const double* A = a4;
    const double* B = a6;
    double* C = a8;

    const __int64 kc = p->kc;
    const __int64 mc = (p->mc < m) ? p->mc : m;
    const __int64 nc = (p->nc < n) ? p->nc : n;
    const __int64 countA = kc * mc;
    const __int64 countB = kc * nc;
    const unsigned long long bytesA = 8ULL * (unsigned long long)countA;
    const unsigned long long bytesB = 8ULL * (unsigned long long)countB;
    if ((unsigned long long)countA > 0x1FFFFFFFFFFFFFFFULL) {
        sub_180093FC0(kc, mc, 0, 0);
        return 0;
    }
    if ((unsigned long long)countB > 0x1FFFFFFFFFFFFFFFULL) {
        sub_180093FC0(kc, nc, 0, 0);
        return 0;
    }


    double* wA = p->wA;
    double* wB = p->wB;
    double* heapA = nullptr;
    double* heapB = nullptr;
    if (!wA) {
        if (bytesA > 0x20000) {
            heapA = static_cast<double*>(std::malloc(bytesA));
            if (!heapA) {
                sub_180093FC0(kc, mc, 0, 0);
                return 0;
            }
            wA = heapA;
        } else {
            wA = static_cast<double*>(_alloca(bytesA));
        }
    }
    if (!wB) {
        if (bytesB > 0x20000) {
            heapB = static_cast<double*>(std::malloc(bytesB));
            if (!heapB) {
                sub_180093FC0(kc, nc, 0, 0);
                return 0;
            }
            wB = heapB;
        } else {
            wB = static_cast<double*>(_alloca(bytesB));
        }
    }

    const bool full = (mc == m && kc == k && nc == n);

    __int64 result = 0;
    __int64 row = 0;
    while (row < m) {
        const __int64 rowEnd = row + mc;
        const __int64 rowStop = (m < rowEnd) ? m : rowEnd;
        const __int64 rows = rowStop - row;
        result = rowEnd;
        __int64 kk = 0;
        while (kk < k) {
            const __int64 kkEnd = kc + kk;
            const __int64 kkStop = (k < kkEnd) ? k : kkEnd;
            const __int64 colsA = kkStop - kk;

            __int64 srcA[2] = {reinterpret_cast<__int64>(A + (row + lda * kk)), lda};
            sub_180084BC0(0, reinterpret_cast<__int64>(wA), srcA, colsA, rows);
            __int64 col = 0;
            while (col < n) {
                const __int64 colEnd = nc + col;
                const __int64 colStop = (n < colEnd) ? n : colEnd;
                const __int64 colsB = colStop - col;
                if (!full || !row) {

                    __int64 srcB[2] = {reinterpret_cast<__int64>(B + (col + ldb * kk)), ldb};
                    sub_180084D90(0, reinterpret_cast<__int64>(wB), srcB, colsA, colsB);
                }

                double* cPanel = C + (row + ldc * col);
                __int64 cObj[4] = {reinterpret_cast<__int64>(cPanel), ldc,
                                   reinterpret_cast<__int64>(wB), countA};
                sub_180082DB0(0, cObj, reinterpret_cast<__int64>(wA),
                              reinterpret_cast<__int64>(wB), rows, colsA, colsB,
                              static_cast<unsigned __int64>(alpha_bits), -1, -1, 0, 0);
                col = colEnd;
            }
            kk = kkEnd;
        }
        row = rowEnd;
    }




    if (bytesB > 0x20000) {
        std::free(heapB);
        result = 0;
    }
    if (bytesA > 0x20000) {
        std::free(heapA);
        result = 0;
    }
    return result;
}
