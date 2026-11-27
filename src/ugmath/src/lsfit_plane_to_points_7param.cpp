









#include <math.h>
#include <stddef.h>

namespace UGS {
namespace Math {

struct Point3
{
    double x, y, z;
};

struct Vector3
{
    double x, y, z;
};

}
}

using UGS::Math::Point3;
using UGS::Math::Vector3;


double** NR_2d_matrix_allo(int a1, int a2, double** a3);
void NR_2d_matrix_init_zero(double** a1, int a2, int a3);
void NR_ask_eigenvalues_jacobi(double** a1, int a2, int a3, double* const a4, double** a5, int* a6);
int VEC3_unitize(const Vector3* a1, double a2, double* a3, Vector3* a4);
int VEC3_ask_perpendicular(const Vector3* a1, Vector3* a2);


void* SM_alloc(unsigned __int64 a1);
void SM_free(void* a1);


extern "C" void sub_180055030(int npts, const double* pts, double tol, Point3* part_a,
                              Point3* part_b, Vector3* normal, int* degen, int* special);
extern "C" void sub_180054570(int npts, const Point3* pts, const Point3* point,
                              const Vector3* normal, double* max_dev, double* mean_dev);

void __cdecl LSFIT_plane_to_points(int a1, Point3* a2, int a3, Point3* a4, Vector3* a5,
                                   int* a6, double* a7)
{
    double* data1 = 0;
    double* data2 = 0;
    Vector3 dir = { 0.0, 0.0, 0.0 };
    Point3  part_a = { 0.0, 0.0, 0.0 };
    Point3  part_b = { 0.0, 0.0, 0.0 };
    int     degen = 0;
    double* cen = 0;
    double  tol = 1.0e-6;
    if ( a1 & 2 )
        tol = 1.0e-3;

    double** cov  = NR_2d_matrix_allo(3, 3, &data1);
    double** evec = NR_2d_matrix_allo(3, 3, &data2);

    a4->x = 0.0;
    a4->y = 0.0;
    a4->z = 0.0;
    a5->x = 0.0;
    a5->y = 0.0;
    a5->z = 0.0;
    *a6 = 0;
    NR_2d_matrix_init_zero(cov, 3, 3);

    double sx = 0.0, sy = 0.0, sz = 0.0;
    for ( int i = 0; i < a3; i++ )
    {
        sx += a2[i].x;
        sy += a2[i].y;
        sz += a2[i].z;
    }
    double dn = (double)a3;
    double cx = sx / dn;
    double cy = sy / dn;
    double cz = sz / dn;

    cen = (double*)SM_alloc(3 * (__int64)a3 * sizeof(double));
    for ( int i = 0; i < a3; i++ )
    {
        cen[3 * i + 0] = a2[i].x - cx;
        cen[3 * i + 1] = a2[i].y - cy;
        cen[3 * i + 2] = a2[i].z - cz;
    }

    sub_180055030(a3, cen, tol, &part_a, &part_b, a5, &degen, a6);
    do
    {
        if ( degen == 1 )
        {
            a4->x = cx;
            a4->y = cy;
            a4->z = cz;
            a5->x = 0.0;
            a5->y = 0.0;
            a5->z = 1.0;
            break;
        }
        if ( *a6 == 1 )
        {
            dir.x = part_a.x;
            dir.y = part_a.y;
            dir.z = part_a.z;
            a4->x = cx;
            a4->y = cy;
            a4->z = cz;
            double mag;
            VEC3_unitize(&dir, 1.0e-10, &mag, &dir);
            VEC3_ask_perpendicular(&dir, a5);
            VEC3_unitize(a5, 1.0e-10, &mag, a5);
            break;
        }

        for ( int i = 0; i < a3; i++ )
        {
            double x = cen[3 * i + 0];
            double y = cen[3 * i + 1];
            double z = cen[3 * i + 2];
            cov[0][0] += x * x;
            cov[0][1] += y * x;
            cov[0][2] += z * x;
            cov[1][1] += y * y;
            cov[1][2] += z * y;
            cov[2][2] += z * z;
        }
        cov[1][0] = cov[0][1];
        cov[2][0] = cov[0][2];
        cov[2][1] = cov[1][2];

        double eig[3];
        int iters;
        NR_ask_eigenvalues_jacobi(cov, 3, 60, eig, evec, &iters);

        double min_ev = 1.0e19;
        double alt = 1.0e19;
        int have_alt = 0;
        int min_idx = 0;
        int alt_idx = 0;
        for ( int i = 0; i < 3; i++ )
        {
            double ev = eig[i];
            if ( fabs(ev - 0.0) <= 1.0e-9 )
            {
                eig[i] = 0.0;
                ev = 0.0;
            }
            else if ( ev < 0.0 )
            {
                double q = 2.0 * cov[1][0] * evec[0][i] * evec[1][i]
                         + cov[0][0] * evec[0][i] * evec[0][i]
                         + 2.0 * cov[2][0] * evec[0][i] * evec[2][i]
                         + cov[1][1] * evec[1][i] * evec[1][i]
                         + 2.0 * cov[2][1] * evec[1][i] * evec[2][i]
                         + cov[2][2] * evec[2][i] * evec[2][i];
                if ( fabs(q) < 1.0e-8 )
                {
                    eig[i] = 0.0;
                    ev = 0.0;
                }
                else if ( alt - 1.0e-10 > ev )
                {
                    alt = fabs(ev);
                    have_alt = 1;
                    alt_idx = i;
                }
            }
            if ( ev >= 0.0 && min_ev > ev )
            {
                min_ev = ev;
                min_idx = i;
            }
        }

        if ( fabs(min_ev - 1.0e19) > 1.0e-10 )
        {
            a5->x = evec[0][min_idx];
            a5->y = evec[1][min_idx];
            a5->z = evec[2][min_idx];
            double mag;
            VEC3_unitize(a5, 1.0e-10, &mag, a5);
            a4->x = cx;
            a4->y = cy;
            a4->z = cz;
        }
        else
        {
            dir.x = part_a.x - cx;
            dir.y = part_a.y - cy;
            dir.z = part_a.z - cz;
            *a6 = 1;
            a4->x = cx;
            a4->y = cy;
            a4->z = cz;
            double mag;
            VEC3_unitize(&dir, 1.0e-10, &mag, &dir);
            VEC3_ask_perpendicular(&dir, a5);
            VEC3_unitize(a5, 1.0e-10, &mag, a5);
        }

        sub_180054570(a3, a2, a4, a5, a7, a7 + 2);
        if ( (a1 & 1) && have_alt && min_idx != alt_idx )
        {
            part_a.x = evec[0][alt_idx];
            part_a.y = evec[1][alt_idx];
            part_a.z = evec[2][alt_idx];
            double max_dev;
            double mean_dev;
            sub_180054570(a3, a2, a4, (const Vector3*)&part_a, &max_dev, &mean_dev);
            if ( a7[2] - 1.0e-10 > mean_dev )
            {
                a5->x = part_a.x;
                a5->y = part_a.y;
                a5->z = part_a.z;
                min_ev = alt;
                a7[0] = max_dev;
                a7[2] = mean_dev;
            }
        }
        a7[1] = sqrt(min_ev / dn);
    } while ( 0 );

    SM_free(cov);
    SM_free(evec);
    if ( data1 )
        SM_free(data1);
    if ( data2 )
        SM_free(data2);
    if ( cen )
        SM_free(cen);
}
