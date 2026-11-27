















#include <math.h>

double EQ_ask_length_tolerance();
void h014(double* a1, double* a2, double* a3, int* a4, int* a5, int* a6);

void h6354(const double* a1, const double* a2, const double* a3, double* a4,
           double* a5, double* a6, int* a7)
{
    double v73[3];
    double v74[2];
    double v76[3];
    int v77;
    int st5;

    *a7 = 0;
    double v17 = EQ_ask_length_tolerance();
    double v13 = a1[1] - a3[1];
    double v14 = a1[0] - a3[0];
    double v15 = a1[2] - a3[2];
    double v16 = v13 * a2[1];
    v73[2] = 1.0;
    double v18 = a3[3] * a3[3];
    {
        double dot = v16 + v14 * a2[0] + v15 * a2[2];
        v73[1] = dot + dot;
    }
    v73[0] = v13 * v13 + v14 * v14 + v15 * v15 - v18;
    h014(v73, v74, v76, &v77, &st5, a7);
    if (!*a7)
        return;

    {
        double v19 = v74[0];
        double v20 = v19;
        if (v19 < 0.0)
            v20 = -v19;
        double v21 = v74[1];
        double v22 = v21;
        if (v21 < 0.0)
            v22 = -v21;
        if (v22 > v20 || *a7 == 1)
        {
            a4[0] = v19;
            a4[1] = v21;
        }
        else
        {
            a4[0] = v21;
            a4[1] = v19;
        }
    }

    {
        long long v23 = *a7;
        for (long long i = 0; i < v23; i++)
        {
            double t = a4[i];
            double p0 = a2[0] * t + a1[0];
            double p1 = a2[1] * t + a1[1];
            double p2 = a2[2] * t + a1[2];
            a5[3 * i + 0] = p0;
            a5[3 * i + 1] = p1;
            a5[3 * i + 2] = p2;
            {
                double q0 = p0 - a3[0];
                double q1 = p1 - a3[1];
                double q2 = p2 - a3[2];
                double n = q1 * q1 + q0 * q0 + q2 * q2;
                double dist = sqrt(n);
                if (dist > v17)
                {
                    double inv = 1.0 / dist;
                    a6[3 * i + 0] = q0 * inv;
                    a6[3 * i + 1] = q1 * inv;
                    a6[3 * i + 2] = q2 * inv;
                }
            }
        }
    }
}
