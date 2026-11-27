








#include <intrin.h>
#include <math.h>
#include <stddef.h>

namespace UGS
{
namespace Math
{

struct Point2
{
    double x;
    double y;
};

struct Vector2
{
    double x;
    double y;
};

}
}


__declspec(dllimport) void* SM_alloc(size_t size);
__declspec(dllimport) void SM_free(void* p);


double** NR_2d_matrix_allo(int rows, int cols, double** storage);
void NR_2d_matrix_init_zero(double** m, int rows, int cols);
void NR_ask_eigenvalues_jacobi(double** A, int n, int max_iter, double* const eig, double** V,
                               int* ierr);
int VEC2_unitize(const UGS::Math::Vector2* v, double tol, double* mag, UGS::Math::Vector2* unit);



extern "C" void sub_180054C60(int n, UGS::Math::Point2* pts, double tol,
                              UGS::Math::Point2* out_pt, UGS::Math::Vector2* out_vec,
                              int* status);

extern "C" void sub_180054390(int n, UGS::Math::Point2* pts, UGS::Math::Point2* out_pt,
                              UGS::Math::Vector2* dir, double* max_out, double* mean_out);


void LSFIT_line_to_points_2d(int mode, UGS::Math::Point2* pts, int n,
                             UGS::Math::Point2* out_pt, UGS::Math::Vector2* out_vec,
                             int* ret, double* dist)
{
    double tol = 1.0e-6;
    if (mode & 2)
        tol = 1.0e-3;

    double* storage_a = 0;
    double* storage_v = 0;
    double mag;
    UGS::Math::Point2 furthest = {0.0, 0.0};
    UGS::Math::Vector2 dir = {0.0, 0.0};
    double eig[2];
    int ierr;

    double** A = NR_2d_matrix_allo(2, 2, &storage_a);
    double** V = NR_2d_matrix_allo(2, 2, &storage_v);

    out_pt->x = 0.0;
    out_pt->y = 0.0;
    out_vec->x = 0.0;
    out_vec->y = 0.0;
    *ret = 0;
    NR_2d_matrix_init_zero(A, 2, 2);

    double* p = (double*)SM_alloc((size_t)(16 * (__int64)n));
    if (n > 0)
    {
        __int64 k = n;
        __int64 j = 0;
        do
        {
            p[2 * j] = pts[j].x;
            p[2 * j + 1] = pts[j].y;
            ++j;
        } while (--k);
    }



    __m128i cnt = _mm_shuffle_epi32(_mm_cvtsi32_si128(n), 0);
    __m128d acc = _mm_setzero_pd();
    if (n > 0)
    {
        __int64 k = n;
        double* d = p;
        double sx = 0.0;
        do
        {
            sx += d[0];
            acc.m128d_f64[0] += d[1];
            d += 2;
        } while (--k);
        acc.m128d_f64[1] = acc.m128d_f64[0];
        acc.m128d_f64[0] = sx;
    }
    __m128d centroid = _mm_div_pd(acc, _mm_cvtepi32_pd(_mm_move_epi64(cnt)));

    __int64 i = 0;
    while (i < (__int64)n)
    {
        p[2 * i] -= centroid.m128d_f64[0];
        p[2 * i + 1] -= centroid.m128d_f64[1];
        ++i;
    }

    sub_180054C60(n, (UGS::Math::Point2*)p, tol, &furthest, &dir, ret);
    if (*ret == 1)
    {
        out_pt->x = centroid.m128d_f64[0];
        out_pt->y = centroid.m128d_f64[1];
        return;
    }

    for (i = 0; i < (__int64)n; ++i)
    {
        double x = p[2 * i];
        double y = p[2 * i + 1];
        A[0][0] += x * x;
        A[0][1] += y * x;
        A[1][1] += y * y;
    }
    A[1][0] = A[0][1];

    NR_ask_eigenvalues_jacobi(A, 2, 60, eig, V, &ierr);

    double best = 1.0e19;
    int k2 = 0;
    if (fabs(eig[0] - 0.0) <= 1.0e-9)
        eig[0] = 0.0;
    if (eig[0] >= 0.0 && 1.0e19 > eig[0])
        best = eig[0];
    if (fabs(eig[1] - 0.0) <= 1.0e-9)
        eig[1] = 0.0;
    if (eig[1] >= 0.0 && best > eig[1])
    {
        best = eig[1];
        k2 = 1;
    }

    if (fabs(best - 1.0e19) <= 1.0e-10)
    {
        out_vec->x = -dir.y;
        out_vec->y = dir.x;
    }
    else
    {
        out_vec->x = V[0][k2];
        out_vec->y = V[1][k2];
        VEC2_unitize(out_vec, 1.0e-10, &mag, out_vec);
    }

    out_pt->x = centroid.m128d_f64[0];
    out_pt->y = centroid.m128d_f64[1];
    sub_180054390(n, pts, out_pt, out_vec, &dist[0], &dist[2]);
    dist[1] = sqrt(best / (double)n);

    SM_free(A);
    if (V)
        SM_free(V);
    if (storage_a)
        SM_free(storage_a);
    if (storage_v)
        SM_free(storage_v);
    if (p)
        SM_free(p);
}
