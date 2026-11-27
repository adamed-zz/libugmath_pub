






void h805(const double* a1, const double* a2, const int* a3, int* a4);
void h000(double* a1);

namespace {
const double kZero = 0.0;
const int kModeZero = 0;
}

void h701(const double* a1, const double* a2, const double* a3, int* a4, double* a5)
{
    *a4 = 1;
    double v6 = *a1;
    double v7 = *a2;
    double v8 = a3[3];
    double v9 = *a3;
    double v33 = a1[3];
    double v10 = a2[3];
    double v11 = a1[1];
    double v12 = a2[1];
    double v13 = a3[1];
    double v14 = a1[2];
    double v28 = v7;
    double v15 = a3[2];
    double v16 = a2[2];
    double v34 = v8;
    double v17 = v15 * v12 - v16 * v13;
    double v29 = v6;
    double v30 = v9;
    double v18 = v14 * v13 - v15 * v11;
    double v19 = v16 * v11 - v14 * v12;
    double v32 = v7 * v18 + v6 * v17 + v9 * v19;
    int v31;
    h805(&v32, &kZero, &kModeZero, &v31);
    if (v31)
    {
        *a4 = 2;
        h000(&v32);
    }
    double v20 = v33;
    double v21 = v32;
    double* v22 = a5;
    double v23 = v18 * v10 + v17 * v33;
    double v24 = v34;
    double v25 = v10 * v15 - v34 * v16;
    double v26 = v34 * v14 - v33 * v15;
    double v27 = v33 * v16 - v10 * v14;
    *a5 = (v23 + v19 * v34) / v32;
    v22[1] = (v26 * v28 + v25 * v29 + v27 * v30) / v21;
    v22[2] = ((v20 * v13 - v24 * v11) * v28 + (v24 * v12 - v10 * v13) * v29 +
              (v10 * v11 - v20 * v12) * v30) / v21;
}
