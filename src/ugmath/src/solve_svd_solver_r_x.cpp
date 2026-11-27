









__declspec(dllimport) void* __cdecl SM_alloc(unsigned __int64);
__declspec(dllimport) void* __cdecl SM_calloc(unsigned __int64, unsigned __int64);
__declspec(dllimport) void __cdecl SM_free(void*);

extern void SOLVE_svd_decompose(double** a1, int a2, int a3, double* a4, double** a5);
extern void sub_1800AFE80(double** a1, double* a2, double** a3, int a4, int a5,
                          int* a6, int a7, double** a8, double** a9, double a10);

void SOLVE_svd_solver_r_x(double** a1, int a2, int* a3, int a4, double** a5,
                          double** a6, double a7)
{
    double* s = (double*)SM_calloc(*a3, 8u);
    __int64 n = *a3;
    double** v = (double**)SM_alloc(8 * n);
    __int64 k = 0;
    if (n > 0)
    {
        for (__int64 i = 0; i < n; ++i)
            v[i] = (double*)SM_alloc(8 * n);
    }
    for (int i = 0; i < *a3; ++i)
    {
        s[i] = 0.0;
        for (int j = 0; j < *a3; ++j)
            v[j][i] = 0.0;
    }
    SOLVE_svd_decompose(a1, a2, *a3, s, v);
    int out;
    sub_1800AFE80(a1, s, v, a2, *a3, &out, a4, a5, a6, a7);
    SM_free(s);
    __int64 m = *a3;
    if (m > 0)
    {
        for (k = 0; k < m; ++k)
            SM_free(v[k]);
    }
    SM_free(v);
    *a3 = out;
}
