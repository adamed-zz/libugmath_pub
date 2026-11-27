
















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
           const int* a5, const double* a6, const double* a7, double* a8)
{
    const int n = a1[0] + a1[4] + a1[5];
    const int w = a1[3];
    const int m = a1[1] - 1;
    int result = 0;
    double** mat = nullptr;
    double* vec = nullptr;

    ext_msetup_banded(n, m, &mat, &vec);
    if (ext_merrorlevel())
    {
        result = -1;
        ext_merrorflush();
        ext_mdispose_banded(&mat, &vec);
        return result;
    }

    ext_h0926a(a1, a2, a7, a3, a4, a5, a6, mat, a8);
    ext_mdecompose_banded(mat, n, m);
    if (ext_merrorlevel())
    {
        ext_merrorflush();
        result = 1;
        ext_mdispose_banded(&mat, &vec);
        return result;
    }

    if (w > 0)
    {
        for (int row = 0; row < w; ++row)
        {
            for (int k = 0; k < n; ++k)
                vec[k] = a8[row + w * k];
            ext_msolve_banded(mat, n, m, vec);
            if (ext_merrorlevel())
            {
                result = 1;
                ext_merrorflush();
                ext_mdispose_banded(&mat, &vec);
                return result;
            }
            for (int k = 0; k < n; ++k)
                a8[row + w * k] = vec[k];
        }
    }

    if (w == 4 && n > 0)
    {
        int i = 0;
        while (a8[4 * i + 3] >= 0.0)
        {
            ++i;
            if (i >= n)
                break;
        }
        if (i < n)
            result = 1;
    }

    ext_mdispose_banded(&mat, &vec);
    return result;
}
