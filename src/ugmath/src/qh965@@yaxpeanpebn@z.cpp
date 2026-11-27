






void b15_MTX3_multiply(const double* a1, const double* a2, double* a3);

static void h100(const double* a1, const double* a2, double* a3)
{
    double x = a1[0];
    double y = a1[1];
    double z = a1[2];
    a3[0] = y * a2[1] + x * a2[0] + z * a2[2];
    a3[1] = x * a2[3] + y * a2[4] + z * a2[5];
    a3[2] = x * a2[6] + y * a2[7] + z * a2[8];
}


void h922(const double* a1, double* a2)
{
    double s = *a1;
    a2[0] = s;
    a2[1] = 0.0;
    a2[2] = 0.0;
    a2[3] = 0.0;
    a2[4] = s;
    a2[5] = 0.0;
    a2[6] = 0.0;
    a2[7] = 0.0;
    a2[8] = s;
}

void h965(double* a1, const double* a2)
{
    double v6[4];
    double v7[10];
    double v8[10];
    double v9;

    b15_MTX3_multiply(a1, a2, v8);
    v9 = 1.0 / a2[12];
    h922(&v9, v7);
    b15_MTX3_multiply(v8, v7, a1);
    h100(a1 + 9, a2, v6);
    a1[9] = v6[0] + a2[9];
    a1[10] = v6[1] + a2[10];
    a1[11] = v6[2] + a2[11];
}
