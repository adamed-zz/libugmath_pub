







void h100(const double* a1, const double* a2, double* a3);
void h634(const double* a1, const double* a2, const double* a3, const double* a4, int* a5,
          double* a6, double* a7);
void h603(const double* a1, const double* a2, const double* a3, const double* a4, int* a5,
          double* a6);

namespace {





const double kAxisZ[3] = {0.0, 0.0, 1.0};
}

void h641(const double* a1, const double* a2, const double* a3, const double* a4,
          const double* a5, int* a6, int* a7, double* a8)
{
    int* v8 = a6;
    int* v10 = a7;
    double v14[3];
    double v15[3];
    double v16[3];
    double v17[3];

    *a6 = 0;
    *v10 = 4;
    h100(a1, a3, v14);
    h100(a2, a3, v15);
    int v18 = 0;
    h634(a4, kAxisZ, v14, v15, &v18, v17, v16);
    if (v18 != 1)
    {
        if (v18 == 3)
            return;
        double* v13 = a8;
        *v8 = -1;
        h603(v17, v16, a4, a5, v10, v13);
        if (*v10 == 1 || *v10 == 2)
            goto LABEL_7;
        if (*v10 == 3)
            return;
    }
    *v8 = -1;
    *v10 = 1;
LABEL_7:
    if ((v14[1] - a4[1]) * v15[1] + (v14[0] - *a4) * v15[0] + (v14[2] - a4[2]) * v15[2] < 0.0)
        *v8 = 1;
}
