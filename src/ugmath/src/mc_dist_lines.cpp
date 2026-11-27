




#include <math.h>

void MC_v_unit(double* const v);

double MC_dist_lines(double* const a1, double* const a2,
                     double* const a3, double* const a4)
{
    double v[3];
    double v6 = a3[0];
    double v7 = a1[1];
    double v8 = a1[2];
    double v9 = a1[0];
    double v10 = a3[0] * v7;
    double v11 = a1[0] * a3[2];
    v[0] = a3[2] * v7 - a3[1] * v8;
    double v12 = v6 * v8 - v11;
    double v13 = v9 * a3[1];
    v[1] = v12;
    v[2] = v13 - v10;
    if (v12 * v12 + v[0] * v[0] + v[2] * v[2] < 0.00000001)
    {
        double v14 = a2[1] - a4[1];
        double v15 = a2[0] - a4[0];
        double v16 = a2[2] - a4[2];
        if (v15 * v15 + v14 * v14 + v16 * v16 < 0.00000001)
            return 0.0;
        double v17 = v14 * v8 - v16 * v7;
        double v18 = v16 * v9 - v15 * v8;
        double v19 = v15 * v7 - v14 * v9;
        if (v18 * v18 + v17 * v17 + v19 * v19 < 0.00000001)
            return 0.0;
        v[0] = v19 * v7 - v18 * v8;
        v[1] = v17 * v8 - v19 * v9;
        v[2] = v18 * v9 - v17 * v7;
        MC_v_unit(v);
        return fabs(v14 * v[1] + v15 * v[0] + v16 * v[2]);
    }
    else
    {
        MC_v_unit(v);
        return fabs((a2[0] - a4[0]) * v[0] + (a2[1] - a4[1]) * v[1]
                    + (a2[2] - a4[2]) * v[2]);
    }
}
