





























#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cmath>
#include <intrin.h>

extern "C" int sub_1800ABB60(const double* a1, double* a2);
extern "C" double g_ugm_solve_cubic_flag;

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

}

extern "C" double sub_1800ACE20(double a1, double a2, double a3, double a4,
                                double* a5) {

    const double t1 = (a1 * 4.0) * a3;
    const double t2 = (-a2) * a2;
    const double t3 = ((-a1) * a4) * a4;

    double bins[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    double sumA = fabs(t1) + 0.0;
    AddTerm(bins, t1);
    sumA = sumA + fabs(t2);
    AddTerm(bins, t2);
    sumA = sumA + fabs(t3);
    AddTerm(bins, t3);
    const double foldA = Fold(bins);


    if (!(sumA * kTol >= fabs(foldA))) {
        const double sumA0 = sumA + 0.0;
        const double u1 = a2 * a4;
        const double u2 = a1 * -4.0;
        const double v36 = (a4 * 0.25) * a4 - a3;

        for (int i = 0; i < 8; ++i) bins[i] = 0.0;
        double sumB = fabs(u1) + 0.0;
        AddTerm(bins, u1);
        sumB = sumB + fabs(u2);
        AddTerm(bins, u2);
        const double foldB = Fold(bins);


        double v7 = 0.0;
        if (!(sumB * kTol >= fabs(foldB))) v7 = foldB;




        const double v45 = _mm_cvtsd_f64(
            _mm_add_sd(_mm_set_sd(sumA0), _mm_set_sd(sumB)));
        double coef[4] = {foldA, v7, -a3, 1.0};
        double roots[3] = {0.0, 0.0, 0.0};
        g_ugm_solve_cubic_flag = v45;
        const int n = sub_1800ABB60(coef, roots);
        if (n <= 0) {
            *a5 = 1e20;
            return a3;
        }

        bool has = false;
        double bestcand = -1e20;
        double best = a3;
        double minres = 1e20;
        double minroot = a3;
        const double na3 = -a3;
        for (int i = 0; i < n; ++i) {
            const double root = roots[i];
            const double d = na3 + root;
            const double rabs = fabs(root);
            const double lin = fabs(d) + 1.0 * rabs;
            const double v52 = (d * root) + v7;
            const double v53 = fabs(v52);
            const double v54 = fabs((v52 * root) + foldA);
            const double v55 =
                (((v53 + lin * rabs) * rabs) + v54) * 5.0e-16;
            if (v55 >= v54) {
                has = true;
                const double cand = root + v36;
                if (cand > bestcand) {
                    *a5 = v55;
                    bestcand = cand;
                    best = root;
                }
            }
            if (minres > v54) {
                minroot = root;
                minres = v54;
            }
        }
        if (has) return best;
        *a5 = minres;
        return minroot;
    }

    *a5 = fabs(foldA);
    return 0.0;
}
