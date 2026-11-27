



#include <math.h>

static int MagBin(double a) {
    if (a <= 100000.0) {
        if (a <= 1.0) return a > 0.00001 ? 1 : 0;
        return 2;
    }
    return 3;
}

extern "C" double sub_1800AAC40(int a1, const double* a2, double* a3,
                                double* a4) {
    double bins[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    double v11 = 0.0;
    int v12 = 0;
    __int64 v16 = 0;
    if (a1 >= 4) {
        const double* v13 = a2 + 2;
        const unsigned int blocks = ((unsigned int)(a1 - 4) >> 2) + 1;
        v12 = 4 * blocks;
        v16 = 4LL * blocks;
        for (__int64 v15 = blocks; v15; --v15) {
            const double v17 = v13[-2];
            const double v18 = fabs(v17);
            v11 = v11 + v18;
            const int v20 = MagBin(v18);
            const double v21 = v13[-1];
            const double v23 = fabs(v21);
            v11 = v11 + v23;
            const __int64 v22 = (v17 > 0.0) ? 0 : 1;
            bins[2 * v20 + v22] += v17;
            const int v25 = MagBin(v23);
            const double v26 = v13[0];
            const double v28 = fabs(v26);
            v11 = v11 + v28;
            const __int64 v27 = (v21 > 0.0) ? 0 : 1;
            bins[2 * v25 + v27] += v21;
            const int v30 = MagBin(v28);
            const __int64 v31 = (v26 > 0.0) ? 0 : 1;
            bins[2 * v30 + v31] += v26;
            const double v32 = v13[1];
            const double v33 = fabs(v32);
            v11 = v11 + v33;
            const int v34 = MagBin(v33);
            const __int64 v35 = (v32 > 0.0) ? 0 : 1;
            v13 += 4;
            bins[2 * v34 + v35] += v32;
        }
    }
    if (a1 > 0 && v12 < a1) {
        const double* v36 = a2 + v16;
        for (__int64 v37 = (unsigned int)(a1 - v12); v37; --v37) {
            const double v38 = *v36;
            const double v39 = fabs(*v36);
            v11 = v11 + v39;
            const int v40 = MagBin(v39);
            const __int64 v41 = (v38 > 0.0) ? 0 : 1;
            ++v36;
            bins[2 * v40 + v41] += v38;
        }
    }
    *a3 = v11;
    *a4 = v11 + *a4;


    const double f01 = bins[1] + bins[0];
    const double f23 = bins[3] + bins[2];
    const double f45 = bins[5] + bins[4];
    const double f67 = bins[7] + bins[6];
    const double lo = f01 + 0.0;
    const double hilo = f45 + (lo + f23);
    return hilo + f67;
}
