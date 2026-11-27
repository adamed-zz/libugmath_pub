







#include <math.h>

namespace UGS
{
namespace Math
{
struct Vector3
{
    double x, y, z;
};
struct Point3
{
    double x, y, z;
};
}
}

using UGS::Math::Point3;
using UGS::Math::Vector3;


int VEC3_unitize(const Vector3* u, double tol, double* len_out, Vector3* out);
void LSFIT_ask_principle_axes_of_inertia_from_3d_pts(int n, const Point3* pts,
                                                     Point3* centroid, double* const vals,
                                                     Vector3* const axes);
void LSFIT_plane_to_points(int mode, const Point3* pts, int n, Point3* out_pt,
                           Vector3* out_normal, int* status, double* dist);
void LSFIT_ask_mean_vec(int n, const Vector3* pts, bool flag, Vector3* out_mean,
                        double* out_angle);
double LSFIT_ask_acute_angle_of_lines_3d(Vector3* a1, Vector3* a2, double tol);
void sub_180051140(int a1, __int64 a2, __int64 a3, __int64 a4, Point3* a5, int* a6,
                   Vector3* a7, __int64* a8, __int64* a9);

void sub_180050C50(int a1, __int64 a2, int a3, const Point3* a4, const Point3* a5,
                   Vector3* a6, double* a7, Point3* a8, int* a9, Vector3* a10)
{

    a8->x = 0.0;
    a8->y = 0.0;
    a8->z = 0.0;
    *a9 = 0;
    a10->x = 0.0;
    a10->y = 0.0;
    a10->z = 0.0;


    const double c0x = a6[0].x;
    const double c0y = a6[0].y;
    const double c0z = a6[0].z;
    const double sum6 = c0x * c0x + c0y * c0y + c0z * c0z;
    const double n6 = sqrt(sum6);

    double v46[3] = {0.0, 0.0, 0.0};
    if (!(n6 <= 1.0e-10))
    {

        const int n = a3;
        double sx = 0.0;
        double sy = 0.0;
        double sz = 0.0;
        if (n > 0)
        {
            for (int i = 0; i < n; ++i)
            {
                sx += a4[i].x;
                sy += a4[i].y;
                sz += a4[i].z;
            }
        }
        const double cnt = (double)n;
        a8->x = sx / cnt;
        a8->y = sy / cnt;
        a8->z = sz / cnt;
    }
    else
    {

        LSFIT_ask_principle_axes_of_inertia_from_3d_pts(a3, a4, a8, v46, a6);
    }


    Vector3 v37 = a6[2];


    const double n7 = sqrt(a7[0] * a7[0] + a7[1] * a7[1] + a7[2] * a7[2]);
    if (n7 <= 1.0e-10)
    {
        Vector3 v42 = {0.0, 0.0, 0.0};
        int plane_stub = 0;


        double dist_stub[3] = {0.0, 0.0, 0.0};
        LSFIT_plane_to_points(0, a4, a3, a8, &v42, &plane_stub, &dist_stub[0]);
        const double tol0 = *(const double*)((const char*)a2 + 8);
        const double ang0 = LSFIT_ask_acute_angle_of_lines_3d(&v42, &a6[0], tol0);
        const double ang1 = LSFIT_ask_acute_angle_of_lines_3d(&v42, &a6[1], tol0);

        if (!(ang1 > ang0))
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


    Vector3 mean44 = {0.0, 0.0, 0.0};
    double ang41 = 0.0;
    LSFIT_ask_mean_vec(a3, (const Vector3*)a5, true, &mean44, &ang41);
    const double tol = *(const double*)((const char*)a2 + 8);


    if (tol >= ang41)
    {
        *a9 = 1;


        double len_tmp = 0.0;
        VEC3_unitize(&mean44, 1.0e-10, &len_tmp, a10);
        return;
    }

    double planeP[3] = {0.0, 0.0, 0.0};
    Vector3 normal40 = {0.0, 0.0, 0.0};
    int status36 = 0;

    double dist48[3] = {0.0, 0.0, 0.0};
    LSFIT_plane_to_points(0, a5, a3, (Point3*)planeP, &normal40, &status36, &dist48[0]);
    if (status36)
    {
        *a9 = 1;
        double len_tmp = 0.0;
        VEC3_unitize(&mean44, 1.0e-10, &len_tmp, a10);
        return;
    }


    const double lenN = sqrt(normal40.y * normal40.y + normal40.x * normal40.x +
                             normal40.z * normal40.z);
    const double dotPN = (0.0 - planeP[0]) * normal40.x +
                         (0.0 - planeP[1]) * normal40.y +
                         (0.0 - planeP[2]) * normal40.z;
    const double ratio = dotPN / lenN;
    const double abs_ratio = fabs(ratio);

    const double clamp1 = (1.0 < abs_ratio) ? 1.0 : abs_ratio;
    const double v34 = acos(clamp1);
    const double v34deg = v34 * 57.29577951308235;


    if (tol > v34deg)
    {
        *a9 = 1;
        return;
    }

    if (v34deg > 90.0 - tol)
        *a9 = 1;

    if (a1 == 0)
    {

        planeP[0] = 0.0;
        planeP[1] = 0.0;
        planeP[2] = 0.0;
        __int64 a2copy = a2;
        sub_180051140(a3, (__int64)a4, (__int64)a5, a2, a8, a9, (Vector3*)planeP,
                      (__int64*)&dist48, &a2copy);

        const double tol2 = *(const double*)((const char*)a2 + 8);
        const double ang =
            LSFIT_ask_acute_angle_of_lines_3d((Vector3*)planeP, &normal40, tol2);

        if (!(ang > 15.0))
        {
            a10->x = planeP[0];
            a10->y = planeP[1];
            a10->z = planeP[2];
        }
        else
        {
            *a10 = v37;
        }
    }
    else if (a1 == 1)
    {

        const double tol1 = *(const double*)((const char*)a2 + 8);
        const double ang = LSFIT_ask_acute_angle_of_lines_3d(&normal40, &v37, tol1);

        if (15.0 >= ang)
            *a10 = v37;
        else
            *a10 = normal40;
    }
    else
    {
        *a10 = v37;
    }
}
