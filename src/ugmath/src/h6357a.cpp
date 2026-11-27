













void h6357b(const double* a1, const double* a2, const double* a3, const double* a4,
            int* a5, int* a6, double* a7);

void h6357a(const double* a1, const double* a2, const double* a3, int* a4, double* a5)
{
    double* v5 = a5;
    double v16[2];
    int st = 0;
    int st2 = 0;
    int v10 = 0;

    *a4 = 0;
    h6357b(a1, a2, a3, a3 + 3, &st, &st2, v5);
    if (!st)
        return;
    v10 = (st == 2);
    h6357b(a1, a2, a3, a3 + 6, &st, &st2, v16);
    if (!st)
        return;
    if (st == 2)
    {
        if (v10)
        {
            if (v16[0] > v5[1])
                return;
            if (v5[0] > v16[1])
                return;
            if (v16[0] > v5[0])
                v5[0] = v16[0];
            if (v5[1] > v16[1])
                v5[1] = v16[1];
        }
        else
        {
            v10 = 1;
            v5[0] = v16[0];
            v5[1] = v16[1];
        }
    }
    h6357b(a1, a2, a3, a3 + 9, &st, &st2, v16);
    if (!st)
        return;
    if (st != 2)
    {
        *a4 = 1;
        return;
    }
    if (!v10)
    {
        v5[0] = v16[0];
        v5[1] = v16[1];
        *a4 = 1;
        return;
    }
    if (v16[0] > v5[1])
        return;
    if (v5[0] > v16[1])
        return;
    if (v16[0] > v5[0])
        v5[0] = v16[0];
    if (v5[1] > v16[1])
        v5[1] = v16[1];
    *a4 = 1;
}
