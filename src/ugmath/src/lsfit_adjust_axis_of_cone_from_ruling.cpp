
























#include <math.h>

namespace UGS
{
namespace Math
{

struct Point3
{
    double x, y, z;
    Point3() { x = 0.0; y = 0.0; z = 0.0; }
};

struct Vector3
{
    double x, y, z;
};

}
}


double LSFIT_ask_dist_pt_to_line_3d(UGS::Math::Point3 *, UGS::Math::Point3 *,
                                    UGS::Math::Vector3 *, double,
                                    UGS::Math::Point3 *, double *);
double LSFIT_ask_acute_angle_of_lines_3d(UGS::Math::Vector3 *,
                                         UGS::Math::Vector3 *, double);

void __cdecl LSFIT_adjust_axis_of_cone_from_ruling(
    double *a1, bool a2, UGS::Math::Point3 *a3, UGS::Math::Vector3 *a4,
    UGS::Math::Point3 *const a5, UGS::Math::Vector3 *a6,
    UGS::Math::Point3 *const a7, double *const a8, double *a9)
{
    double d[2] = { 0.0 };
    UGS::Math::Point3 cp[2];
    UGS::Math::Point3 ip[2];
    UGS::Math::Point3 *out = a7;
    double scratch;

    out[0].x = out[0].y = out[0].z = 0.0;
    out[1].x = out[1].y = out[1].z = 0.0;
    a8[0] = 0.0;
    a8[1] = 0.0;
    *a9 = 0.0;

    UGS::Math::Point3 r0 = a5[0];
    UGS::Math::Point3 r1 = a5[1];
    ip[0] = r0;
    ip[1] = r1;

    if (a2)
    {
        for (int i = 0; i < 2; ++i)
            a8[i] = LSFIT_ask_dist_pt_to_line_3d(&a5[i], a3, a4, a1[0],
                                                 &out[i], &scratch);
    }
    else
    {
        for (int i = 0; i < 2; ++i)
        {
            double dist = LSFIT_ask_dist_pt_to_line_3d(
                &ip[i], a3, a4, a1[0], &cp[i], &scratch);
            d[i] = dist;


            if (a1[0] > dist
                || a1[0] >= sqrt((a3->y - cp[i].y) * (a3->y - cp[i].y)
                                 + (a3->x - cp[i].x) * (a3->x - cp[i].x)
                                 + (a3->z - cp[i].z) * (a3->z - cp[i].z)))
            {
                cp[i] = *a3;
                d[i] = 0.0;
            }
        }
        if (!(d[1] >= d[0]))
        {
            out[0] = cp[1];
            out[1] = cp[0];
            a5[0] = r1;
            a5[1] = r0;
            a8[0] = d[1];
            a8[1] = d[0];
        }
        else
        {
            out[0] = cp[0];
            out[1] = cp[1];
            a8[0] = d[0];
            a8[1] = d[1];
        }
        if ((out[1].y - out[0].y) * a4->y
                + (out[1].x - out[0].x) * a4->x
                + (out[1].z - out[0].z) * a4->z < 0.0)
        {
            a4->x = -a4->x;
            a4->y = -a4->y;
            a4->z = -a4->z;
            a6->x = -a6->x;
            a6->y = -a6->y;
            a6->z = -a6->z;
        }
        *a9 = LSFIT_ask_acute_angle_of_lines_3d(a4, a6, a1[1]);
    }
}
