














int __cdecl ludcmp_a_with_abort(double **a, int n, int *indx, double *work,
                                bool (__cdecl *abort_fn)(void));

int __cdecl ludcmp_a(double **a, int n, int *indx, double *work)
{
    return ludcmp_a_with_abort(a, n, indx, work, 0);
}
