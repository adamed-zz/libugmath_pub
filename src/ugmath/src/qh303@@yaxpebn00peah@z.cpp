





extern void h300(const double* a, const double* b, double* out);

void h303(const double* a1, const double* a2, const double* a3, int* a4)
{
    double v10;
    double v11;
    h300(a1, a3, &v10);
    h300(a2, a3, &v11);
    double v7 = v10;
    double v8 = v11;

    bool v9 = !(v10 > v11);
    *a4 = 1;
    if (!v9)
        *a4 = 2;
    if (v8 == v7)
        *a4 = 3;
}
