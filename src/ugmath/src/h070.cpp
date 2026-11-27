









void h070(const double* a1, double* a2)
{
    double v2;
    double v3;
    if (*a2 > *a1)
        *a2 = *a1;
    v2 = a1[1];
    if (a2[1] > v2)
        a2[1] = v2;
    if (*a1 > a2[2])
        a2[2] = *a1;
    v3 = a1[1];
    if (v3 > a2[3])
        a2[3] = v3;
}
