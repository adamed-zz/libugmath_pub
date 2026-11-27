





#include <cstdint>


__declspec(dllimport) void* __cdecl SM_alloc(unsigned __int64 size);
__declspec(dllimport) void __cdecl SM_free(void* ptr);


extern void SOLVE_svd_decompose(double** a, int m, int n, double* s, double** v);
extern void sub_1800AFB80(double** a, double* s, double** v, int m, int n,
                          int* rank, double* u, double* vt, double tol);

void __cdecl SOLVE_svd_solver(double** a1, int a2, int* a3, double* const a4, double* const a5)
{
    double* s = (double*)SM_alloc(8LL * *a3);
    __int64 n = *a3;
    double** rows = (double**)SM_alloc(8 * n);
    if (n > 0)
    {
        for (__int64 i = 0; i < n; ++i)
            rows[i] = (double*)SM_alloc(8 * n);
    }
    int j = 0;
    if (*a3 > 0)
    {
        __int64 off = 0;
        do
        {
            s[off] = 0.0;
            for (int i = 0; i < *a3; ++i)
                rows[i][off] = 0.0;
            ++j;
            ++off;
        } while (j < *a3);
    }
    SOLVE_svd_decompose(a1, a2, *a3, s, rows);
    int rank;
    sub_1800AFB80(a1, s, rows, a2, *a3, &rank, a4, a5, 1e-8);
    SM_free(s);
    __int64 n2 = *a3;
    if (n2 > 0)
    {
        for (__int64 i = 0; i < n2; ++i)
            SM_free(rows[i]);
    }
    SM_free(rows);
    *a3 = rank;
}
