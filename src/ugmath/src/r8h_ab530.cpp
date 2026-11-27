











#include <math.h>

extern "C" double sub_1800A94D0(const double* p);
extern "C" double* sub_1800A95D0(double* out, const double* z);

namespace {




int g_checking_level = 0;

}

extern "C" double* sub_1800AB530(double* a1, int a2, const double* a3,
                                 double* a4, double a5, char a6) {
    const int deg = a2;
    const int deg1 = deg - 1;
    double root[2] = {a4[0], a4[1]};
    double top[2] = {a3[2 * deg], a3[2 * deg + 1]};
    double last = sub_1800A94D0(root);
    const double dDeg = (double)deg;
    const double dDeg1 = (double)deg1;
    int iter = 1;
    int ok = 0;

    for (;;) {

        const double z0mag = sub_1800A94D0(root);


        double pr = a3[2 * deg];
        double pi = a3[2 * deg + 1];

        double v26 = sub_1800A94D0(top);
        double ar = 0.0, ai = 0.0, br = 0.0, bi = 0.0;
        for (int j = deg1; j >= 0; --j) {
            const double cr = a3[2 * j];
            const double ci = a3[2 * j + 1];
            const double nar = (root[0] * ar - root[1] * ai) + br;
            const double nai = (root[1] * ar + root[0] * ai) + bi;
            const double nbr = (root[0] * br - root[1] * bi) + pr;
            const double nbi = (root[1] * br + root[0] * bi) + pi;
            const double npr = (pr * root[0] - pi * root[1]) + cr;
            const double npi = (pr * root[1] + pi * root[0]) + ci;
            ar = nar;
            ai = nai;
            br = nbr;
            bi = nbi;
            pr = npr;
            pi = npi;
            double c[2] = {pr, pi};
            v26 = v26 * z0mag + sub_1800A94D0(c);
        }


        {
            double c[2] = {pr, pi};
            if (v26 * 5.0e-16 >= fabs(sub_1800A94D0(c))) {
                ok = 1;
                break;
            }
        }


        double gre, gim;
        if (fabs(pr) >= fabs(pi)) {
            const double r = pi / pr;
            const double den = pi * r + pr;
            gre = (r * bi + br) / den;
            gim = (bi - r * br) / den;
        } else {
            const double r = pr / pi;
            const double den = pr * r + pi;
            gre = (r * br + bi) / den;
            gim = (r * bi - br) / den;
        }




        double qre, qim;
        const double ar2 = ar + ar;
        const double ai2 = ai + ai;
        if (fabs(pr) >= fabs(pi)) {
            const double r = pi / pr;
            const double den = pi * r + pr;
            qre = (ai2 * r + ar2) / den;
            qim = (ai2 - ar2 * r) / den;
        } else {
            const double r = pr / pi;
            const double den = pr * r + pi;
            qim = (ai2 * r - ar2) / den;
            qre = (ai2 + ar2 * r) / den;
        }


        const double g2r = gre * gre - gim * gim;
        const double g2i = gim * gre + gim * gre;
        double arg[2];
        arg[0] = ((g2r - qre) * dDeg - g2r) * dDeg1;
        arg[1] = ((g2i - qim) * dDeg - g2i) * dDeg1;
        double s[2];
        sub_1800A95D0(s, arg);


        const double sumr = s[0] + gre;
        const double sumi = s[1] + gim;
        const double alt[2] = {gre - s[0], gim - s[1]};
        double v62 = sumr;
        double v63 = sumi;
        double addp[2] = {sumr, sumi};
        const double magSum = sub_1800A94D0(addp);
        if (sub_1800A94D0(alt) > magSum) {
            v62 = alt[0];
            v63 = alt[1];
        }



        double dre, dim;
        if (!(fabs(v62) >= fabs(v63))) {
            const double r = v62 / v63;
            const double den = v62 * r + v63;
            dre = (r * dDeg + 0.0) / den;
            dim = (r * 0.0 - dDeg) / den;
        } else {
            const double r = v63 / v62;
            const double den = v63 * r + v62;
            dre = (r * 0.0 + dDeg) / den;
            dim = (0.0 - r * dDeg) / den;
        }


        const double nre = root[0] - dre;
        const double nim = root[1] - dim;
        if (0.0 >= fabs(root[0] - nre) && 0.0 >= fabs(root[1] - nim)) {
            ok = 1;
            break;
        }

        double dpair[2] = {dre, dim};
        const double dmag = sub_1800A94D0(dpair);

        if (iter > 6 && dmag >= last) {
            ok = 1;
            break;
        }
        root[0] = nre;
        root[1] = nim;
        a4[0] = nre;
        a4[1] = nim;
        last = dmag;
        if (!a6) {
            double rp[2] = {root[0], root[1]};
            if (sub_1800A94D0(rp) * a5 >= dmag) {
                ok = 1;
                break;
            }
        }
        if (++iter > 100) {
            break;

        }
    }

    if (!ok && g_checking_level > 0) {


    }
    a1[0] = a4[0];
    a1[1] = a4[1];
    return a1;
}
