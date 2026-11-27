














#include <stdarg.h>
#include <math.h>

namespace UGS
{
namespace Math
{
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


void LSFIT_ask_principle_axes_of_inertia_from_3d_pts(int n, Point3* pts, Point3* center,
                                                     double* const ied,
                                                     Vector3* const axes);
void LSFIT_ask_mean_vec(int n, Vector3* pts, bool flag, Vector3* out_mean, double* out_angle);
void LSFIT_plane_to_points(int mode, Point3* pts, int n, Point3* out_pt, Vector3* out_vec,
                           int* status, double* dist);
double LSFIT_ask_acute_angle_of_lines_3d(Vector3* a1, Vector3* a2, double tol);
int VEC3_unitize(const Vector3* u, double tol, double* len_out, Vector3* out);

void sub_180051CD0(int a1, __int64 a2, int a3, Point3* a4, Vector3* a5, Vector3* a6,
                   double* a7, ...)
{
    va_list ap;
    va_start(ap, a7);
    Point3* v40 = va_arg(ap, Point3*);
    Vector3* v42 = va_arg(ap, Vector3*);
    int* v44 = va_arg(ap, int*);
    double* v45 = va_arg(ap, double*);
    va_end(ap);

    const double tol = *(double*)(a2 + 8);
    Point3* v7 = v40;
    Vector3* v8 = v42;
    int* v12 = v44;
    double* v9 = v45;

    *((double*)v7 + 2) = 0.0;
    *((double*)v7 + 1) = 0.0;
    *(double*)v7 = 0.0;
    *((double*)v8 + 2) = 0.0;
    *((double*)v8 + 1) = 0.0;
    *(double*)v8 = 0.0;
    *v12 = 0;
    v9[0] = 0.0;
    v9[1] = 0.0;
    v9[2] = 0.0;


    double nrm = sqrt(a6->x * a6->x + a6->y * a6->y + a6->z * a6->z);


    if (1.0e-10 >= nrm)
    {
        double ied;
        LSFIT_ask_principle_axes_of_inertia_from_3d_pts(a3, a4, v7, &ied, a6);
    }
    else
    {
        double sx = 0.0, sy = 0.0, sz = 0.0;
        if (a3 > 0)
        {
            const Point3* p = a4;
            for (int i = 0; i < a3; ++i)
            {
                sx += p->x;
                sy += p->y;
                sz += p->z;
                ++p;
            }
        }
        v7->x = sx / (double)a3;
        v7->y = sy / (double)a3;
        v7->z = sz / (double)a3;
    }


    double nrm7 = sqrt(a7[0] * a7[0] + a7[1] * a7[1] + a7[2] * a7[2]);
    if (1.0e-10 >= nrm7)
    {
        double dist = 0.0;
        int status = 0;
        Vector3 plane_dir;
        plane_dir.x = 0.0;
        plane_dir.y = 0.0;
        plane_dir.z = 0.0;
        LSFIT_plane_to_points(0, a4, a3, v7, &plane_dir, &status, &dist);
        double ang0 = LSFIT_ask_acute_angle_of_lines_3d(&plane_dir, a6, tol);
        double ang1 = LSFIT_ask_acute_angle_of_lines_3d(&plane_dir, a6 + 1, tol);

        if (!(ang0 < ang1))
        {
            a7[0] = a6[1].x;
            a7[1] = a6[1].y;
            a7[2] = a6[1].z;
        }
        else
        {
            a7[0] = a6[0].x;
            a7[1] = a6[0].y;
            a7[2] = a6[0].z;
        }
    }

    Vector3 mean;
    mean.x = 0.0;
    mean.y = 0.0;
    mean.z = 0.0;
    double mean_angle = 0.0;
    LSFIT_ask_mean_vec(a3, a5, true, &mean, &mean_angle);

    if (!(mean_angle <= tol))
    {
        Point3 plane_pt = {0.0, 0.0, 0.0};
        int status = 0;
        LSFIT_plane_to_points(0, (Point3*)a5, a3, &plane_pt, v8, &status, v9);
        if (status)
        {
            *v12 = 1;
            double len;
            VEC3_unitize(&mean, 1.0e-10, &len, v8);
        }
        if (!*v12 &&
            (LSFIT_ask_acute_angle_of_lines_3d(v8, a6 + 2, tol) <= 15.0 || a1 == 2))
        {
            v8->x = a6[2].x;
            v8->y = a6[2].y;
            v8->z = a6[2].z;
        }
    }
    else
    {
        *v12 = 1;
        double len;
        VEC3_unitize(&mean, 1.0e-10, &len, v8);
    }
}
