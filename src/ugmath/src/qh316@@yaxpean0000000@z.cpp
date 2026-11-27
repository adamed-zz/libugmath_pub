





extern void h019(const double* p, const double* d, const double* q, double* out);

static const double kNegOne316[2] = {-1.0, -1.0};

void h316(double* a1, double* a2, double* a3, double* a4,
          double* a5, double* a6, double* a7, double* a8)
{
    double v10 = a3[1] - a1[1];
    double v11 = a3[2] - a1[2];
    double v14 = a4[1] * -1.0;
    double v19[2];
    double v20[3];
    v20[0] = *a3 - *a1;
    v20[1] = v10;
    v20[2] = v11;
    double v21[3];
    v21[0] = *a4 * kNegOne316[0];
    v21[1] = a4[1] * kNegOne316[1];
    v21[2] = a4[2] * -1.0;
    h019(a2, v21, v20, v19);
    *a5 = v19[0];
    *a6 = v19[1];
    double v15 = *a5 * a2[2] + a1[2];
    double v17 = *a5 * a2[1] + a1[1];
    *a7 = *a5 * *a2 + *a1;
    a7[1] = v17;
    a7[2] = v15;
    double v18 = *a6 * a4[1] + a3[1];
    v15 = *a6 * a4[2] + a3[2];
    *a8 = *a6 * *a4 + *a3;
    a8[1] = v18;
    a8[2] = v15;
}
