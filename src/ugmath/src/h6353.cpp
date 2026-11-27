
















#include <math.h>

double EQ_ask_length_tolerance();
int SOLVE_quadratic(const double* a1, double* a2);

void h6353(const double* a1, const double* a2, const double* a3, double* a4,
           double* a5, double* a6, int* a7)
{
    int v8 = 0;
    *a7 = 0;
    double v56 = EQ_ask_length_tolerance();
    double v13 = cos(a3[6]);
    double v14 = sin(a3[6]);
    double v15 = a1[1] - a3[1];
    double v16 = a1[0] - a3[0];
    double v17 = v14;
    double v18 = a1[2] - a3[2];
    double v19 = v16 * a2[0];
    double v20 = v13 / v14;
    double v21 = v13 * v13;
    double v22 = a2[0] * a3[3] + a2[1] * a3[4] + a2[2] * a3[5];
    double v23 = v16 * a3[3] + v15 * a3[4] + v18 * a3[5];
    double v24 = v18 * a2[2];
    double v25 = v15 * a2[1];
    double v53[3];
    double roots[2];

    v53[2] = v22 * v22 - v21;
    v53[0] = v23 * v23 - (v15 * v15 + v16 * v16 + v18 * v18) * v21;
    {

        double v52b = v23 * v22 - (v19 + v25 + v24) * v21;
        v53[1] = v52b + v52b;
    }

    int v26 = SOLVE_quadratic(v53, roots);
    *a7 = v26;
    if (!v26)
        return;

    {
        double v27 = roots[0];
        double v28 = v27;
        if (v27 < 0.0)
            v28 = -v27;
        double v29 = roots[1];
        double v30 = v29;
        if (v29 < 0.0)
            v30 = -v29;
        if (v30 > v28 || v26 == 1)
        {
            a4[0] = v27;
            a4[1] = v29;
        }
        else
        {
            a4[0] = v29;
            a4[1] = v27;
        }
    }

    {
        long long v31 = v26;
        int v32 = 1;
        if (v31 >= 1)
        {
            long long v33 = 1;
            long long i = 0;
            double* v37 = a6;
            do
            {
                double t = a4[i];
                double v39 = t * a2[0] + a1[0];
                double v40 = t * a2[1] + a1[1];
                double v41 = t * a2[2] + a1[2];
                double v42 = v39 - a3[0];
                double v43 = v40 - a3[1];
                double v44 = v41 - a3[2];
                double n = v43 * v43 + v42 * v42 + v44 * v44;
                double v46 = sqrt(n);
                if (v56 < v46)
                {
                    double inv = 1.0 / v46;
                    double v48 = v43 * inv;
                    double v49 = v44 * inv;
                    double v50 = v42 * inv;
                    if (v48 * a3[4] + v50 * a3[3] + v49 * a3[5] <= 0.0)
                    {
                        --*a7;
                        if (v32 == 1 && v31 == 2)
                            v8 = 1;
                    }
                    else
                    {
                        a5[3 * i + 0] = v39;
                        a5[3 * i + 1] = v40;
                        a5[3 * i + 2] = v41;
                        v37[0] = v50;
                        v37[1] = v48;
                        v37[2] = v49;
                        if (!*a7)
                            return;
                        v37[0] = v50 * v20 - a3[3] / v17;
                        v37[1] = v48 * v20 - a3[4] / v17;
                        v37[2] = v49 * v20 - a3[5] / v17;
                    }
                }
                else
                {
                    --*a7;
                }
                ++v32;
                ++v33;
                ++i;
                v37 += 3;
            } while (v33 <= v31);
            if (v8 == 1)
            {
                a4[0] = a4[1];
                a5[0] = a5[3];
                a5[1] = a5[4];
                a5[2] = a5[5];
                a6[0] = a6[3];
                a6[1] = a6[4];
                a6[2] = a6[5];
            }
        }
    }
}
