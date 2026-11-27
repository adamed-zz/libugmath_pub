







#include <math.h>

#include <string.h>

extern "C" double* sub_1800A95D0(double* out, const double* z);

namespace {


inline unsigned BucketOf(double v) {
    const double a = fabs(v);
    if (a > 1.0e5) return 3u;
    if (a > 1.0) return 2u;
    return (a > 1.0e-5) ? 1u : 0u;
}



inline void Accum(double* bins, double v) {
    const unsigned long long i = BucketOf(v);
    const unsigned long long base = i << 4;
    const unsigned long long off = (v > 0.0) ? 0ull : 8ull;
    double* slot = (double*)((char*)bins + (base + off));
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

}

extern "C" double* sub_1800A9F60(double a1, double a2, double a3, double a4,
                                 double a5, double* a6, double* a7) {
    const double v8 = a1 * -4.0;
    const double v9 = a5 * a5;
    double bins[8] = {};
    Accum(bins, v9);
    Accum(bins, v8);
    const double v17 = a4 + ((fabs(v9) + 0.0) + fabs(v8));


    double v21 = 0.0;
    double v22 = 0.0;
    {
        const double thr = v17 * 1.0e-13;
        const double sum = Fold(bins);
        if (!(thr >= fabs(sum))) {
            double in[2] = {sum, 0.0};
            double out[2];
            sub_1800A95D0(out, in);
            v21 = out[0] * 2.0;
            v22 = out[1] * 2.0;
        }
    }

    const double v23 = a2 * -2.0;
    const double v24 = a3 * 0.75 * a3;
    for (int i = 0; i < 8; ++i) bins[i] = 0.0;
    Accum(bins, v24);
    Accum(bins, v23);
    const double v30 = (fabs(v24) + 0.0) + fabs(v23);
    const double v31 = v17 + v30;
    const double v32 = v30 * 1.0e-13;

    double sel2[2];
    SelectOrZero(v32, Fold(bins), sel2);
    const double v34 = v31 * 1.0e-13;
    const double v36 = sel2[0];
    const double v37 = sel2[1];

    double r[2];
    r[0] = v36 + v21;
    r[1] = v37 + v22;
    if (v34 >= fabs(r[0])) r[0] = 0.0;
    {
        double in[2] = {r[0], r[1]};
        sub_1800A95D0(r, in);
    }
    memcpy(a6, r, sizeof r);

    double d[2];
    d[0] = v36 - v21;
    d[1] = v37 - v22;
    if (v34 >= fabs(d[0])) d[0] = 0.0;
    {
        double in[2] = {d[0], d[1]};
        sub_1800A95D0(d, in);
    }
    memcpy(a7, d, sizeof d);
    return a7;
}
