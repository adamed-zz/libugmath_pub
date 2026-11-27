





#include <math.h>

namespace {

int MagBin(double a) {
    if (a > 100000.0) return 3;
    if (a > 1.0) return 2;
    return a > 0.00001;
}
}

extern "C" int sub_1800AC240(const double* a1, double* a2) {
    double bins[4][2] = {{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}};
    const double B = a1[1];
    const double C = a1[2];
    const double A = a1[0];
    const double b2 = B * B;
    const double v9 = fabs(b2) + 0.0;
    const double cross = C * -4.0 * A;

    const int idx = MagBin(fabs(b2));
    int half = (b2 > 0.0) ? 0 : 1;
    bins[idx][half] += b2;

    const double abscross = fabs(cross);
    const double scale = v9 + abscross;
    const int idx2 = MagBin(abscross);
    half = (cross > 0.0) ? 0 : 1;
    bins[idx2][half] += cross;


    const double p01 = bins[0][1] + bins[0][0];
    const double p23 = bins[1][1] + bins[1][0];
    const double p45 = bins[2][1] + bins[2][0];
    const double p67 = bins[3][1] + bins[3][0];
    const double sum = ((p01 + 0.0) + p23) + p45 + p67;



    if (!(scale * 5.0e-16 >= fabs(sum))) {
        if (!(sum > 0.0)) return 0;
        const double r = sqrt(sum);
        double q;
        if (B >= 0.0) q = B + r;
        else q = B - r;
        const double q2 = -q * 0.5;
        a2[0] = q2 / C;
        a2[1] = A / q2;
        return 2;
    }
    const double d = -B / (C + C);
    a2[0] = d;
    a2[1] = d;
    return 2;
}
