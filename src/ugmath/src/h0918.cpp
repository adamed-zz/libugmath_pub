







int h0917(double a1, const double* a2, int a3, double a4);

int h0918(double* a1, const double* a2, int a3, int a4)
{
    int result = h0917(*a1, a2, a3, 1.0e-12);
    if (a4 - 1 > result)
        return -1;
    int v9 = a3 - a4;
    if (result > v9 - 1)
        return -1;
    double v10 = a2[a4 - 1];
    double v11 = *a1;
    if (v10 - 1.0e-12 > v11)
        return -1;
    double v12 = a2[v9];
    if (v11 > v12 + 1.0e-12)
        return -1;
    if (v10 >= v11)
    {
        *a1 = v10;
        v11 = v10;
    }
    if (v11 >= v12)
        *a1 = v12 - 5.0e-13;
    return result;
}
