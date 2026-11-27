









#include <math.h>

extern void h270(const double* a1, const double* a2, const double* a3, const double* a4,
                 double* a5);
extern void h200(const double* a1, const double* a2, double* a3);
extern void h805(const double* a, const double* b, const int* mode, int* out);

static const double kZero405 = 0.0;
static const int kMode405a = 1;
static const int kMode405b = 2;
static const double kStep405 = 1.2566370614359172;
static const double kDiv405 = 2.5;
static const double kTiny405 = 0.0001;

void h405(const int* a1, const double* a2, const double* a3, const double* a4,
          const double* a5, const double* a6, const double* a7, int* a8, double* a9)
{
    double pr[2];
    h270(a7, a2, a5, a6, pr);
    double v80 = pr[0];
    double v81 = pr[1];

    double v13;
    double v14;
    int mode = *a1;
    if (mode - 3 >= 0)
    {
        double v15 = *a3;
        if (mode == 3)
        {
            if (v80 - v81 * v81 / v15 >= 0.0)
            {
                double t = v15 * v80;
                double v17 = sqrt(t);
                v13 = v17 / kDiv405;
                v14 = -v17;
            }
            else
            {
                double v17 = v81;
                if (v81 < 0.0)
                    v17 = -v81;
                v13 = fabs(v81 / kDiv405);
                v14 = -v17;
            }
        }
        else
        {
            double v19 = *a4;
            if (v80 * v80 / (v15 * v15) - v81 * v81 / (v19 * v19) - 1.0 > 0.0)
            {
                double v20 = v15 / v80;
                if (v20 > 0.0)
                {
                    double v76 = 1.0 - v20 * v20;
                    double v22 = sqrt(fabs(v76));
                    double v18 = atan(v22 / v20);
                    double v17 = v18;
                    v13 = v18 / kDiv405;
                    v14 = -v17;
                }
                else
                {
                    double v16 = atan(v81 / v19);
                    v13 = fabs(v16 / kDiv405);
                    v14 = -fabs(v16);
                }
            }
            else
            {
                double v16 = atan(v81 / v19);
                v13 = fabs(v16 / kDiv405);
                v14 = -fabs(v16);
            }
        }
    }
    else
    {
        v13 = kStep405;
        v14 = 0.0;
    }

    double v75 = v13;
    int v23 = 0;
    int v74 = 0;
    int v24 = 0;
    int v77 = -1;
    int v78 = 0;
    int v25 = 1;
    double v27 = v14;
    double v12 = 0.0;
    double pts[16];
    double v79[2];
    int flag;

    do
    {
        int converged = 0;
        for (;;)
        {
            double v28 = *a3;
            double v32;
            double v33;
            if (*a1 - 3 >= 0)
            {
                if (*a1 == 3)
                {
                    v79[0] = v27 * v27 / v28;
                    v79[1] = v27;
                    h805(&v75, &kZero405, &kMode405a, &flag);
                    if (flag == 1)
                    {
                        converged = 1;
                        break;
                    }
                    v32 = 1.0;
                    v33 = (v27 + v27) / *a3;
                }
                else
                {
                    double v34 = cos(v27);
                    double v35 = sin(v27);
                    double v36 = v35 * *a4 / v34;
                    v79[0] = v28 / v34;
                    v79[1] = v36;
                    h805(&v75, &kZero405, &kMode405a, &flag);
                    if (flag == 1)
                    {
                        converged = 1;
                        break;
                    }
                    double v37 = v34 * v34;
                    v33 = v35 * *a3 / v37;
                    v32 = *a4 / v37;
                }
            }
            else
            {
                double v29 = cos(v27);
                double v30 = sin(v27);
                v79[0] = v28 * v29;
                v79[1] = v30 * *a4;
                h805(&v75, &kZero405, &kMode405a, &flag);
                if (flag == 1)
                {
                    converged = 1;
                    break;
                }
                v32 = v29 * *a4;
                v33 = -*a3 * v30;
            }

            double v39 = (v81 - v79[1]) * v32 + (v80 - v79[0]) * v33;
            double v40 = fabs(v39);
            if (v40 <= kTiny405)
            {
                double r2 = (v81 - v79[1]) * (v81 - v79[1]) +
                            (v80 - v79[0]) * (v80 - v79[0]);
                double v41 = sqrt(r2);
                double v82 = v41;
                h805(&v82, &kZero405, &kMode405a, &flag);
                if (flag == 1)
                {
                    converged = 1;
                    break;
                }
                double v42 = v32 * v32 + v33 * v33;
                double v43 = sqrt(v42);
                double v76 = v40 / (v43 * v41);
                h805(&v76, &kZero405, &kMode405a, &flag);
                if (flag == 1)
                {
                    converged = 1;
                    break;
                }
            }

            double v44 = v75;
            int advance = 0;
            if (v74)
            {
                double v45 = v39 * v12;
                if (v45 < 0.0)
                    v27 = v27 - v75;
                else if (v45 == 0.0)
                {
                    converged = 1;
                    break;
                }


                v75 = v75 * 0.5;
                v27 = v27 + v75;
            }
            else
            {
                if (v23)
                {
                    v12 = (double)v23;
                    v74 = 1;
                    double v68 = v39 * (double)v23;
                    double v76 = v68;



                    if (!(v68 < 0.0))
                    {
                        if (v68 != 0.0)
                            advance = 1;
                        else
                            converged = 1;
                        break;
                    }
                    v27 = v27 - v75;
                    v75 = v75 * 0.5;
                    v27 = v27 + v44 * 0.5;
                }
                else
                {
                    v27 = v27 + v75;
                    v23 = 1;
                    if (v39 < 0.0)
                        v23 = -1;
                }
            }
            if (advance)
                break;
        }

        if (converged)
        {
            int take = 1;
            if (v24)
            {
                double v83;
                h200(v79, &pts[v78 - 1], &v83);
                h805(&v83, &kZero405, &kMode405b, &flag);
                take = (flag != 1);
            }
            if (take)
            {
                ++v24;
                v77 += 2;
                v78 = v77;
                pts[v77 - 1] = v79[0];
                pts[v77] = v79[1];
            }
        }

        if (v25 != 5)
        {
            v23 = 0;
            v74 = 0;
            v75 = v13;
            v27 = (double)v25 * v13 + v14;
        }
        ++v25;
    } while (v25 <= 5);

    *a8 = v24;
    if (v24 > 0)
    {
        for (int i = 0; i < v24; ++i)
        {
            double v57 = pts[2 * i];
            double v58 = pts[2 * i + 1];
            a9[2 * i] = v57 * *a5 - v58 * *a6 + *a2;
            a9[2 * i + 1] = v58 * *a5 + v57 * *a6 + a2[1];
        }
    }
}
