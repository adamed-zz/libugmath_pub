






void h000(double* a1);

void h702(double* a1, const double* a2, const double* a3, int* a4)
{
    double* v4 = a1;
    long long v5 = 1;
    *a4 = 1;
    double v17[2];
    double* v7 = v17;
    double* v8 = a1 + 1;
    long long v9 = (const char*)a3 - (const char*)v4;
    long long v10 = 2;
    double* v11 = v8;
    long long v12 = (const char*)v17 - (const char*)v4;

    do
    {


        bool c1 = *(const double*)((const char*)v4 + v9) > *v4;
        long long v13 = c1 ? v5 : v5 + 2;
        bool c2 = !(*(const double*)((const char*)v4 + v9 + 16) >= *v4);
        if (c1 || c2)
        {
            *a4 = 2;
            double v14 = a2[1] - *v8;
            v17[0] = *a2 - *a1;
            double v15 = a3[v13 - 1];
            v17[1] = v14;
            double v16 = v15 - *v4;
            *v4 = v15;
            h000(v7);
            v8 = a1 + 1;
            *v11 = v16 * *(const double*)((const char*)v11 + v12) /
                       *(const double*)((const char*)v4 + v12) + *v11;
        }
        ++v7;
        ++v5;
        ++v4;
        --v11;
        --v10;
    } while (v10);
}
