











#include <cmath>

extern "C" double* sub_1800AB530(double* a1, int a2, const double* a3,
                                 double* a4, double a5, char a6);

namespace {

int g_checking_level = 0;


constexpr double kTol = 2e-05;

constexpr double kSnap = 0.0002;

}

extern "C" double* sub_1800AB130(int a1, const double* a2, double* a3,
                                 char a4) {
    const int deg = a1;
    double work[10];
    double root[2];
    double out[2];
    double* result = work;

    if (g_checking_level > 0 && deg > 4) {


    }
    if (deg >= 0) {
        for (int k = 0; k <= deg; ++k) {
            work[2 * k] = a2[2 * k];
            work[2 * k + 1] = a2[2 * k + 1];
        }
    } else {

        return result;
    }

    const double tol = kTol;
    const double snap = kSnap;

    for (int d = deg; d >= 1; --d) {
        root[0] = 0.0;
        root[1] = 0.0;
        out[0] = 0.0;
        out[1] = 0.0;
        result = sub_1800AB530(out, d, work, root, tol, 0);

        const double re = out[0];
        double im = out[1];

        if (!(fabs(im) > fabs(re) * snap)) im = 0.0;
        a3[2 * (d - 1)] = re;
        a3[2 * (d - 1) + 1] = im;



        double br = work[2 * d];
        double bi = work[2 * d + 1];
        for (int k = d - 1; k >= 0; --k) {
            const double cr = work[2 * k];
            const double ci = work[2 * k + 1];
            work[2 * k] = br;
            work[2 * k + 1] = bi;
            const double nbr = (br * re - bi * im) + cr;
            const double nbi = (br * im + bi * re) + ci;
            br = nbr;
            bi = nbi;
        }
    }

    if (a4 && deg > 0) {
        for (int i = 0; i < deg; ++i) {
            root[0] = a3[2 * i];
            root[1] = a3[2 * i + 1];
            out[0] = 0.0;
            out[1] = 0.0;
            result = sub_1800AB530(out, deg, a2, root, tol, 1);
            a3[2 * i] = out[0];
            a3[2 * i + 1] = out[1];
        }
    }
    return result;
}
