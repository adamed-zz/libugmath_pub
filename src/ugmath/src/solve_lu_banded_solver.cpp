












__declspec(dllimport) void* __cdecl SM_alloc(unsigned __int64 size);
__declspec(dllimport) void* __cdecl SM_calloc(unsigned __int64 count, unsigned __int64 size);
__declspec(dllimport) void __cdecl SM_free(void* p);


void __cdecl bandec(double** a, int n, int m1, int m2, double** al, int* indx, double* d);
void __cdecl banbks(double** a, int n, int m1, int m2, double** al, int* indx, double* b);

int __cdecl SOLVE_lu_banded_solver(double** a1, double** a2, int a3, int a4, int a5, int a6)
{
    int i, j;
    double d[2];
    double** al = (double**)SM_alloc(8 * (__int64)a3);
    for (i = 0; i < a3; ++i)
        al[i] = (double*)SM_calloc(a5, 8);
    int* indx = (int*)SM_alloc(4 * (__int64)a3);
    double* work = (double*)SM_alloc(8 * (__int64)a3);

    bandec(a1, a3, a5, a6, al, indx, d);
    for (j = 0; j < a4; ++j)
    {
        for (i = 0; i < a3; ++i)
            work[i] = a2[i][j];
        banbks(a1, a3, a5, a6, al, indx, work);
        for (i = 0; i < a3; ++i)
            a2[i][j] = work[i];
    }

    SM_free(work);
    SM_free(indx);
    for (i = 0; i < a3; ++i)
        SM_free(al[i]);
    SM_free(al);
    return 0;
}
