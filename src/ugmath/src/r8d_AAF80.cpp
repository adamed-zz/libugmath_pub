



#include <math.h>

extern "C" __int64 sub_1800AAF80(int a1, const double* a2, double* a3) {
    __int64 result = 0;
    const __int64 v4 = a1;
    __int64 v6 = 0;
    __int64 v9 = 0;
    if (a1 < 4LL) {
        if (a1 <= 0) return result;
        goto LABEL_24;
    }
    {
        const __int64 block_count = ((a1 - 4LL) >> 2) + 1;
        v6 = 4 * block_count;
        const double* v7 = a2 + 5;
        __int64 v10 = block_count;
        do {
            double v11 = v7[-4];
            if (!(fabs(v7[-5]) * 0.00004 < fabs(v11))) v11 = 0.0;
            if (!(fabs(v11) > 0.0)) {
                result = (unsigned int)(result + 1);
                a3[v9++] = v7[-5];
            }
            double v12 = v7[-2];
            if (!(fabs(v7[-3]) * 0.00004 < fabs(v12))) v12 = 0.0;
            if (!(fabs(v12) > 0.0)) {
                result = (unsigned int)(result + 1);
                a3[v9++] = v7[-3];
            }
            double v13 = v7[0];
            if (!(fabs(v7[-1]) * 0.00004 < fabs(v13))) v13 = 0.0;
            if (!(fabs(v13) > 0.0)) {
                result = (unsigned int)(result + 1);
                a3[v9++] = v7[-1];
            }
            double v14 = v7[2];
            if (!(fabs(v7[1]) * 0.00004 < fabs(v14))) v14 = 0.0;
            if (!(fabs(v14) > 0.0)) {
                result = (unsigned int)(result + 1);
                a3[v9++] = v7[1];
            }
            v7 += 8;
        } while (--v10);
    }
LABEL_24:
    if (v6 < v4) {
        double* v15 = a3 + v9;
        const double* v16 = a2 + 2 * v6;
        __int64 v17 = v4 - v6;
        do {
            double v18 = v16[1];
            if (!(fabs(v16[0]) * 0.00004 < fabs(v18))) v18 = 0.0;
            if (!(fabs(v18) > 0.0)) {
                result = (unsigned int)(result + 1);
                *v15++ = v16[0];
            }
            v16 += 2;
        } while (--v17);
    }
    return result;
}
