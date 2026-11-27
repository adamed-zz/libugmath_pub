







void h632(const double* a1, double* a2, const double* a3, double* a4, int* a5, double* a6);

void h630(const double* a1, const double* a2, const double* a3, const double* a4,
          int* a5, double* a6)
{
    double v12[4];
    double v11[3];
    double v6 = a2[1] - a1[1];
    v12[0] = *a2 - *a1;
    double v7 = a2[2] - a1[2];
    v12[1] = v6;
    double v8 = *a4 - *a3;
    v12[2] = v7;
    double v9 = a4[1] - a3[1];
    v11[0] = v8;
    double v10 = a4[2] - a3[2];
    v11[1] = v9;
    v11[2] = v10;
    h632(a1, v12, a3, v11, a5, a6);
}
