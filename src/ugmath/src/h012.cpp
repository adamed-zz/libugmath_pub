







#include <cmath>

double EQ_ask_number_tolerance(void);

void h012(double *a1, double *a2, double *a3, int *a4)
{
    double vv[2] = {0.0, 0.0};
    double *v4 = &vv[0];
    double *v5 = &vv[1];
    long long v6 = 1;
    int v10 = 1;
LABEL_2:
    *v4 = *a1;
    *v5 = *a2;
    double v11 = vv[0];
    double v12 = vv[1];
    if (vv[0] > vv[1])
    {
        v12 = vv[1] + 6.283185307179586;
        vv[1] = vv[1] + 6.283185307179586;
    }
    double v13 = *a3;
    int v14 = 1;
    while (1)
    {
        if (EQ_ask_number_tolerance() >= fabs(v13 - v11))
            break;
        if (v13 > v11)
        {
            if (EQ_ask_number_tolerance() >= fabs(v13 - v12))
                break;
            int v15 = 3;
            if (v13 > v12)
                v15 = 5;
            int v16 = v15 - 1;
            if (v16)
            {
                int v17 = v16 - 1;
                if (!v17 || (unsigned int)(v17 - 1) < 2)
                    break;
            }
        }
        ++v14;
        v13 = v13 + 6.283185307179586;
        if (v14 > 2)
        {
            ++v10;
            ++v6;
            ++v4;
            --v5;
            if (v6 <= 2)
                goto LABEL_2;
            break;
        }
    }
    *a4 = v10;
    *a1 = v11;
    *a2 = v12;
}
