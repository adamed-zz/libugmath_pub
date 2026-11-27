


























#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cmath>
#include <intrin.h>

extern "C" int sub_1800ABB60(const double* a1, double* a2);
extern "C" int sub_1800AC240(const double* a1, double* a2);
extern "C" double g_ugm_solve_cubic_flag;

namespace {

constexpr double kTol = 1e-13;

inline int MagBin(double a) {
    if (a > 100000.0) return 3;
    if (a > 1.0) return 2;
    return (a > 0.00001) ? 1 : 0;
}

inline int Half(double v) { return (v > 0.0) ? 0 : 1; }


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
    const int idx = 2 * MagBin(a) + Half(v);
    bins[idx] = v + bins[idx];
}

}

extern "C" int sub_1800ACA50(double a1, double a2, double a3, double a4,
                             double* a5) {
    const double t1 = (a2 * -0.5) * a3;
    const double t2 = (a3 * 0.125) * a3 * a3;
    const double t3 = (a3 * -0.375) * a3;

    double bins[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    double sumA = fabs(a1) + 0.0;
    AddTerm(bins, a1);
    sumA = sumA + fabs(t1);
    AddTerm(bins, t1);
    sumA = sumA + fabs(t2);
    AddTerm(bins, t2);
    const double foldA = Fold(bins);

    for (int i = 0; i < 8; ++i) bins[i] = 0.0;
    double sumB = fabs(a2) + 0.0;
    AddTerm(bins, a2);
    sumB = sumB + fabs(t3);
    AddTerm(bins, t3);
    const double foldB0 = Fold(bins);




    const double v23 = _mm_cvtsd_f64(
        _mm_add_sd(_mm_set_sd(a4), _mm_set_sd(sumA)));
    const double v33 = v23 + (sumB + 0.0);


    const double foldB = (sumB * kTol >= fabs(foldB0)) ? 0.0 : foldB0;



    if (!(sumA * kTol >= fabs(foldA))) {
        double c[4] = {foldA, foldB, 0.0, 1.0};
        g_ugm_solve_cubic_flag = v33;
        return sub_1800ABB60(c, a5);
    }
    double c[4] = {foldB, 0.0, 1.0, 0.0};
    const int n = sub_1800AC240(c, a5);
    a5[n] = 0.0;
    return n + 1;
}
