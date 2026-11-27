






void h805(const double* a1, const double* a2, const int* a3, int* a4);
void h000(double* a1);

namespace {
const double kOne = 1.0;
const int kModeOne = 1;
}

void h705(const int* a1, const double* a2, const double* a3, const double* a4, const double* a5,
          double* a6)
{
    double* v8 = a6;
    double v10 = *a4;
    double v11 = a4[1];
    double v12 = a5[1];
    double v13 = *a3 - *a2;
    double v14 = a3[1] - a2[1];
    double v15 = a5[0];
    double v18s = v14 * v14 + v13 * v13;
    h000(&v18s);
    double v18 = ((v15 - v10) * v13 + (v12 - v11) * v14) / v18s;
    int st;
    h805(&v18, &kOne, &kModeOne, &st);
    double v17;
    if (st)
    {
        *v8 = v15;
        v17 = v12;
    }
    else
    {
        double v16 = v18 / (v18 - 1.0);
        *v8 = v16 * *a3 + (1.0 - v16) * v15;
        v17 = v16 * a3[1] + (1.0 - v16) * v12;
    }
    v8[1] = v17;
    if (*a1)
    {
        *v8 = *a3 * 0.8 + *v8 * 0.2;
        v8[1] = a3[1] * 0.8 + v17 * 0.2;
    }
}
