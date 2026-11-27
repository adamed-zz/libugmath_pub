
















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



int h0913b(const int* a1, const double* a2, const double* a3, const double* a4,
           const int* a5, const double* a6, const double* a7, double* a8);

int h0925(const int* a1, const double* a2, const double* a3, int* a4,
          double* a5, double* a6)
{
    const int n = a1[0];
    int params[8];
    double p1[3];
    double p2[3];
    double p3[4];
    double slopes[2];
    double tanv[3];
    double a4data[7];
    int mode_first = 1;
    int mode_last = 3;
    int modes[2];

    params[0] = n;
    params[1] = 4;
    params[2] = 0;
    params[3] = 1;
    params[4] = 2;
    params[5] = 0;
    params[6] = 0;
    params[7] = 2;

    a4data[0] = 0.0;
    a4data[1] = 1.0;
    a4data[2] = -5.0e-13;

    modes[0] = 1;
    modes[1] = 1;

    *a4 = n + 2;

    p2[0] = a2[1];
    p3[1] = 0.0;
    p2[1] = 0.0;
    p1[1] = 0.0;
    p3[2] = 0.0;
    p2[2] = 0.0;
    p1[2] = 0.0;
    p1[0] = a2[0];
    p3[0] = a2[2];

    ext_h553(p1, p2, p3, a3, a3 + 1, a3 + 2, &mode_first, tanv);
    slopes[0] = tanv[0];

    const int k = n - 3;
    p1[0] = a2[k];
    p2[0] = a2[k + 1];
    p3[0] = a2[k + 2];
    ext_h553(p1, p2, p3, &a3[k], &a3[k + 1], &a3[k + 2], &mode_last, tanv);
    slopes[1] = tanv[0];

    a6[0] = 0.0;
    a6[1] = 0.0;
    a6[2] = 0.0;
    int w = 3;
    for (int i = 0; i < n; ++i)
    {
        a6[w] = a3[i];
        ++w;
    }
    a6[w] = 1.0;
    a6[w + 1] = 1.0;
    a6[w + 2] = 1.0;

    return h0913b(params, a2, a3, a4data, modes, slopes, a6, a5);
}
