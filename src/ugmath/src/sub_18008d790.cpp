





















#include <cstdint>
#include <cstring>
#include <xmmintrin.h>
#include <emmintrin.h>

static inline __m128d L2(const double* p) { return _mm_loadu_pd(p); }


static inline double RED(__m128d v) {
    return _mm_cvtsd_f64(_mm_add_sd(v, _mm_unpackhi_pd(v, v)));
}

extern "C" __declspec(noinline) long long sub_18008D790(
    long long m, long long n, const long long* a3, const long long* a4,
    double* Y, long long ystride, double alpha)
{
    const long long ld = a3[1];
    const long long inc = a4[1];
    const double* const A = reinterpret_cast<const double*>(a3[0]);
    const double* const X = reinterpret_cast<const double*>(a4[0]);

    long long done = 0;


    const unsigned long long span = static_cast<unsigned long long>(ld) * 8ull;
    const long long lim8 = (span <= 0x7D00ull) ? m - 7 : 0;
    if (lim8 > 0) {
        for (; done < lim8; done += 8) {
            const double* const ab = A + done * ld;
            __m128d p0 = _mm_setzero_pd();
            __m128d p1 = _mm_setzero_pd();
            __m128d p2 = _mm_setzero_pd();
            __m128d p3 = _mm_setzero_pd();
            __m128d p4 = _mm_setzero_pd();
            __m128d p5 = _mm_setzero_pd();
            __m128d p6 = _mm_setzero_pd();
            __m128d p7 = _mm_setzero_pd();
            long long c = 0;
            for (; c + 2 <= n; c += 2) {
                const __m128d xv = L2(X + c * inc);
                const double* const a = ab + c;
                p0 = _mm_add_pd(p0, _mm_mul_pd(L2(a + 0 * ld), xv));
                p1 = _mm_add_pd(p1, _mm_mul_pd(L2(a + 1 * ld), xv));
                p2 = _mm_add_pd(p2, _mm_mul_pd(L2(a + 2 * ld), xv));
                p3 = _mm_add_pd(p3, _mm_mul_pd(L2(a + 3 * ld), xv));
                p4 = _mm_add_pd(p4, _mm_mul_pd(L2(a + 4 * ld), xv));
                p5 = _mm_add_pd(p5, _mm_mul_pd(L2(a + 5 * ld), xv));
                p6 = _mm_add_pd(p6, _mm_mul_pd(L2(a + 6 * ld), xv));
                p7 = _mm_add_pd(p7, _mm_mul_pd(L2(a + 7 * ld), xv));
            }
            double s0 = RED(p0);
            double s1 = RED(p1);
            double s2 = RED(p2);
            double s3 = RED(p3);
            double s4 = RED(p4);
            double s5 = RED(p5);
            double s6 = RED(p6);
            double s7 = RED(p7);
            if (c < n) {
                const double* xd = X + c * inc;
                const double* a = A + done * ld + c;
                const long long rem = n - c;
                if (rem >= 4) {
                    long long g = (static_cast<unsigned long long>(rem - 4) >> 2) + 1;
                    do {
                        const double x0 = xd[0];
                        const double x1 = xd[inc];
                        const double x2 = xd[2 * inc];
                        const double x3 = xd[3 * inc];
                        s0 = ((x1 * a[1] + x0 * a[0]) + s0) + x2 * a[2] + x3 * a[3];
                        s1 = ((x1 * a[ld + 1] + x0 * a[ld]) + s1) + x2 * a[ld + 2] + x3 * a[ld + 3];
                        s2 = ((x1 * a[2 * ld + 1] + x0 * a[2 * ld]) + s2) + x2 * a[2 * ld + 2] +
                             x3 * a[2 * ld + 3];
                        s3 = ((x1 * a[3 * ld + 1] + x0 * a[3 * ld]) + s3) + x2 * a[3 * ld + 2] +
                             x3 * a[3 * ld + 3];
                        s4 = ((x1 * a[4 * ld + 1] + x0 * a[4 * ld]) + s4) + x2 * a[4 * ld + 2] +
                             x3 * a[4 * ld + 3];
                        s5 = ((x1 * a[5 * ld + 1] + x0 * a[5 * ld]) + s5) + x2 * a[5 * ld + 2] +
                             x3 * a[5 * ld + 3];
                        s6 = ((x1 * a[6 * ld + 1] + x0 * a[6 * ld]) + s6) + x2 * a[6 * ld + 2] +
                             x3 * a[6 * ld + 3];
                        s7 = (((x0 * a[7 * ld] + s7) + x1 * a[7 * ld + 1]) + x2 * a[7 * ld + 2]) +
                             x3 * a[7 * ld + 3];
                        xd += 4 * inc;
                        a += 4;
                        c += 4;
                    } while (--g);
                }
                for (; c < n; ++c) {
                    const double xv = *xd;
                    xd += inc;
                    s0 += xv * a[0 * ld];
                    s1 += xv * a[1 * ld];
                    s2 += xv * a[2 * ld];
                    s3 += xv * a[3 * ld];
                    s4 += xv * a[4 * ld];
                    s5 += xv * a[5 * ld];
                    s6 += xv * a[6 * ld];
                    s7 += xv * a[7 * ld];
                    ++a;
                }
            }
            double* const yb = Y + done * ystride;
            yb[0 * ystride] = s0 * alpha + yb[0 * ystride];
            yb[1 * ystride] = s1 * alpha + yb[1 * ystride];
            yb[2 * ystride] = s2 * alpha + yb[2 * ystride];
            yb[3 * ystride] = s3 * alpha + yb[3 * ystride];
            yb[4 * ystride] = s4 * alpha + yb[4 * ystride];
            yb[5 * ystride] = s5 * alpha + yb[5 * ystride];
            yb[6 * ystride] = s6 * alpha + yb[6 * ystride];
            yb[7 * ystride] = s7 * alpha + yb[7 * ystride];
        }
    }


    for (; done < m - 3; done += 4) {
        const double* const ab = A + done * ld;
        __m128d q0 = _mm_setzero_pd();
        __m128d q1 = _mm_setzero_pd();
        __m128d q2 = _mm_setzero_pd();
        __m128d q3 = _mm_setzero_pd();
        long long c = 0;
        for (; c + 2 <= n; c += 2) {
            const __m128d xv = L2(X + c * inc);
            q0 = _mm_add_pd(q0, _mm_mul_pd(L2(ab + 0 * ld + c), xv));
            q1 = _mm_add_pd(q1, _mm_mul_pd(L2(ab + 1 * ld + c), xv));
            q2 = _mm_add_pd(q2, _mm_mul_pd(L2(ab + 2 * ld + c), xv));
            q3 = _mm_add_pd(q3, _mm_mul_pd(L2(ab + 3 * ld + c), xv));
        }
        double s0 = RED(q0);
        double s1 = RED(q1);
        double s2 = RED(q2);
        double s3 = RED(q3);
        if (c < n) {
            const double* xd = X + c * inc;
            const double* a = ab + c;
            const long long rem = n - c;
            if (rem >= 4) {
                long long g = (static_cast<unsigned long long>(rem - 4) >> 2) + 1;
                do {
                    const double x0 = xd[0];
                    const double x1 = xd[inc];
                    const double x2 = xd[2 * inc];
                    const double x3 = xd[3 * inc];
                    s0 = ((x1 * a[1] + x0 * a[0]) + s0) + x2 * a[2] + x3 * a[3];
                    s1 = ((x1 * a[ld + 1] + x0 * a[ld]) + s1) + x2 * a[ld + 2] + x3 * a[ld + 3];
                    s2 = ((x1 * a[2 * ld + 1] + (x0 * a[2 * ld] + s2)) + x2 * a[2 * ld + 2]) +
                         x3 * a[2 * ld + 3];
                    s3 = (((x0 * a[3 * ld] + s3) + x1 * a[3 * ld + 1]) + x2 * a[3 * ld + 2]) +
                         x3 * a[3 * ld + 3];
                    xd += 4 * inc;
                    a += 4;
                    c += 4;
                } while (--g);
            }
            for (; c < n; ++c) {
                const double xv = *xd;
                xd += inc;
                s0 += xv * a[0 * ld];
                s1 += xv * a[1 * ld];
                s2 += xv * a[2 * ld];
                s3 += xv * a[3 * ld];
                ++a;
            }
        }
        double* const yb = Y + done * ystride;
        yb[0 * ystride] = s0 * alpha + yb[0 * ystride];
        yb[1 * ystride] = s1 * alpha + yb[1 * ystride];
        yb[2 * ystride] = s2 * alpha + yb[2 * ystride];
        yb[3 * ystride] = s3 * alpha + yb[3 * ystride];
    }


    for (; done < m - 1; done += 2) {
        const double* const ab = A + done * ld;
        __m128d q0 = _mm_setzero_pd();
        __m128d q1 = _mm_setzero_pd();
        long long c = 0;
        for (; c + 2 <= n; c += 2) {
            const __m128d xv = L2(X + c * inc);
            q0 = _mm_add_pd(q0, _mm_mul_pd(L2(ab + 0 * ld + c), xv));
            q1 = _mm_add_pd(q1, _mm_mul_pd(L2(ab + 1 * ld + c), xv));
        }
        double s0 = RED(q0);
        double s1 = RED(q1);
        if (c < n) {
            const double* xd = X + c * inc;
            const double* a = ab + c;
            const long long rem = n - c;
            if (rem >= 4) {
                long long g = (static_cast<unsigned long long>(rem - 4) >> 2) + 1;
                do {
                    const double x0 = xd[0];
                    const double x1 = xd[inc];
                    const double x2 = xd[2 * inc];
                    const double x3 = xd[3 * inc];
                    s0 = ((x1 * a[1] + (x0 * a[0] + s0)) + x2 * a[2]) + x3 * a[3];
                    s1 = (((x0 * a[ld] + s1) + x1 * a[ld + 1]) + x2 * a[ld + 2]) + x3 * a[ld + 3];
                    xd += 4 * inc;
                    a += 4;
                    c += 4;
                } while (--g);
            }
            for (; c < n; ++c) {
                const double xv = *xd;
                xd += inc;
                s0 += xv * a[0 * ld];
                s1 += xv * a[1 * ld];
                ++a;
            }
        }
        double* const yb = Y + done * ystride;
        yb[0 * ystride] = s0 * alpha + yb[0 * ystride];
        yb[1 * ystride] = s1 * alpha + yb[1 * ystride];
    }


    for (; done < m; ++done) {
        const double* const ar = A + done * ld;
        __m128d q = _mm_setzero_pd();
        long long c = 0;
        for (; c + 2 <= n; c += 2) {
            q = _mm_add_pd(q, _mm_mul_pd(L2(ar + c), L2(X + c * inc)));
        }
        double s = RED(q);
        if (c < n) {
            const double* xd = X + c * inc;
            const double* a = ar + c;
            const long long rem = n - c;
            if (rem >= 4) {
                long long g = (static_cast<unsigned long long>(rem - 4) >> 2) + 1;
                do {
                    const double x0 = xd[0];
                    const double x1 = xd[inc];
                    const double x2 = xd[2 * inc];
                    const double x3 = xd[3 * inc];
                    s = (((x2 * a[2] + x1 * a[1]) + (x0 * a[0] + s)) + x3 * a[3]);
                    xd += 4 * inc;
                    a += 4;
                    c += 4;
                } while (--g);
            }
            for (; c < n; ++c) {
                const double xv = *xd;
                xd += inc;
                s += xv * a[0];
                ++a;
            }
        }
        Y[done * ystride] = s * alpha + Y[done * ystride];
    }
    return done;
}
