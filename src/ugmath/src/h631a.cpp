












void h630(const double* a1, const double* a2, const double* a3, const double* a4,
          int* a5, double* a6);

void h631a(double* a1, double* a2, double* a3, double* a4, double a5, int* a6, double* a7)
{
    int n = 0;
    *a6 = 0;
    h630(a1, a2, a3, a4, &n, a7);
    if (n > 2)
    {
        double v13 = a7[0];
        double v14 = a7[1];
        double v15 = a7[2];
        if ((a2[1] - v14) * (a1[1] - v14) + (a2[0] - v13) * (a1[0] - v13)
                + (a2[2] - v15) * (a1[2] - v15) > a5 + 0.0)
            return;
        if ((a4[1] - v14) * (a3[1] - v14) + (a4[0] - v13) * (a3[0] - v13)
                + (a4[2] - v15) * (a3[2] - v15) > a5 + 0.0)
            return;
        *a6 = 1;
        return;
    }
    {
        double v16 = a1[0];
        double v17 = a3[0];
        double v18 = a3[1];
        double v19 = a3[2];
        double v20 = a5 + 0.0;
        double v21 = a4[2];
        double v22 = v18 - a1[1];
        double v23 = v19 - a1[2];
        if (!((a4[1] - a1[1]) * v22 + (a4[0] - v16) * (v17 - v16) + (v21 - a1[2]) * v23 > a5 + 0.0))
        {
            a7[0] = v16;
            a7[1] = a1[1];
            a7[2] = a1[2];
        }
        else
        {
            double v24 = a2[0];
            double v25 = v18 - a2[1];
            double v26 = v19 - a2[2];
            if (!((a4[1] - a2[1]) * v25 + (a4[0] - v24) * (v17 - v24) + (v21 - a2[2]) * v26 > v20))
            {
                a7[0] = v24;
                a7[1] = a2[1];
                a7[2] = a2[2];
            }
            else
            {
                if (v25 * v22 + (v17 - v24) * (v17 - v16) + v26 * v23 > v20)
                    return;
                a7[0] = v17;
                a7[1] = a3[1];
                a7[2] = a3[2];
            }
        }
        *a6 = 2;
    }
}
