






void h100(const double* a1, const double* a2, double* a3);
void h641(const double* a1, const double* a2, const double* a3, const double* a4,
          const double* a5, int* a6, int* a7, double* a8);
void h922(const double* a1, double* a2);
void vunt3(const double* a1, int* a2, double* a3);

namespace {
const double kOne = 1.0;
}

void h642(const double* a1, const double* a2, const double* a3, const double* a4,
          const double* a5, const double* a6, const double* a7, const double* a8,
          int* a9, int* a10, double* a11)
{
    double v25[3];
    double v23[3];
    double v27[4];
    double v28[20];

    h100(a1, a3, v25);
    h100(a2, a3, v23);
    double v14 = *a4;
    double v15 = a4[1];
    v27[2] = a4[2];
    double v16 = *a7;
    double v17 = *a8;
    double v18 = *a8 * v25[0];
    double v19 = *a8 * v23[0];
    double v20 = *a5;
    double v21 = *a6;
    double v30 = 1.0;

    v27[0] = (v15 * v17 + v14 * v16) / v20;
    v27[1] = (v15 * v16 - v14 * v17) / v21;
    v25[0] = (v17 * v25[1] + v16 * v25[0]) / v20;
    v25[1] = (v16 * v25[1] - v18) / v21;
    double v22 = (v17 * v23[1] + v16 * v23[0]) * v20;
    v23[1] = (v16 * v23[1] - v19) * v21;
    v23[0] = v22;
    int v29;
    vunt3(v23, &v29, v23);
    h922(&kOne, v28);
    h641(v25, v23, v28, v27, &v30, a9, a10, a11);
}
