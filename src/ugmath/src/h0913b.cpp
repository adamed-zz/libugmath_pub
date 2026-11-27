

















#pragma once
#include <cstddef>


void* SM_alloc(size_t n);
void* SM_alloc(size_t n, size_t m);
void* SM_calloc(size_t n, size_t m);
void  SM_free(void* p);


int  ext_merrorlevel();
void ext_merrorflush();
void ext_msetup_banded(int n, int m, double*** a, double** b);
void ext_mdecompose_banded(double** a, int n, int m);
void ext_msolve_banded(double** a, int n, int m, double* b);
void ext_mdispose_banded(double*** a, double** b);
void ext_bandec(double** a, int n, int m1, int m2, double** al, int* indx, double* d);
void ext_banbks(double** a, int n, int m1, int m2, double** al, int* indx, double* b);
int  ext_SOLVE_lu_solver(double** a, double** b, int n, int m);
int  ext_knot_seq_order_4(const int* a1, const double* a3, const double* a4, int* a7, double* a8);
void ext_h0926a2(const int* a1, const double* a2, const double* a3, const double* a4,
                 const double* a5, const int* a6, const double* a7, double** a8, double* a9);
void ext_h0926a(const int* a1, const double* a2, const double* a3, const double* a4,
                const double* a5, const int* a6, const double* a7, double** a8, double* a9);
void ext_h0926(const int* a1, const double* a2, const double* a3, const double* a4,
               const int* a5, double* a6);
int  ext_h0914(const int* a1, const double* a2, const double* a3, int* a4, double* a5);
void ext_h0927(const int* a1, const double* a2, const double* a3, double* a4);
void ext_h805(const double* a1, const double* a2, const int* a3, int* a4);
int  ext_em0928(const int* a1, const int* a2, const double* a3);
double ext_h128(double a, double b);
int  ext_h553(const double* a1, const double* a2, const double* a3,
              const double* a4, const double* a5, const double* a6,
              const int* a7, double* a8);
void ext_e0925(int* a1, double* a2, double* a3, double* a4);
int  ext_eqz(const double* a, const double* b, const int* mode);


int  h0917(double x, const double* knots, int n, double tol);
int  h0918(double* x, const double* knots, int n, int m);
int  h0914(const int* a1, const double* a2, const double* a3, int* a4, double* a5);
int  h0913a(const int* a1, const double* a2, const double* a3, const double* a4,
            const int* a5, const double* a6, const double* a7, double* a8);
int  h0913b(const int* a1, const double* a2, const double* a3, const double* a4,
            const int* a5, const double* a6, const double* a7, double* a8);
void h0926(const int* a1, const double* a2, const double* a3, const double* a4,
           const int* a5, double* a6);
void h0926a(const int* a1, const double* a2, const double* a3, const double* a4,
            const double* a5, const int* a6, const double* a7, double** a8, double* a9);
int  h0916(int a1, const double* a2, int a3, int a4, double a5, int a6, double* const a7);
int  h0913(const int* a1, const double* a2, const double* a3, const double* a4,
           const int* a5, const double* a6, int* a7, double* a8, double* a9);
int  h0925(const int* a1, const double* a2, const double* a3, int* a4, double* a5, double* a6);
int  h0925_chk(int a1, double* a2, const double* a3);


extern "C" void* g_b6_raw_base;



int h0913a(const int* a1, const double* a2, const double* a3, const double* a4,
           const int* a5, const double* a6, const double* a7, double* a8);

int h0913b(const int* a1, const double* a2, const double* a3, const double* a4,
           const int* a5, const double* a6, const double* a7, double* a8)
{
    const int periodic = a1[2];
    const int n = a1[0];
    const int count = a1[1];
    const int stride = a1[3];
    const int v16 = a1[4];
    const int v17 = a1[5];
    const int v18 = a1[6];
    int clamped = count - 1;
    int total;

    if (periodic)
    {
        if (a1[7] + 1 <= clamped)
            clamped = a1[7] + 1;
        total = v18 + v17 + v16 + n + clamped;
    }
    else
    {
        total = v18 + v17 + n + v16;
        if (!v17 && !v18)
        {
            int params[8];
            params[2] = 0;
            params[6] = a1[7];
            params[1] = count;
            params[5] = 0;
            params[0] = n;
            params[3] = stride;
            params[4] = v16;
            return h0913a(params, a2, a3, a4, a5, a6, a7, a8);
        }
    }

    double* mat = (double*)SM_calloc((size_t)total * (size_t)total, 8u);
    ext_h0926(a1, a7, a3, a4, a5, mat);
    ext_h0927(a1, a2, a6, a8);
    double** rows = (double**)SM_alloc(8ull * (size_t)total);
    double** cols = (double**)SM_alloc(8ull * (size_t)total);
    *rows = mat;
    if (total <= 1)
    {
        *cols = a8;
    }
    else
    {
        for (int i = 1; i < total; ++i)
            rows[i] = rows[i - 1] + total;
        *cols = a8;
        for (int i = 1; i < total; ++i)
            cols[i] = cols[i - 1] + stride;
    }
    const unsigned int rc = (unsigned int)ext_SOLVE_lu_solver(rows, cols, total, stride);
    SM_free(mat);
    SM_free(rows);
    SM_free(cols);
    return (int)rc;
}
