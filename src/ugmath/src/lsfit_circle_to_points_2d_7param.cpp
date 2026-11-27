



#include <math.h>
#include <intrin.h>

namespace UGS {
namespace Math {

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

struct ARC_SPLINE_1_seg_2d_s;


double** __cdecl NR_2d_matrix_allo(int rows, int cols, double** storage);
void __cdecl NR_2d_matrix_init_zero(double** m, int rows, int cols);
void __cdecl NR_matrix_2d_as_1d_identity(double* a, int n);
void __cdecl NR_matrix_copy_2d_to_1d(double** m, int rows, int cols, double* a);
void __cdecl NR_generalized_eigenvalues_symm(double* a, double* b, int n, int matz,
                                             double* const d, double* v,
                                             int* nrot, int* ierr);
void __cdecl ARC_SPLINE_cre_circle_thru_3_points_2d(
    const UGS::Math::Point2* p1, const UGS::Math::Point2* p2, const UGS::Math::Point2* p3,
    const double* const tol, ARC_SPLINE_1_seg_2d_s* seg, int* status);
void __cdecl LSFIT_line_to_points_2d(int type, UGS::Math::Point2* pts, int n,
                                     UGS::Math::Point2* pt, UGS::Math::Vector2* dir,
                                     int* status, double* fit);
void __cdecl sub_1800540A0(int n, UGS::Math::Point2* pts, UGS::Math::Point2* center,
                           double radius, double* maxdev, double* rms);

__declspec(dllimport) void* __cdecl SM_alloc(unsigned __int64 size);
__declspec(dllimport) void __cdecl SM_free(void* p);

using UGS::Math::Point2;
using UGS::Math::Vector2;

#pragma pack(push, 8)
union D2
{
    __m128d v;
    double  d[2];
};
#pragma pack(pop)

void __cdecl LSFIT_circle_to_points_2d(Point2* pts, int n, double tol, Point2* center,
                                       double* radius, int* status, double* resid)
{
    unsigned int best = 0;
    __int64      nn   = n;

    __m128i cnt = _mm_shuffle_epi32(_mm_cvtsi32_si128(n), 0);

    double* s1 = 0;
    double* s2 = 0;
    double* s3 = 0;
    double** m  = NR_2d_matrix_allo(4, 4, &s1);
    double** m2 = NR_2d_matrix_allo(4, 4, &s2);
    double** m3 = NR_2d_matrix_allo(4, 4, &s3);

    center->x = 0.0;
    center->y = 0.0;
    *radius   = 1.0e19;
    *status   = 0;
    NR_2d_matrix_init_zero(m, 4, 4);

    double* q = (double*)SM_alloc(16 * nn);
    if (n > 0)
    {
        for (__int64 i = 0; i != nn; ++i)
        {
            q[2 * i]     = pts[i].x;
            q[2 * i + 1] = pts[i].y;
        }
    }


    D2 acc;
    acc.v = _mm_setzero_pd();
    double  sumx = 0.0;
    if (n > 0)
    {
        double* p = q;
        __int64 k = nn;
        do
        {
            sumx += p[0];
            acc.d[0] += p[1];
            p += 2;
        } while (--k);
        acc.d[1] = acc.d[0];
        acc.d[0] = sumx;
    }
    __m128d mean = _mm_div_pd(acc.v, _mm_cvtepi32_pd(_mm_move_epi64(cnt)));
    Point2  mid;
    _mm_storeu_pd(&mid.x, mean);

    for (__int64 i = 0; i < nn; ++i)
    {
        q[2 * i]     = q[2 * i] - mid.x;
        q[2 * i + 1] = q[2 * i + 1] - mid.y;
    }

    (*m)[0] = (double)(int)n;
    (*m)[1] = 0.0;
    (*m)[2] = 0.0;

    for (__int64 i = 0; i < nn; ++i)
    {
        double x  = q[2 * i];
        double y  = q[2 * i + 1];
        double r2 = x * x + y * y;
        (*m)[3]     = r2 + (*m)[3];
        m[1][1]     = x * x + m[1][1];
        m[1][2]     = y * x + m[1][2];
        m[1][3]     = r2 * x + m[1][3];
        m[2][2]     = y * y + m[2][2];
        m[2][3]     = r2 * y + m[2][3];
        m[3][3]     = r2 * r2 + m[3][3];
    }

    m[1][0] = (*m)[1];
    m[2][0] = (*m)[2];
    m[2][1] = m[1][2];
    m[3][0] = (*m)[3];
    m[3][1] = m[1][3];
    m[3][2] = m[2][3];

    double ma[16];
    NR_matrix_2d_as_1d_identity(ma, 4);
    ma[3]  = -2.0;
    ma[12] = -2.0;
    ma[0]  = 0.0;
    ma[15] = 0.0;

    double* storage = 0;
    double  mb[16];
    NR_matrix_2d_as_1d_identity(mb, 4);
    mb[0]  = 0.0;
    mb[15] = 0.0;
    mb[3]  = -2.0;
    mb[12] = -2.0;

    double** unused = NR_2d_matrix_allo(4, 4, &storage);
    NR_matrix_copy_2d_to_1d(m, 4, 4, storage);

    double eval[4];
    double evec[16];
    int    nrot;
    int    ierr;
    NR_generalized_eigenvalues_symm(mb, storage, 4, 60, eval, evec, &nrot, &ierr);
    if (unused)
        SM_free(unused);
    if (storage)
        SM_free(storage);

    if (ierr == 1)
        goto fallback;
    {
        double lmax = 0.0;
        if (eval[0] > 1.0e-19 && eval[0] > 0.0)
            lmax = eval[0];
        if (eval[1] > 1.0e-19 && eval[1] > lmax)
        {
            best = 1;
            lmax = eval[1];
        }
        if (eval[2] > 1.0e-19 && eval[2] > lmax)
        {
            best = 2;
            lmax = eval[2];
        }
        if (eval[3] > 1.0e-19 && eval[3] > lmax)
        {
            best = 3;
            lmax = eval[3];
        }
        if (lmax < 1.0e-10)
            goto fallback;

        if (*status == 0)
        {
            double inv = 1.0 / lmax;
            double c   = evec[best];
            double e0  = evec[best + 4];
            double e1  = evec[best + 8];
            double e3  = evec[best + 12];
            if (fabs(e3 - 0.0) > 1.0e-19)
            {
                double cy = e1 / e3 * -0.5;
                double cx = e0 / e3 * -0.5;
                center->y = cy;
                center->x = cx;
                *radius   = sqrt(fabs(cy * cy + cx * cx - c / e3));
                _mm_storeu_pd(&center->x,
                              _mm_add_pd(_mm_loadu_pd(&center->x), mean));
                sub_1800540A0(n, pts, center, *radius, resid, resid + 2);
                resid[1] = sqrt((double)(int)n * inv);
            }
            else
            {
                *status = 1;
            }
        }

        SM_free(m);
        SM_free(m2);
        SM_free(m3);
        if (s1)
            SM_free(s1);
        if (s2)
            SM_free(s2);
        if (s3)
            SM_free(s3);
        if (q)
            SM_free(q);
        return;
    }

fallback:

    {
        Point2  line_pt;
        Vector2 line_dir;
        double  lfit[3];
        line_pt.x  = 0.0;
        line_pt.y  = 0.0;
        line_dir.x = 0.0;
        line_dir.y = 0.0;
        int ls;
        LSFIT_line_to_points_2d(0, pts, n, &line_pt, &line_dir, &ls, lfit);
        if (ls == 1 || tol * 0.5 > lfit[1])
        {
            *status = 1;
        }
        else
        {
            double tol2[2] = {1.0e-10, 0.001};
            ARC_SPLINE_cre_circle_thru_3_points_2d(
                pts, &pts[n / 2], &pts[n - 1],
                tol2, (ARC_SPLINE_1_seg_2d_s*)mb, status);
            if (*status == 0)
            {
                *radius = *(double*)((char*)mb + 0x48);
                *center = *(Point2*)((char*)mb + 0x28);
                SM_free(m);
                SM_free(m2);
                SM_free(m3);
                SM_free(s1);
                SM_free(s2);
                SM_free(s3);
                SM_free(q);
                return;
            }
        }
        *radius = 1.0e19;
    }

    SM_free(m);
    SM_free(m2);
    SM_free(m3);
    SM_free(s1);
    SM_free(s2);
    SM_free(s3);
    SM_free(q);
}
