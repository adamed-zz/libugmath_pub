








































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
    volatile double va = a;
    return _mm_cvtsd_f64(_mm_mul_sd(_mm_set_sd(b), _mm_load_sd((const double*)&va)));
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
                                            __int64 a9, __int64 a10, __int64 a11, __int64 a12) {
    const Obj* o = reinterpret_cast<const Obj*>(a2);
    double* C = o->c;
    const __int64 ldc = o->ldc;
    double* A = reinterpret_cast<double*>(a3);
    double* B = reinterpret_cast<double*>(a4);
    const __int64 N = a5;
    const __int64 K = a6;
    const __int64 M = a7;
    double alpha;
    memcpy(&alpha, &a8, sizeof alpha);
    const __int64 la = (a9 == -1) ? K : a9;
    const __int64 lb = (a10 == -1) ? K : a10;
    const __int64 offA = a11;
    const __int64 offB = a12;


    volatile __int64 kdiv = 32 * K;
    volatile __int64 kchunks = (-32 * K + 32640) / (unsigned __int64)kdiv;
    (void)kchunks;

    const __int64 M4 = (((M >> 63) & 3) + M) & ~static_cast<__int64>(3);
    const __int64 j4 = 4 * (N / 4);
    const __int64 j2 = j4 + 2 * ((N % 4) / 2);













    for (__int64 i0 = 0; i0 < M4; i0 += 4) {
        for (__int64 jp = 0; jp < j4; jp += 4) {
            const double* ap0 = A + jp * la + 4 * offA;
            for (__int64 rg = 0; rg < 4; rg += 2) {
                double s[2][4];
                double c0[2][4];
                for (__int64 r = 0; r < 2; ++r) {
                    const double* bp = B + 4 * offB + i0 * lb + rg + r;




                    for (__int64 cc = 0; cc < 4; ++cc)
                        s[r][cc] = madd_seqA(ap0 + cc, 4, bp, 4, K);
                }
                for (__int64 r = 0; r < 2; ++r)
                    for (__int64 cc = 0; cc < 4; ++cc)
                        c0[r][cc] = C[(i0 + rg + r) * ldc + jp + cc];
                for (__int64 r = 0; r < 2; ++r)
                    for (__int64 cc = 0; cc < 4; ++cc)
                        C[(i0 + rg + r) * ldc + jp + cc] =
                            AddW(WmulS(s[r][cc], alpha), c0[r][cc]);
            }
        }
    }
    for (__int64 i = M4; i < M; ++i) {
        const double* bp = B + offB + i * lb;
        for (__int64 jp = 0; jp < j4; jp += 4) {
            const double* ap0 = A + jp * la + 4 * offA;
            double s[4];
            double c0[4];
            for (__int64 cc = 0; cc < 4; ++cc) s[cc] = madd_seqB(ap0 + cc, 4, bp, 1, K);
            for (__int64 cc = 0; cc < 4; ++cc) c0[cc] = C[i * ldc + jp + cc];
            for (__int64 cc = 0; cc < 4; ++cc)
                C[i * ldc + jp + cc] = AddW(WmulA(alpha, s[cc]), c0[cc]);
        }
    }


    if (j2 > j4) {
        const double* ap0 = A + j4 * la + 2 * offA;
        const __int64 k8 = K & ~static_cast<__int64>(7);
        for (__int64 i0 = 0; i0 < M4; i0 += 4) {


            for (__int64 rg = 0; rg < 4; rg += 2) {
                double s[2][2];
                double c0[2][2];
                for (__int64 r = 0; r < 2; ++r) {
                    const double* bp = B + 4 * offB + i0 * lb + rg + r;
                    for (__int64 c = 0; c < 2; ++c) {
                        double se = 0.0, so = 0.0;
                        for (__int64 k = 0; k < k8; ++k) {
                            const double p = MulA(ap0[k * 2 + c], bp[k * 4]);
                            if (k & 1)
                                so = AddAcc(so, p);
                            else
                                se = AddAcc(se, p);
                        }
                        double sum = AddAcc(se, so);




                        const bool useB = (k8 == 0) && ((rg + r) == 0 || (rg + r) == 3);
                        for (__int64 k = k8; k < K; ++k) {
                            const double p = useB ? MulB(ap0[k * 2 + c], bp[k * 4])
                                                  : MulA(ap0[k * 2 + c], bp[k * 4]);
                            sum = AddAcc(sum, p);
                        }
                        s[r][c] = sum;
                    }
                }
                for (__int64 r = 0; r < 2; ++r)
                    for (__int64 c = 0; c < 2; ++c)
                        c0[r][c] = C[(i0 + rg + r) * ldc + j4 + c];
                for (__int64 r = 0; r < 2; ++r)
                    for (__int64 c = 0; c < 2; ++c)
                        C[(i0 + rg + r) * ldc + j4 + c] = AddW(WmulA(alpha, s[r][c]), c0[r][c]);
            }
        }
        for (__int64 i = M4; i < M; ++i) {
            const double* bp = B + offB + i * lb;
            double s[2];
            double c0[2];
            for (__int64 c = 0; c < 2; ++c) s[c] = madd_seqB(ap0 + c, 2, bp, 1, K);
            for (__int64 c = 0; c < 2; ++c) c0[c] = C[i * ldc + j4 + c];
            for (__int64 c = 0; c < 2; ++c)
                C[i * ldc + j4 + c] = AddW(WmulA(alpha, s[c]), c0[c]);
        }
    }


    if (j2 < N) {
        const double* ap0 = A + j2 * la + offA;
        for (__int64 i0 = 0; i0 < M4; i0 += 4) {
            for (__int64 r = 0; r < 4; ++r) {
                const double* bp = B + 4 * offB + i0 * lb + r;
                const double s = madd_seqA(ap0, 1, bp, 4, K);
                C[(i0 + r) * ldc + j2] = AddW(WmulS(s, alpha), C[(i0 + r) * ldc + j2]);
            }
        }
        for (__int64 i = M4; i < M; ++i) {
            const double* bp = B + offB + i * lb;
            const double s = madd_seqA(ap0, 1, bp, 1, K);
            C[i * ldc + j2] = AddW(WmulS(s, alpha), C[i * ldc + j2]);
        }
    }





    if (N == 0) return 0;
    if ((N & 3) == 0 || (N & 3) == 2) return N;
    return ((M & 3) == 0) ? M : reinterpret_cast<__int64>(C);
}
