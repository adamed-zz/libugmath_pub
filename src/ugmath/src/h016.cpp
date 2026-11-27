







#include <cmath>

double EQ_ask_number_tolerance(void);
void h014(double *a1, double *a2, double *a3, int *a4, int *a5, int *a6);
void h018(double *a1, int *a2, double *a3);

void h016(double *a1, double *a2, double *a3, int *a4, int *a5, int *a6)
{
    *a6 = 0;
    int v79 = 3;
    double sum = a1[0] * a1[0] + a1[1] * a1[1] + a1[2] * a1[2] + a1[3] * a1[3];
    double v15 = sqrt(sum);
    double v17 = sqrt(sqrt(v15));
    if (!(EQ_ask_number_tolerance() >= fabs(v17)))
    {
        double v76[4];
        double v18 = a1[3] / v15;
        double v19 = a1[0] / v15;
        double v20 = a1[1] / v15;
        double u2 = a1[2] / v15;
        v76[0] = v19;
        v76[1] = v20;
        v76[2] = u2;
        v76[3] = v18;
        if (!(EQ_ask_number_tolerance() >= fabs(v18)))
        {
            double v22 = v19 / v18;
            *a5 = 3;
            *a4 = 3;
            double v23 = v20 / v18;
            u2 = u2 / v18;
            v76[0] = v22;
            v76[1] = v23;
            v76[2] = u2;
            v76[3] = v18 / v18;
            if (!(EQ_ask_number_tolerance() >= fabs(v22)))
            {
                double v24 = 0.0;
                double p = v23 - u2 * u2 / 3.0;
                double q = v22 - u2 * v23 / 3.0
                           + (u2 * u2 * u2 + u2 * u2 * u2) / 27.0;
                if (1e-25 > fabs(p))
                    p = 0.0;
                if (1e-37 > fabs(q))
                    q = 0.0;

        int v26 = 0;
        int v27 = 1;
        double v28 = fabs(p);
        int v29 = 0;
        double v30 = p * p * p * -4.0 - q * q * 27.0;
        double v31 = 10.0;
        do
        {
            double v32 = v28 * 10.0;
            if (v32 > 10.0)
                break;
            double v33 = v32 * 10.0;
            v26 = v29 + 1;
            if (v33 > 10.0)
                break;
            double v34 = v33 * 10.0;
            int v35 = v29 + 2;
            ++v26;
            if (v34 > 10.0)
                break;
            double v36 = v34 * 10.0;
            v26 = v35 + 1;
            if (v36 > 10.0)
                break;
            v28 = v36 * 10.0;
            int v37 = v35 + 2;
            ++v26;
            if (v28 > 10.0)
                break;
            v27 += 5;
            v26 = v37 + 1;
            v29 = v37 + 1;
        } while (v27 <= 100);
        int v38 = 0;
        double v39 = fabs(q);
        do
        {
            double v40 = v39 * 10.0;
            if (v40 > 10.0)
                break;
            double v41 = v40 * 10.0;
            if (v41 > 10.0)
            {
                ++v38;
                break;
            }
            double v42 = v41 * 10.0;
            if (v42 > 10.0)
            {
                v38 += 2;
                break;
            }
            double v43 = v42 * 10.0;
            if (v43 > 10.0)
            {
                v38 += 3;
                break;
            }
            v39 = v43 * 10.0;
            if (v39 > 10.0)
            {
                v38 += 4;
                break;
            }
            v38 += 5;
        } while (v38 <= 99);
        int v44 = v38 - 3;
        if (v44 < v26)
            v26 = v44;
        double v45;
        if (v26 >= 6)
        {
            double v46 = 1.0;
            int v47 = 6 * (v26 / 2);
            if (v47)
            {
                if (v47 < 0)
                    v31 = 0.1;
                unsigned int v48 = (v47 >= 0) ? (unsigned int)v47 : (unsigned int)(-v47);
                while (1)
                {
                    if ((v48 & 1) != 0)
                        v46 = v46 * v31;
                    v48 >>= 1;
                    if (!v48)
                        break;
                    v31 = v31 * v31;
                }
            }
            v45 = v46 * v30;
        }
        else
        {
            v45 = p * p * p * -4.0 - q * q * 27.0;
        }
        if (1e-15 > fabs(v45))
            v30 = 0.0;

                double v74[2] = {0.0, 0.0};
                if (v30 < 0.0)
                    v74[0] = sqrt(v30 * -3.0);
                if (v30 >= 0.0)
                    v74[1] = sqrt(v30 * 3.0);
                double v54[2] = {v74[0] * 1.5, v74[1] * 1.5};
                double v76b[2] = {q * -13.5, 0.0};
                double v55 = sqrt(3.0);
                double v56 = v55 * 0.5;
                double v57 = v55 * -0.5;
                double v74b[2] = {-0.5, v56};
                double v75[2] = {-0.5, v57};
                if (!(v30 < 0.0))
                {
                    *a6 = 3;
                    v75[0] = v54[0] + v76b[0];
                    v75[1] = v54[1] + v76b[1];
                    h018(v75, &v79, v76b);
                    double v70 = v76b[1];
                    double v71 = v76b[0] * -0.5;


                    double t1 = v71 - v70 * v56;
                    double t2 = v71 - v70 * v57;
                    *a2 = v76b[0] * 2.0 / 3.0;
                    a2[1] = (t1 + t1) / 3.0;
                    a2[2] = (t2 + t2) / 3.0;
                    *a3 = 0.0;
                    a3[1] = 0.0;
                }
                else
                {
                    *a6 = 1;
                    double v58 = 1.0;
                    double t1 = v76b[0] + v54[0];
                    double v60 = 1.0;
                    if (t1 < 0.0)
                        v58 = -1.0;
                    double t2 = v76b[0] - v54[0];
                    if (t2 < 0.0)
                        v60 = -1.0;
                    double u = pow(fabs(t1), 0.3333333333333333) * v58;
                    double v = pow(fabs(t2), 0.3333333333333333) * v60;
                    if (!(q <= 0.0) && v != 0.0)
                        u = p * -3.0 / v;
                    if (q < 0.0 && u != 0.0)
                        v = p * -3.0 / u;
                    *a2 = (v + u) / 3.0;
                    *a3 = 0.0;
                    double r0 = (v * v74b[0] + u * v75[0]) * 0.3333333333333333;
                    double r1 = (v * v74b[1] + u * v75[1]) * 0.3333333333333333;
                    a2[1] = r0;
                    a3[1] = r1;
                    a2[2] = a2[1];
                    v24 = -a3[1];
                }
                a3[2] = v24;
                u2 = u2 / 3.0;
                *a2 = *a2 - u2;
                a2[1] = a2[1] - u2;
                a2[2] = a2[2] - u2;
            }
            else
            {
                *a2 = 0.0;
                *a3 = 0.0;
                int v73 = 0;
                int scratch = 0;
                h014(&v76[1], a2 + 1, a3 + 1, &v73, &v79, &scratch);
                *a6 = scratch + 1;
            }
        }
        else
        {
            h014(v76, a2, a3, a4, a5, a6);
        }
    }
    else
    {
        *a4 = 4;
    }
}
