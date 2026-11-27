








void h071(const double* a1, double* a2)
{
    double v2 = *a1;
    if (*a2 > *a1) {
        *a2 = v2;
        v2 = *a1;
    }
    if (v2 > a2[1])
        a2[1] = v2;
    double v3 = a1[1];
    if (a2[2] > v3) {
        a2[2] = v3;
        v3 = a1[1];
    }
    if (v3 > a2[3])
        a2[3] = v3;
    double v4 = a1[2];
    if (a2[4] > v4) {
        a2[4] = v4;
        v4 = a1[2];
    }
    if (v4 > a2[5])
        a2[5] = v4;
}
