






#include <math.h>
extern void h311(const double* a1, const double* a2, const double* a3, double* a4);
extern void h805(const double* a, const double* b, const int* mode, int* out);
extern void h809(double* a, const double* b, const int* mode, int* out);

static const double kZero3F70 = 0.0;
static const int kMode3F70 = 1;
static const double kRange3F70[2] = {0.0, 1.0};
static const int kMode3F702 = 0;

void sub_180039F70(const double* a1, const double* a2, const double* a3,
                   const double* a4, int* a5)
{
    double v19;
    h311(a3, a2, a1, &v19);
    int* v9 = a5;
    if (a4)
    {
        if (*a4 < fabs(v19 - 0.0))
        {
            *a5 = 0;
            return;
        }
    }
    else
    {
        h805(&v19, &kZero3F70, &kMode3F70, a5);
    }
    if (*v9)
    {
        double v10 = a1[1] - a2[1];
        double v11 = a1[2] - a2[2];
        double v12 = *a3 - *a2;
        double v13 = *a1 - *a2;
        double v14 = a3[1] - a2[1];
        double v15 = a3[2] - a2[2];
        double v16 = v10 * v10 + v13 * v13 + v11 * v11;
        double v17 = sqrt(v16);
        double v20 = (v10 * v14 + v12 * v13 + v11 * v15) / (v17 * v17);
        double v18[2] = {kRange3F70[0], kRange3F70[1]};
        h809(&v20, v18, &kMode3F702, v9);
    }
}
