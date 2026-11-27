











#include <math.h>

void h014(double* a1, double* a2, double* a3, int* a4, int* a5, int* a6);
void h053(const double* a1, const double* a2, double* a3);

void h615(const double* a1, const double* a2, const int* a3, const double* a4, int* a5,
          double* a6, double* a7)
{
    double v9 = a1[0];
    double v10 = a1[1];
    double v12 = a2[0];
    double v11 = a2[1];
    double v14 = a4[0];
    double v13 = a4[1];
    double ang[6];
    double coef[3];
    int v77 = 0;
    int v78 = 0;
    int count = 0;
    int v8 = 0;

    *a5 = 0;
    switch (*a3)
    {
    case 1:
    case 2:
    {
        double c0 = v10 * v10 * (v14 * v14) + v9 * v9 * (v13 * v13) - v14 * v14 * (v13 * v13);
        double c1 = v14 * v14 * v10 * v11 + v13 * v13 * v9 * v12;
        double c2 = c1 + c1;
        double c3 = v11 * v11 * (v14 * v14) + v12 * v12 * (v13 * v13);
        double n = sqrt(c2 * c2 + c0 * c0 + c3 * c3);
        coef[0] = c0 / n;
        coef[1] = c2 / n;
        coef[2] = c3 / n;
        h014(coef, ang, ang + 2, &v78, &v77, &count);
        v8 = count;
        if (count)
        {
            for (int i = 0; i < count; ++i)
            {
                double a = (ang[i] * v11 + v10) / v13;
                double b = (ang[i] * v12 + v9) / v14;
                h053(&a, &b, &a7[i]);
            }
        }
        else
        {
            break;
        }
    }
    goto LABEL_61;
    case 3:
    {
        double q0 = v10 * v10 - v14 * v9;
        double q1 = (v10 + v10) * v11 - v14 * v12;
        double q2 = v11 * v11;
        double n = sqrt(q1 * q1 + q0 * q0 + q2 * q2);
        coef[0] = q0 / n;
        coef[1] = q1 / n;
        coef[2] = q2 / n;
        h014(coef, ang, ang + 2, &v78, &v77, &count);
        if (count)
        {
            int k = 0;
            for (int i = 0; i < count; ++i)
            {
                double t = ang[i];
                if (t * v12 + v9 >= 0.0)
                {
                    a7[k] = t * v11 + v10;
                    ang[k] = t;
                    ++k;
                    ++v8;
                }
            }
        }
        else
        {
            break;
        }
    }
    goto LABEL_61;
    case 4:
    {
        double e1 = v13 * v13;
        double e2 = v14 * v14;
        double q0 = v9 * v9 * e1 - v10 * v10 * e2 - e2 * e1;
        double q1 = e1 * v9 * v12 - e2 * v10 * v11;
        double q2 = q1 + q1;
        double q3 = v12 * v12 * e1 - v11 * v11 * e2;
        double n = sqrt(q2 * q2 + q0 * q0 + q3 * q3);
        coef[0] = q0 / n;
        coef[1] = q2 / n;
        coef[2] = q3 / n;
        h014(coef, ang, ang + 2, &v78, &v77, &count);
        if (count)
        {
            int k = 0;
            for (int i = 0; i < count; ++i)
            {
                double t = ang[i];
                if (t * v12 + v9 >= 0.0)
                {
                    a7[k] = t * v11 + v10;
                    ang[k] = t;
                    ++k;
                    ++v8;
                }
            }
        }
        else
        {
            break;
        }
    }
    goto LABEL_61;
    default:
        return;
    }
    return;
LABEL_61:
    a6[0] = ang[0];
    a6[1] = ang[1];
    *a5 = v8;
}
