









#include <emmintrin.h>
#include <math.h>

#include <string.h>

extern "C" double sub_1800A94D0(const double* p);
extern "C" double* sub_1800A95D0(double* out, const double* z);

namespace {


inline unsigned BucketOf(double v) {
    const double a = fabs(v);
    if (a > 1.0e5) return 3u;
    if (a > 1.0) return 2u;
    return (a > 1.0e-5) ? 1u : 0u;
}



inline void Accum(double* bins, double v) {
    const unsigned i = BucketOf(v);
    const unsigned long long off = (v > 0.0) ? 0ull : 8ull;
    double* slot = (double*)((char*)bins + 16ull * i + off);
    *slot = v + *slot;
}


inline double Fold(const double* bins) {
    double s = bins[1] + bins[0];
    s = s + 0.0;
    s = s + (bins[3] + bins[2]);
    s = s + (bins[5] + bins[4]);
    s = s + (bins[7] + bins[6]);
    return s;
}


inline void SelectOrZero(double thr, double sum, double* out) {
    if (!(thr >= fabs(sum))) {
        out[0] = sum;
    } else {
        out[0] = 0.0;
    }
    out[1] = 0.0;
}



inline void CDiv(__m128d A, double a, double b, double* re, double* im) {
    const __m128d v = A;
    const double ar = _mm_cvtsd_f64(A);
    const double ai = _mm_cvtsd_f64(_mm_unpackhi_pd(v, v));
    if (fabs(ar) >= fabs(ai)) {
        const double r = ai / ar;
        const double den = ai * r + ar;
        *re = (b * r + a) / den;
        *im = (b - a * r) / den;
    } else {
        const double r = ar / ai;
        const double den = ar * r + ai;
        *re = (b + a * r) / den;
        *im = (b * r - a) / den;
    }
}

}

extern "C" double* sub_1800A9750(double a1, double a2, double a3, double a4,
                                  double a5, const double* a6, double* a7,
                                  double* a8) {
    const double v8 = -a2;
    const double v10 = -a5;

    double bins[8] = {};
    const double v14 = a3 * 0.5 * a3;
    double mag = fabs(v14) + 0.0;
    Accum(bins, v14);
    mag = mag + fabs(v8);
    Accum(bins, v8);
    const double v26 = mag + fabs(v10);
    Accum(bins, v10);
    const double v28 = a4 + v26;
    const double v32 = v28 * 1.0e-13;

    double sel1[2];
    SelectOrZero(v32, Fold(bins), sel1);
    const double v37 = sel1[0];
    const double v38 = sel1[1];

    for (int i = 0; i < 8; ++i) bins[i] = 0.0;

    const double v36 = a2 * a3;
    const double v34 = a1 * -2.0;
    const double v40 = a3 * -0.25 * a3 * a3;
    double mag2 = fabs(v36) + 0.0;
    Accum(bins, v36);
    mag2 = mag2 + fabs(v34);
    Accum(bins, v34);
    const double v51 = mag2 + fabs(v40);
    Accum(bins, v40);
    const double v52 = v28 + v51;

    double sel2[2];
    SelectOrZero(v51 * 1.0e-13, Fold(bins), sel2);
    const double v55 = sel2[0];
    const double v56 = sel2[1];

    const double norm = sub_1800A94D0(a6);
    double res[2];
    if (!(1.0 > norm)) {

        const double norm2 = sub_1800A94D0(a6);
        const double v89 = (v52 - (1.0 - 1.0 / norm2) * v51) * 1.0e-13;
        double sre;
        double sim;
        CDiv(_mm_loadu_pd(a6), v55, v56, &sre, &sim);
        double t = v37 + sre;
        const double u = v38 + sim;
        if (v89 >= fabs(t)) t = 0.0;
        double in[2] = {t, u};
        sub_1800A95D0(res, in);
        memcpy(a7, res, sizeof res);
        double t2 = v37 - sre;
        const double u2 = v38 - sim;
        if (v89 >= fabs(t2)) t2 = 0.0;
        double in2[2] = {t2, u2};
        sub_1800A95D0(res, in2);
    } else {

        const double v57 = v52 * 1.0e-13;
        const double p0 = v37 * a6[0] - v38 * a6[1];
        const double p1 = v37 * a6[1] + v38 * a6[0];
        const double v60 = v55 + p0;
        const double v61 = v56 + p1;
        double in[2] = {v60, v61};
        const double n1 = sub_1800A94D0(in);
        if (!(v57 >= fabs(n1))) {
            double sre;
            double sim;
            CDiv(_mm_loadu_pd(a6), v60, v61, &sre, &sim);
            if (v57 >= fabs(sre)) sre = 0.0;
            double z[2] = {sre, sim};
            sub_1800A95D0(res, z);
        } else {
            res[0] = 0.0;
            res[1] = 0.0;
        }
        memcpy(a7, res, sizeof res);
        const double d0 = p0 - v55;
        const double d1 = p1 - v56;
        double diff[2] = {d0, d1};
        const double n2 = sub_1800A94D0(diff);
        if (!(v57 >= fabs(n2))) {
            double sre;
            double sim;
            CDiv(_mm_loadu_pd(a6), d0, d1, &sre, &sim);
            if (v57 >= fabs(sre)) sre = 0.0;
            double z[2] = {sre, sim};
            sub_1800A95D0(res, z);
        } else {
            res[0] = 0.0;
            res[1] = 0.0;
        }
    }
    memcpy(a8, res, sizeof res);
    return a8;
}
