











#include <math.h>

void h100(const double* a1, const double* a2, double* a3);
void h922(const double* a1, double* a2);
void h611(const double* a1, const double* a2, const double* a3, int* a4, double* a5,
          double* a6);
void h110(const double* a1, double* a2);

void h612(const double* a1, const double* a2, const double* a3, int* a4, double* a5,
          double* a6)
{
    static const double kOne = 1.0;
    double pt[6];
    double v30[8];
    double v31[8];
    double v33[9];
    double v10, v11, v12, v13, v14, v15, v16, v17;

    h100(a1, a3, &pt[0]);
    h100(a1 + 3, a3, &pt[3]);
    v10 = a2[11];
    v11 = a2[12];
    v12 = a2[10];
    v13 = a2[7];
    v14 = a2[9];
    v15 = v10 * pt[0];
    v16 = v10 * pt[3];
    v30[0] = a2[0];
    v30[1] = a2[1];
    v17 = (v11 * a2[8] - v13 * v10) / v12;
    v30[2] = (v13 * v11 + a2[8] * v10) / v14;
    v30[3] = v17;
    v30[4] = a2[2];
    v30[5] = 1.0;
    pt[3] = (v11 * pt[3] + v10 * pt[4]) / v14;
    pt[0] = (v11 * pt[0] + v10 * pt[1]) / v14;
    pt[1] = (v11 * pt[1] - v15) / v12;
    pt[4] = (v11 * pt[4] - v16) / v12;
    h922(&kOne, v33);
    h611(&pt[0], v30, v33, a4, &v31[0], a6);
    if (*a4 != 1)
    {
        h110(a3, v33);
        int n = *a4;
        if (n >= 2)
        {
            int v19 = 0;
            double* v20 = &v31[1];
            int v21 = n - 1;
            do
            {
                double v22 = *(v20 - 1) * a2[9];
                double v23 = a2[10] * *v20;
                v20[1] = a2[2];
                double v24 = v22 * a2[11] + v23 * a2[12];
                double v25 = v22 * a2[12] - v23 * a2[11];
                *v20 = v24;
                *(v20 - 1) = v25;
                h100(&v31[v19], v33, &a5[v19]);
                v19 += 3;
                v20 += 3;
                --v21;
            } while (v21);
        }
    }
}
