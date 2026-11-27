















#include <cstring>


double** NR_2d_matrix_allo(int, int, double**);
void NR_cholesky_decomp(int, double*, double* const, int*);
void NR_cholesky_inverse(int, double* const, double*);
void NR_matrix_2d_as_1d_init_zero_ut(double*, int);
void NR_matrix_2d_as_1d_product_of_2(double*, double*, int, int, int, double*);
void NR_matrix_2d_as_1d_nxn_transp(double*, int);
void NR_2d_matrix_nxn_transp(double**, int);
void NR_ask_eigenvalues_jacobi(double**, int, int, double* const, double**, int*);
int SOLVE_lu_solver(double**, double**, int, int);


__declspec(dllimport) void SM_free(void*);
__declspec(dllimport) void ERROR_internal(const char*, int, const char*, ...);

void NR_generalized_eigenvalues_symm(double* a1, double* a2, int n, int a4,
                                     double* const a5, double* a6, int* a7, int* a8)
{
    double* st1 = 0;
    double* st2 = 0;
    double** m1;
    double** m2;
    double** m3;
    int i;
    int j;

    *a8 = 0;
    NR_cholesky_decomp(n, a2, a5, a8);
    if (*a8 == 1)
        return;

    m1 = NR_2d_matrix_allo(n, n, &st1);
    m2 = NR_2d_matrix_allo(n, n, &st2);
    m3 = NR_2d_matrix_allo(n, n, &a6);



    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++)
            m2[i][j] = 0.0;
        for (j = 0; j < i; j++)
            m2[i][j] = a2[i * n + j];
        m2[i][i] = a5[i];
    }

    NR_cholesky_inverse(n, a5, a2);
    NR_matrix_2d_as_1d_init_zero_ut(a2, n);
    NR_matrix_2d_as_1d_product_of_2(a2, a1, n, n, n, a6);
    NR_matrix_2d_as_1d_nxn_transp(a2, n);
    NR_matrix_2d_as_1d_product_of_2(a6, a2, n, n, n, st1);
    NR_ask_eigenvalues_jacobi(m1, n, a4, a5, m3, a7);
    NR_2d_matrix_nxn_transp(m2, n);
    if (SOLVE_lu_solver(m2, m3, n, n)) {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\nr_eigensystems.c",
                       427,
                       "The third call of SOLVE_lu_solver failed.");
        __debugbreak();
    }

    if (st1)
        SM_free(st1);
    if (m1)
        SM_free(m1);
    if (st2)
        SM_free(st2);
    if (m2)
        SM_free(m2);
    if (m3)
        SM_free(m3);
}
