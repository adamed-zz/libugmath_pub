



































void* SM_alloc(size_t n);
void* SM_calloc(size_t n, size_t m);
void  SM_free(void* p);

void h0926a2(const int* a1, const double* a2, const double* a3, const double* a4,
             const double* a5, const int* a6, const double* a7, double** a8, double* a9);
void bandec(double** a, int n, int m1, int m2, double** al, int* indx, double* d);
void banbks(double** a, int n, int m1, int m2, double** al, int* indx, double* b);
#include <cstring>

int h0913a2(const int* a1, const double* a2, const double* a3, const double* a4,
            const int* a5, const double* a6, const double* a7, double* a8)
{
    const int v10 = a1[1];
    int v14 = v10 - 1;
    int v15 = a1[0] + a1[4] + a1[5] + a1[6];
    const int v16 = a1[3];
    const int v52 = a1[2];
    int v57 = v10 - 1;
    if (v52 == 1)
    {
        if (a1[7] + 1 <= v14)
            v14 = a1[7] + 1;
        v15 += v14;
        v57 = 2 * v10 - 2;
    }
    const int v17 = v15;
    const size_t v17u = (size_t)(long long)v17;
    const size_t v18 = v17u * 8;

    double** v53 = (double**)SM_alloc(v18);
    if (v17 > 0)
    {
        for (int i = 0; i < v17; ++i)
            v53[i] = (double*)SM_calloc((size_t)(long long)(2 * v57 + 1), 8);
    }
    double* v55 = (double*)SM_alloc(v18);
    const int nz = v16 * v15;
    if (nz > 0)
        memset(a8, 0, (size_t)((long long)nz * 8));

    h0926a2(a1, a2, a7, a3, a4, a5, a6, v53, a8);

    double** v54 = (double**)SM_alloc(v18);
    const int v23 = v57;
    if (v17 > 0)
    {
        for (int j = 0; j < v17; ++j)
            v54[j] = (double*)SM_calloc((size_t)v57, 8);
    }
    int* v58 = (int*)SM_alloc(v17u * 4);
    double v56[9] = {};
    bandec(v53, v15, v23, v23, v54, v58, v56);

    for (int k = 0; k < v16; ++k)
    {
        for (int t = 0; t < v17; ++t)
            v55[t] = a8[k + v16 * t];

        banbks(v53, v15, v23, v23, v54, v58, v55);

        for (int t = 0; t < v17; ++t)
        {
            int row;
            if (v52 == 1)
                row = (t & 1) ? (v15 - (t + 1) / 2) : (t / 2);
            else
                row = t;
            a8[k + v16 * row] = v55[t];
        }
    }

    int v48 = 0;
    if (v16 == 4 && v17 > 0)
    {


        const double* v46 = a8 + 3;
        int v47 = 0;
        while (!(1e-7 > *v46))
        {
            ++v47;
            v46 += 4;
            if (v47 >= v17)
                goto frees;
        }
        v48 = 1;
    }
frees:
    SM_free(v55);
    SM_free(v58);
    if (v17 > 0)
    {
        for (int i = 0; i < v17; ++i)
        {
            SM_free(v54[i]);
            SM_free(v53[i]);
        }
    }
    SM_free(v54);
    SM_free(v53);
    return v48;
}
