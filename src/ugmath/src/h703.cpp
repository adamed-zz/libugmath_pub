






void h804(double* a1, const double* a2, const int* a3, int* a4);
int eqz(const double* a1, const double* a2, const int* a3);

namespace {
const double kZero = 0.0;
const int kModeZero = 0;
}

void h703(double* a1, const double* a2, const double* a3, int* a4)
{
    *a4 = 1;
    double v18[2];
    long long v4 = (const char*)a1 - (const char*)v18;
    const double* v5 = v18;
    long long v17 = (const char*)a1 - (const char*)v18;
    double* v6 = a1 + 1;
    long long v7 = 2;
    long long v16 = (const char*)v18 - (const char*)a1;
    const double* v9 = a3;
    double* v10 = a1;
    long long v11 = 2;
    int v22;

    do
    {
        long long v12 = v7 - 1;
        h804((double*)((const char*)v5 + v4), v9, &kModeZero, &v22);
        int mode = 0;
        if (v22 == 1)
        {
            mode = 1;
        }
        else if (v22 == 3)
        {
            mode = 2;
        }
        else if (v22 == 5)
        {
            v12 = v7;
            mode = 1;
        }
        if (mode == 1)
        {
            *a4 = 3;
            double v13 = a2[1] - a1[1];
            v18[0] = *a2 - *a1;
            double v14 = a3[v12 - 1];
            v18[1] = v13;
            double v15 = v14 - *v10;
            *v10 = v14;
            if (!eqz(v5, &kZero, &kModeZero))
                *v6 = v15 * *(const double*)((const char*)v6 + v16) /
                          *(const double*)((const char*)v10 + v16) + *v6;
        }
        else if (mode == 0)
        {
            if (*a4 != 3)
                *a4 = 2;
        }
        v4 = v17;
        v9 += 2;
        ++v5;
        v7 += 2;
        ++v10;
        --v6;
        --v11;
    } while (v11);
}
