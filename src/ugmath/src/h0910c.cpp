



























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

#include <cmath>
#include <cstring>

void h0910c(const int* a1, const int* a2, int* a3, double* a4, int* a5)
{
    const int v5 = (int)*a3;
    double* const v6 = a4 - 1;
    const double v7 = a4[0];
    const double v14 = a4[v5 - 1] - v7;
    int v71 = 0;
    int v8 = 0;


    for (int i = 0; i < v5; ++i)
        v6[i + 1] = (v6[i + 1] - v7) / v14;


    double dzero = 0.0;
    double done = 1.0;
    int mode = 0;
    int v75 = 0;
    int v27 = 0;
    if (v5 >= 1)
    {
        const double* v11 = a4;
        for (int k = v5; k > 0; --k)
        {
            ext_h805(v11, &dzero, &mode, &v75);
            if (v75 == 1)
                ++v8;
            ext_h805(v11, &done, &mode, &v75);
            if (v75 == 1)
                ++v27;
            ++v11;
        }
    }


    const int v29 = std::abs(v27 - v8);
    if (v27 <= v8)
    {
        if (v27 < v8)
        {
            const int v37 = v5 + 1;
            const int hi = v5 + v29;
            if (v37 <= hi)
            {
                for (int i = v37; i <= hi; ++i)
                    v6[i] = 1.0;
            }
            *a3 = v5 + v29;
        }
    }
    else
    {
        const int v30 = v29 + v5;
        const int v31 = v29 + 1;
        if (v30 >= v31)
        {
            for (int i = v30; i >= v31; --i)
                v6[i] = v6[i - v29];
        }
        if (v29 >= 1)
            memset(a4, 0, 8ull * (unsigned long long)v29);
        *a3 += v29;
    }


    const int v38 = ext_em0928(a1, a2, a4);
    *a5 = v38;
    const int v41 = v38 + (int)*a3;
    {
        int v43 = v41;
        int v47 = v41;
        while (v43 >= v38 + 1)
        {
            v6[v43] = v6[v47 - *a5];
            --v43;
            --v47;
        }
    }
    *a3 += 2 * (*a5);


    {
        const int v48 = (int)*a3;
        int v50 = v48 - *a5 + 1;
        int v52 = v29 + *a5 + 2;
        while (v50 <= v48)
        {
            v6[v50] = v6[v52] + 1.0;
            ++v50;
            ++v52;
        }
    }


    {
        const int v59 = *a5;
        const int v61 = (int)*a3 - v59 - v29 - 1;
        int v67 = v61;
        for (int v60 = v59; v60 >= 1; --v60)
            v6[v60] = v6[v67--] - 1.0;
    }
}
