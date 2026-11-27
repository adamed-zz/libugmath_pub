






void vunt3(const double* a1, int* a2, double* a3);
void h636(const double* a1, const double* a2, const double* a3, int* a4, double* a5);

void h635(const double* a1, const double* a2, const double* a3, const double* a4,
          int* a5, double* a6)
{
    int st;
    double v13[3];
    double v11[3];
    double v14[4];

    vunt3(a2, &st, v13);
    vunt3(a4, &st, v11);
    v14[0] = v11[0];
    v14[1] = v11[1];
    v14[2] = v11[2];
    v14[3] = v11[1] * a3[1] + v11[0] * a3[0] + v11[2] * a3[2];
    h636(a1, v13, v14, a5, a6);
}
