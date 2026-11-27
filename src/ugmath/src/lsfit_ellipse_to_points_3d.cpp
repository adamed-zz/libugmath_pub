








#include <emmintrin.h>

namespace UGS {
namespace Math {
struct Point3 {
    double x, y, z;
};
struct Vector3 {
    double x, y, z;
};
struct Point2 {
    double x, y;
};
}
}

struct CSYS_s {
    double origin[3];
    double x_axis[3];
    double y_axis[3];
    double z_axis[3];
};


__declspec(dllimport) void * __cdecl SM_alloc(unsigned __int64 size);
__declspec(dllimport) void __cdecl SM_free(void *p);


void LSFIT_ellipse_to_points_2d(UGS::Math::Point2 *pts2d, int npts,
                                UGS::Math::Point2 *center2d, double *a4, double *a5,
                                double *a6, int *status, double *a8);
void LSFIT_plane_to_points(int a1, UGS::Math::Point3 *points, int npts,
                           UGS::Math::Point3 *center, UGS::Math::Vector3 *normal,
                           int *status, double *a7);


void sub_180055700(unsigned int npts, UGS::Math::Point3 *points,
                   UGS::Math::Point3 *center, UGS::Math::Vector3 *normal,
                   UGS::Math::Point2 *buf, CSYS_s *csys);


extern "C" double __cdecl sqrt(double x);

void LSFIT_ellipse_to_points_3d(UGS::Math::Point3 *points, int npoints,
                                UGS::Math::Point3 *center, UGS::Math::Vector3 *normal,
                                UGS::Math::Point3 *fit_center, double *radius1,
                                double *radius2, double *radius3, int *status,
                                double *work, CSYS_s *csys)
{
    __int64 count = npoints;
    center->x = 0.0;
    center->y = 0.0;
    center->z = 0.0;
    fit_center->x = 0.0;
    fit_center->y = 0.0;
    fit_center->z = 0.0;
    *radius1 = 1.0e19;
    *radius2 = 1.0e19;
    *status = 0;

    double len = sqrt(normal->x * normal->x + normal->y * normal->y +
                      normal->z * normal->z);
    if (len <= 1.0e-10) {
        LSFIT_plane_to_points(0, points, npoints, center, normal, status, work);
    } else {
        double sx = 0.0;
        double sy = 0.0;
        double sz = 0.0;
        if ((int)count > 0) {
            __int64 left = count;
            const double *p = (const double *)((const char *)points + 16);
            do {
                sx = sx + p[-2];
                sy = sy + p[-1];
                sz = sz + p[0];
                p += 3;
                --left;
            } while (left);
        }
        center->x = sx / (double)(int)count;
        center->y = sy / (double)(int)count;
        center->z = sz / (double)(int)count;
    }

    if (*status == 0) {
        double v31[2] = {0.0, 0.0};
        UGS::Math::Point2 *buf = (UGS::Math::Point2 *)SM_alloc(16 * count);
        sub_180055700((unsigned int)count, points, center, normal, buf, csys);
        LSFIT_ellipse_to_points_2d(buf, npoints, (UGS::Math::Point2 *)v31,
                                   radius1, radius2, radius3, status, work);
        if (*status == 0) {
            __m128d vv = _mm_loadu_pd(v31);
            *(__m128d *)fit_center =
                _mm_unpacklo_pd(vv, _mm_unpackhi_pd(vv, vv));
            fit_center->z = 0.0;
            double x = fit_center->x;
            double y = fit_center->y;
            double z = fit_center->z;
            double nx = y * csys->y_axis[0] + x * csys->x_axis[0] +
                        z * csys->z_axis[0] + csys->origin[0];
            double ny = x * csys->x_axis[1] + y * csys->y_axis[1] +
                        z * csys->z_axis[1] + csys->origin[1];
            double nz = y * csys->y_axis[2] + x * csys->x_axis[2] +
                        z * csys->z_axis[2] + csys->origin[2];
            fit_center->x = nx;
            fit_center->y = ny;
            fit_center->z = nz;
        }
        if (buf) {
            SM_free(buf);
        }
    }
}
