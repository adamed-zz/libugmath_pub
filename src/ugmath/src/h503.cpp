










#include <math.h>

extern void h805(const double* a1, const double* a2, const int* a3, int* a4);

static const double kZero = 0.0;
static const int kMode1 = 1;

void h503(int const* a1, double const* a2, double const* a3, double const* a4,
          double const* a5, double const* a6, double const* a7, int* a8,
          double* a9, double* a10)
{
    double* v11 = const_cast<double*>(a5);
    double* v12 = const_cast<double*>(a6);
    double v16 = a7[1] * *a5 - *a7 * *a6;
    double v34 = a7[1] * *a6 + *a7 * *a5;
    double v35 = v16;
    int flag;
    h805(&v34, &kZero, &kMode1, &flag);
    int v17 = *a1 - 3;
    double v23 = 0.0;
    double v24 = 0.0;
    int write9 = 0;
    int write10 = 0;
    if (flag)
    {
        if (v17 >= 0)
        {
            *a8 = 2;
            if (!v17)
            {
                a9[0] = *a2;
                a9[1] = a2[1];
                return;
            }
            v23 = *a3;
            v24 = 0.0;
            write9 = 1;
        }
        else
        {
            *a8 = 3;
            v24 = 0.0;
            v23 = *a3;
            write10 = 1;
            write9 = 1;
        }
    }
    else
    {
        double v18 = v35 / v34;
        if (v17 < 0)
        {
            *a8 = 3;
            double v19 = *a4;
            double v20 = *a3 * *a3 * v18;
            double v22 = sqrt(v20 * v18 + v19 * v19);
            v23 = v20 / v22;
            v24 = -v19 * v19 / v22;
            write10 = 1;
            write9 = 1;
        }
        else
        {
            *a8 = 1;
            if (v17)
            {
                double disc = *a3 * *a3 * v18 * v18 - *a4 * *a4;

                if (!(0.0 >= disc))
                {
                    h805(&disc, &kZero, &kMode1, &flag);
                    if (flag != 1)
                    {
                        *a8 = 2;
                        double v29 = sqrt(disc);
                        v24 = *a4 * *a4 / v29;
                        v23 = *a3 * *a3 * v18 / v29;
                        if (*a3 * v23 < 0.0)
                            v23 = -v23;
                        if (*a3 * v18 < 0.0)
                            v24 = -v24;
                        write9 = 1;
                    }
                }
            }
            else
            {
                h805(&v35, &kZero, &kMode1, &flag);
                if (flag != 1)
                {
                    h805(&v18, &kZero, &kMode1, &flag);
                    if (flag != 1)
                    {
                        *a8 = 2;
                        v24 = *a3 / (v18 * 2.0);
                        v23 = v24 * v24 / *a3;
                        write9 = 1;
                    }
                }
            }
        }
    }
    if (write10)
    {
        a10[0] = v24 * *v12 - v23 * *v11 + *a2;
        a10[1] = -v23 * *v12 - v24 * *v11 + a2[1];
    }
    if (write9)
    {
        a9[0] = v23 * *v11 - v24 * *v12 + *a2;
        a9[1] = v24 * *v11 + v23 * *v12 + a2[1];
    }
}
