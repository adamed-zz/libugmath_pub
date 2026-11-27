




void h004(const double* a1, const double* a2, const double* a3, double* a4);
void h805(const double* a1, const double* a2, const int* a3, int* a4);
void vcru3(const double* a1, const double* a2, int* a3, double* a4);

void fe358(int* a1, double* a2, int* a3) {
    static const double kZero = 0.0;
    static const int kSel = 0;
    double v17[3];
    double v16[3];
    double v18[3];
    double v19[4];
    double v21;
    int v20;
    *a3 = 0;
    v17[0] = a2[3] - a2[0];
    v17[1] = a2[4] - a2[1];
    v17[2] = a2[5] - a2[2];
    v16[0] = a2[6] - a2[0];
    v16[1] = a2[7] - a2[1];
    v16[2] = a2[8] - a2[2];
    switch (*a1 - 2) {
    case 2:
        v18[0] = a2[9] - a2[0];
        v18[1] = a2[10] - a2[1];
        v18[2] = a2[11] - a2[2];
        h004(v17, v16, v18, &v21);
        h805(&v21, &kZero, &kSel, &v20);
        if (v20 == 1) *a3 = 2;
        break;
    case 1:
    default:
        vcru3(v17, v16, a3, v19);
        *a3 = 1 - *a3;
        break;
    }
}
