












__declspec(dllimport) void* __cdecl SM_alloc(unsigned __int64 size);
__declspec(dllimport) void __cdecl SM_free(void* p);


int __cdecl ludcmp_a(double** a, int n, int* indx, double* d);
int __cdecl ludcmp_a_with_abort(double** a, int n, int* indx, double* d,
                                bool (__cdecl* abort)(void));
void __cdecl lubksb_a(double** a, int n, int* indx, double* b);

int __cdecl SOLVE_lu_solver_with_abort(double** a1, double** a2, int a3, int a4,
                                       bool (__cdecl* a5)(void))
{
    double d[2];
    int indx[16];
    double work[16];
    int* ipiv = indx;
    double* x = work;

    if (a3 > 16)
    {
        ipiv = (int*)SM_alloc(4 * (__int64)a3);
        x = (double*)SM_alloc(8 * (__int64)a3);
    }

    int rc = a5 ? ludcmp_a_with_abort(a1, a3, ipiv, d, a5)
                : ludcmp_a(a1, a3, ipiv, d);
    if (rc)
    {
        if (a3 > 16)
        {
            SM_free(ipiv);
            SM_free(x);
        }
        return rc;
    }

    for (int i = 0; i < a4; ++i)
    {
        for (int k = 0; k < a3; ++k)
            x[k] = a2[k][i];
        lubksb_a(a1, a3, ipiv, x);
        for (int k = 0; k < a3; ++k)
            a2[k][i] = x[k];
    }

    if (a3 > 16)
    {
        SM_free(ipiv);
        SM_free(x);
    }
    return 0;
}
