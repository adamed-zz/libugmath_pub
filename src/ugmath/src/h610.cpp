









#include <math.h>

void h805(const double* a1, const double* a2, const int* a3, int* a4);

void h610(const double* a1, const double* a2, const double* a3, const double* a4,
          int* a5, double* a6, double* a7)
{
    static const double kZero = 0.0;
    static const int kSelTwo = 2;
    static const int kSelOne = 1;
    double v10, v11, v12, v13, v16, v17, v18, v19, v20, v22, v23, v24;
    double v26, v27, v28, v29, v31, v32, v33, v34;
    int st;
    int v21;

    v10 = *a1;
    v11 = a1[1];
    *a5 = 1;
    v12 = *a3 - v10;
    v13 = a3[1] - v11;
    v31 = v13 * v13 + v12 * v12;
    v33 = sqrt(v31);
    h805(&v31, &kZero, &kSelTwo, &st);
    if (!st)
    {
        v34 = *a2 + *a4;
        h805(&v33, &v34, &kSelOne, &st);
        if (st == 1)
        {
            v18 = v33;
            goto LABEL_14;
        }
        v16 = *a4;
        v17 = *a2;
        v18 = v33;
        v19 = v33 - (*a4 + *a2);
        if (!(v19 < 0.0))
        {
            if (v19 != 0.0)
                return;
            goto LABEL_14;
        }
        v34 = v17 - v16;
        v32 = fabs(v17 - v16);
        h805(&v33, &v32, &kSelOne, &st);
        if (st == 1)
        {
            v18 = v33;
        }
        else
        {
            v18 = v33;
            v20 = fabs(*a2 - *a4);
            if (v33 - v20 < 0.0)
                return;
            if (v33 - v20 != 0.0)
            {
                *a5 = 3;
                goto LABEL_15;
            }
        }
    LABEL_14:
        *a5 = 2;
    LABEL_15:
        v21 = *a5;
        {
            double v23x;
            v22 = ((*a2 - *a4) * (*a4 + *a2) + v31) / (v18 + v18);
            v23x = (*a2 - v22) * (*a2 + v22);
            v23 = 0.0 > v23x ? 0.0 : v23x;
            v24 = sqrt(v23);
            if (*a5 == 2)
                v24 = 0.0;
            v26 = v22 * v12;
            v27 = v24 * v13;
            v28 = v22 * v13;
            v29 = v24 * v12;
            a6[0] = (v26 - v27) / v18 + v10;
            a6[1] = (v29 + v28) / v18 + v11;
            a7[0] = (v27 + v26) / v18 + v10;
            a7[1] = (v28 - v29) / v18 + v11;
        }
        return;
    }
    h805(a2, a4, &kSelOne, &st);
    if (st == 1)
        *a5 = 4;
}
