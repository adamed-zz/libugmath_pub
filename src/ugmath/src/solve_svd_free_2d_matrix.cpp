















__declspec(dllimport) void __cdecl SM_free(void* ptr);

void SOLVE_svd_free_2d_matrix(double** a, int n)
{
    for (int i = n - 1; i >= 0; i--)
        SM_free(a[i]);
    SM_free(a);
}
