















#include <math.h>

void vunt3(const double* a1, int* a2, double* a3);
void h430(const double* a1, const double* a2, const double* a3, double* a4);

void h6355(double* a1, double* a2, double* a3, int* a4)
{
    double v26[3];
    double v31[3];
    double v23[3];
    double v27[3];
    double v28[3];
    int v34;

    v26[0] = a2[0] - a1[0];
    v26[1] = a2[1] - a1[1];
    v26[2] = a2[2] - a1[2];
    vunt3(v26, a4, v31);
    if (!*a4)
        return;

    h430(a1, a2, a3, v23);
    v27[0] = v23[0] - a3[0];
    v27[1] = v23[1] - a3[1];
    v27[2] = v23[2] - a3[2];
    double v11 = v27[1] * v27[1] + v27[0] * v27[0] + v27[2] * v27[2];
    vunt3(v27, &v34, v28);

    if (v34)
    {
        double v12 = fabs(v28[1] * a3[4] + v28[0] * a3[3] + v28[2] * a3[5])
                   + fabs(v28[1] * a3[7] + v28[0] * a3[6] + v28[2] * a3[8])
                   + fabs(v28[1] * a3[10] + v28[0] * a3[9] + v28[2] * a3[11]);
        if (sqrt(v11) > v12)
        {
            *a4 = 0;
            return;
        }
    }

    {
        double v19 = fabs(v31[1] * a3[4] + v31[0] * a3[3] + v31[2] * a3[5])
                   + fabs(v31[1] * a3[7] + v31[0] * a3[6] + v31[2] * a3[8])
                   + fabs(v31[1] * a3[10] + v31[0] * a3[9] + v31[2] * a3[11]);
        a2[0] = v31[0] * v19 + v23[0];
        a2[1] = v31[1] * v19 + v23[1];
        a2[2] = v31[2] * v19 + v23[2];
        double v22 = -v19;
        a1[0] = v31[0] * v22 + v23[0];
        a1[1] = v31[1] * v22 + v23[1];
        a1[2] = v31[2] * v22 + v23[2];
        *a4 = 1;
    }
}
