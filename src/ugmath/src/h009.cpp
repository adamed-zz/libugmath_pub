







#include <cmath>

double EQ_ask_number_tolerance(void);
void h010(double *a1, double *a2, int *a3, double *a4);

void h009(double *a1, double *a2, int *a3, double *a4)
{
    *a3 = 2;
    int v8 = 0;
    if (EQ_ask_number_tolerance() >= fabs(a1[1] - a1[0] - 6.283185307179586))
    {
        *a4 = a2[0];
        a4[1] = a2[1];
        return;
    }
    v8 = EQ_ask_number_tolerance() >= fabs(a2[1] - a2[0] - 6.283185307179586);
    int v15 = v8;
    if (v8)
    {
        *a4 = a1[0];
        a4[1] = a1[1];
        return;
    }
    h010(a1, a2, a3, a4);
    double v14[2];
    double *v7;
    if (!(a1[1] > a2[1]))
    {
        v14[0] = a1[0] + 6.283185307179586;
        v14[1] = a1[1] + 6.283185307179586;
        v7 = v14;
    }
    else
    {
        v14[0] = 6.283185307179586 + a2[0];
        v14[1] = 6.283185307179586 + a2[1];
        v7 = a1;
        a2 = v14;
    }
    double v13[2];
    h010(v7, a2, &v15, v13);
    if (v15 != 1)
    {
        if (*a3 == 2)
        {
            *a3 = 3;
            a4[2] = v13[0];
            a4[3] = v13[1];
        }
        else
        {
            *a3 = 2;
            a4[0] = v13[0];
            a4[1] = v13[1];
        }
    }
}
