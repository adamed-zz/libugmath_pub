






int h670(const double* a1, const double* a2)
{
    int v2 = 0;
    const double* v3 = a1 + 1;
    long long v4 = 0;
    long long v5 = (const char*)a2 - (const char*)a1;

LABEL_2:
    v2 += 2;
    int v7 = 0;
    if (v4 != 4)
        v7 = v2;
    long long v8;
    if (v7 == 4)
    {
        v8 = 0;
    }
    else
    {
        v8 = 2;
        if (v4 != 4)
            v8 = v4 + 4;
    }
    long long v9 = 1;
    const double* v10 = a1;
    if (v4 != 4)
    {
        v9 = v4 + 3;
        v10 = v3 + 1;
    }
    double v11 = a1[v9] - a1[v8 + 1];
    double v12 = a1[v8] - *v10;
    double v13 = -(v12 * a1[v9] + *v10 * v11);
    if (v11 * *(v3 - 1) + v12 * *v3 - (v12 * a1[v9] + *v10 * v11) < 0.0)
    {
        v11 = -v11;
        v12 = -v12;
        v13 = -v13;
    }
    for (long long i = 0; i < 6; i += 2)
    {
        if (v11 * a2[i] + v12 * a2[i + 1] + v13 >= 0.0)
        {
            double v15 = a2[v9] - a2[v8 + 1];
            const double* v16 = a2;
            if (v4 != 4)
                v16 = (const double*)((const char*)v3 + v5 + 8);
            double v17 = a2[v8] - *v16;
            double v18 = -(a2[v9] * v17 + *v16 * v15);
            if (v17 * *(const double*)((const char*)v3 + v5) +
                    v15 * *(const double*)((const char*)v3 + v5 - 8) -
                    (a2[v9] * v17 + *v16 * v15) <
                0.0)
            {
                v15 = -v15;
                v17 = -v17;
                v18 = -v18;
            }
            for (long long j = 0; j < 6; j += 2)
            {
                if (v17 * a1[j + 1] + v15 * a1[j] + v18 >= 0.0)
                {
                    v4 += 2;
                    v3 += 2;
                    if (v4 < 6)
                        goto LABEL_2;
                    return 1;
                }
            }
            return 0;
        }
    }
    return 0;
}
