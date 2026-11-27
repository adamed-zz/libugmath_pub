









#include <math.h>
#include <string.h>

static double PtrAsDouble(const void* p)
{
    double d;
    memcpy(&d, &p, sizeof(d));
    return d;
}

void h55030(double const* a1, double const* a2, double const* a3, double const* a4,
            double const* a5, double const* a6, double const* a7, double const* a8,
            int const* a9, double* a10)
{
    double v10 = 0.0;
    double v11 = 0.0;
    double v12 = 0.0;
    double v13 = fabs(*a5 - *a4);
    double v14 = fabs(*a6 - *a5);
    double v15 = 3.0 / (v13 * v13);
    double v16 = 3.0 / (v14 * v14);
    double v17 = 1.0 / v14;
    double v18 = (*a2 - *a1) * v15 + (*a3 - *a2) * v16;
    double v19 = 1.0 / v13;
    double v20 = (a2[1] - a1[1]) * v15 + (a3[1] - a2[1]) * v16;
    double v21 = (a2[2] - a1[2]) * v15 + (a3[2] - a2[2]) * v16;
    double v22s = 1.0 / v14 + 1.0 / v13;
    double v22 = v22s + v22s;
    double v25 = 0.0;
    double v26 = 0.0;
    double v27 = 0.0;
    const double* v23;
    const double* v24;
    switch (*a9)
    {
    case 1:
        v23 = a7;
        v24 = a8;
        v26 = 1.0 / v19;
        v10 = v22 * *a7 + v17 * *a8;
        v27 = v22;
        v12 = v17 * a8[2] + v22 * a7[2];
        v25 = 1.0 / v14;
        v11 = v25 * v24[1] + v27 * v23[1];
        break;
    case 2:
        v23 = a7;
        v24 = a8;
        v26 = 1.0 / v22;
        v10 = v19 * *a7 + v17 * *a8;
        v27 = 1.0 / v13;
        v12 = v17 * a8[2] + v19 * a7[2];
        v25 = 1.0 / v14;
        v11 = v25 * v24[1] + v27 * v23[1];
        break;
    case 3:
        v23 = a7;
        v24 = a8;
        v25 = v22;
        v26 = 1.0 / v17;
        v10 = v19 * *a7 + v22 * *a8;
        v27 = 1.0 / v13;
        v12 = v22 * a8[2] + v19 * a7[2];
        v11 = v25 * v24[1] + v27 * v23[1];
        break;
    default:
        v26 = PtrAsDouble(a5);
        break;
    }
    a10[0] = v18 * v26 + v10 * -v26;
    a10[1] = v20 * v26 + v11 * -v26;
    a10[2] = v21 * v26 + v12 * -v26;
}
