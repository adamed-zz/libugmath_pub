







__declspec(dllimport) void *__cdecl SM_alloc(unsigned __int64 a1);
__declspec(dllimport) void __cdecl SM_free(void *a1);


void SOLVE_svd_decompose(double **a, int m, int n, double *w, double **v);
void sub_1800AFB80(double **a, double *w, double **v, int m, int n, int *nsv,
                   double *u, double *vt, double tol);

void SOLVE_svd_solver_r(double **a1, int a2, int *a3, double *const a4,
                        double *const a5, double a6)
{
    double **v6 = a1;
    double *v9 = (double *)SM_alloc(8LL * *a3);
    __int64 v10 = *a3;
    double *v11 = v9;
    double **v13 = (double **)SM_alloc(8 * v10);
    if (v10 > 0)
    {
        for (__int64 i = 0; i < v10; ++i)
            v13[i] = (double *)SM_alloc(8 * v10);
        v6 = a1;
    }
    int v15 = *a3;
    int v16 = 0;
    if (*a3 > 0)
    {
        __int64 v17 = 0;
        do
        {
            v11[v17] = 0.0;
            int v18 = 0;
            v15 = *a3;
            if (*a3 > 0)
            {
                double **v19 = v13;
                do
                {
                    __int64 v20 = (__int64)*v19++;
                    ++v18;
                    *(__int64 *)(v17 * 8 + v20) = 0;
                    v15 = *a3;
                } while (v18 < *a3);
            }
            ++v16;
            ++v17;
        } while (v16 < v15);
    }
    int v23;
    SOLVE_svd_decompose(v6, a2, v15, v11, v13);
    sub_1800AFB80(v6, v11, v13, a2, *a3, &v23, a4, a5, a6);
    SM_free(v11);
    __int64 v21 = *a3;
    if (v21 > 0)
    {
        for (__int64 v12 = 0; v12 < v21; ++v12)
            SM_free(v13[v12]);
    }
    SM_free(v13);
    *a3 = v23;
}
