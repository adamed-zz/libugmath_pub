



































#define WIN32_LEAN_AND_MEAN
#include <intrin.h>
#include <cmath>

extern "C" double sub_1800AAC40(int n, const double* values, double* sum_out,
                                double* accum);
extern "C" int sub_1800ACA50(double a1, double a2, double a3, double a4,
                             double* a5);
extern "C" double sub_1800ACE20(double a1, double a2, double a3, double a4,
                                double* a5);
extern "C" double* sub_1800A95D0(double* out, const double* z);
extern "C" double* sub_1800A9750(double a1, double a2, double a3, double a4,
                                 double a5, const double* a6, double* a7,
                                 double* a8);
extern "C" double* sub_1800A9F60(double a1, double a2, double a3, double a4,
                                 double a5, double* a6, double* a7);
extern "C" __int64 sub_1800AAF80(int n, const double* pairs, double* out);

namespace {

constexpr double kTol = 1e-13;

inline int MagBin(double a) {
    if (a > 100000.0) return 3;
    if (a > 1.0) return 2;
    return (a > 0.00001) ? 1 : 0;
}

inline double Fold(const double* b) {
    double s = b[1] + b[0];
    s = s + 0.0;
    s = s + (b[3] + b[2]);
    s = s + (b[5] + b[4]);
    s = s + (b[7] + b[6]);
    return s;
}

inline void AddTerm(double* bins, double v) {
    const double a = fabs(v);
    const int idx = 2 * MagBin(a) + ((v > 0.0) ? 0 : 1);
    bins[idx] = v + bins[idx];
}



inline double AddL(double a, double b) {
    return _mm_cvtsd_f64(_mm_add_sd(_mm_set_sd(a), _mm_set_sd(b)));
}

inline double SubL(double a, double b) {
    return _mm_cvtsd_f64(_mm_sub_sd(_mm_set_sd(a), _mm_set_sd(b)));
}

}

extern "C" __int64 sub_1800AC470(const double* a1, double* a2) {
    const double d4 = a1[4];
    const double d = a1[3] / d4;
    const double b = a1[2] / d4;
    const double aa = a1[1] / d4;
    const double e = a1[0] / d4;

    const double dd = d * d;

    double q[4];
    q[0] = e;
    q[1] = (aa * -0.25) * d;
    q[2] = (b * 0.0625) * dd;
    q[3] = (dd * -0.01171875) * dd;

    double v64 = 0.0;
    double v63 = 0.0;
    const double v19 = sub_1800AAC40(4, q, &v64, &v63);

    const double shift = d * 0.25;


    if (v64 * kTol >= fabs(v19)) {
        const int n = sub_1800ACA50(aa, b, d, v63, a2);
        a2[n] = 0.0;
        const int cnt = n + 1;
        for (int i = 0; i < cnt; ++i) a2[i] = a2[i] - shift;
        return cnt;
    }

    const double v24 = sub_1800ACE20(e, aa, b, d, &v63);
    const double v23 = dd * 0.25;
    const double v25 = -b;

    double bins[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    double sum = fabs(v23) + 0.0;
    AddTerm(bins, v23);
    sum = sum + fabs(v25);
    AddTerm(bins, v25);
    sum = sum + fabs(v24);
    AddTerm(bins, v24);
    const double fold = Fold(bins);
    const double v38 = AddL(v63, sum);

    double v54[2] = {0.0, 0.0};
    double v55[2] = {0.0, 0.0};
    double v12lo = 0.0;
    double v12hi = 0.0;


    if (v38 * kTol >= fabs(fold)) {
        sub_1800A9F60(e, b, d, v38, v24, v54, v55);
    } else {
        v55[0] = fold;
        v55[1] = 0.0;
        sub_1800A95D0(q, v55);
        v12lo = q[0];
        v12hi = q[1];
        sub_1800A9750(aa, b, d, v38, v24, q, v54, v55);
    }

    const double v39 = v12lo;
    const double v40 = v12hi;
    const double v41 = v39 * -0.5;
    const double v43 = v40 * -0.5;

    const double b39 = v39 * 0.5;
    const double b40 = v40 * 0.5;
    const double b54r = v54[0] * 0.5;
    const double b54i = v54[1] * 0.5;
    const double b55r = v55[0] * 0.5;
    const double b55i = v55[1] * 0.5;

    double c[8];
    c[0] = AddL(b39, b54r);
    c[2] = SubL(b39, b54r);
    c[1] = AddL(b40, b54i);
    c[3] = SubL(b40, b54i);
    c[4] = AddL(v41, b55r);
    c[6] = SubL(v41, b55r);
    c[5] = AddL(v43, b55i);
    c[7] = SubL(v43, b55i);

    const int cnt = (int)sub_1800AAF80(4, c, a2);
    for (int i = 0; i < cnt; ++i) a2[i] = a2[i] - shift;
    return cnt;
}
