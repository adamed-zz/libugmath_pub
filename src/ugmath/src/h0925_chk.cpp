















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


int h0925_chk(int a1, double* a2, const double* a3)
{
    const long long n = a1;

    const double d1 = *(volatile const double*)(a3 + 1);
    const long long dir = (d1 <= a3[0]) ? -1 : 1;
    int bad = 0;

    if (n > 2)
    {
        long long idx = 2;
        const double* p = a3 + 3;
        if (n >= 6)
        {
            do
            {
                if (bad)
                    break;
                const double pm1 = p[-1];
                const double pm2 = p[-2];
                if (dir == -1)
                {
                    if (pm1 >= pm2)
                    {
                        bad = 1;
                        break;
                    }
                    if (p[0] >= pm1)
                    {
                        bad = 1;
                        break;
                    }
                    const double v13 = p[1];
                    if (v13 >= p[0])
                    {
                        bad = 1;
                        break;
                    }
                    if (p[2] >= v13)
                        bad = 1;
                }
                else
                {
                    if (pm2 >= pm1)
                    {
                        bad = 1;
                        break;
                    }
                    if (pm1 >= p[0])
                    {
                        bad = 1;
                        break;
                    }
                    const double v14 = p[1];
                    if (p[0] >= v14)
                    {
                        bad = 1;
                        break;
                    }
                    bad = (v14 >= p[2]);
                }
                idx += 4;
                p += 4;
            } while (idx < n - 3);
        }
        while (!bad && idx < n)
        {
            const double cur = a3[idx];
            const double prev = a3[idx - 1];
            if (dir == -1)
            {
                if (cur >= prev)
                    bad = 1;
            }
            else
            {
                bad = (prev >= cur);
            }
            ++idx;
        }
        if (!bad)
            return 0;

        const int cnt = (int)(n - 1);
        int mode = 2;
        double* seg = (double*)SM_alloc(32ull * (size_t)cnt);
        double prev = a3[0];
        for (long long k = 1; k < n; ++k)
        {
            const double cur = a3[k];
            const double d = cur - prev;
            prev = cur;
            double* q = seg + 4 * (k - 1);
            q[0] = d + d;
            q[1] = 0.0;
            q[2] = 0.0;
            q[3] = 1.0;
        }

        int rc = 0;
        const int limit = cnt - 2;
        for (int i = 0; i < limit; ++i)
        {
            if (rc)
                break;
            double out[12];
            ext_e0925(&mode, a2 + i + 1, seg + 4 * i, out);
            if (!(out[8] * out[0] <= 0.0))
            {
                rc = 0;
                if (!(out[4] * out[0] >= 0.0))
                    rc = (out[4] * out[4] >= out[8] * out[0]) ? 1 : 0;
            }
            else
            {
                rc = 1;
            }
        }
        return rc;
    }
    return 0;
}
