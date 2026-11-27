















#include <cmath>

struct ARC_SPLINE_1_seg_2d_s
{
    int    type;
    int    dir;
    double base_x;
    double base_y;
    double start;
    double end;
    double center_x;
    double center_y;
    double line_dx;
    double line_dy;
    double radius;
    double radius2;
};

namespace UGS { namespace Math {
struct Point2 { double x; double y; };
}}

using UGS::Math::Point2;


void ARC_SPLINE_ask_parm_at_a_point_2d(
    const ARC_SPLINE_1_seg_2d_s* a1, const Point2* a2, const double* const a3,
    Point2* a4, double* a5, int* a6, int* a7);
void ARC_SPLINE_cre_circle_thru_2_points_and_radius(
    const Point2* a1, const Point2* a2, double a3, int a4, const double* const a5,
    int* a6, ARC_SPLINE_1_seg_2d_s* a7, ARC_SPLINE_1_seg_2d_s* a8, int* a9);
void ARC_SPLINE_inter_of_2_circular_arcs_2d(
    const ARC_SPLINE_1_seg_2d_s* a1, const ARC_SPLINE_1_seg_2d_s* a2, int a3, int a4,
    const double* const a5, int* a6, Point2* a7, double* a8, int* a9,
    Point2* a10, double* a11, int* a12, int* a13);
int ARC_SPLINE_ask_is_parm_in_arc_domain(
    const ARC_SPLINE_1_seg_2d_s* a1, double a2, double* a3);

void ARC_SPLINE_ask_tangents_thru_a_point_2d(
    const ARC_SPLINE_1_seg_2d_s* a1,
    const Point2* a2,
    int a3,
    const double* const a4,
    int* a5,
    Point2* a6,
    Point2* a7,
    double* a8,
    int* a9,
    int* a10)
{
    const Point2* v40 = a2;
    double*       v10 = a8;
    Point2*       v12 = a6;
    Point2*       v13 = a7;
    const double* v14 = a4;
    int*          v15 = a9;
    int*          v16 = a10;

    *a5 = 0;
    v10[0] = 0.0;
    v10[1] = 0.0;
    *(long long*)v15 = -1;
    *(long long*)&v12->x = 0;
    *(long long*)&v12->y = 0;
    *(long long*)&v13->x = 0;
    *(long long*)&v13->y = 0;
    *v16 = 0;



    *(int*)&a8 = 0;
    Point2 center = {0.0, 0.0};

    if (!a1)
        goto BAD_INPUT;

    {
        int    type = a1->type;
        double cx   = a1->center_x;
        double cy   = a1->center_y;
        center.x = cx;
        center.y = cy;
        if (type == 0)
            return;
        if (type != 1)
            goto BAD_INPUT;

        {
            double radius = a1->radius;
            double py     = v40->y;
            double px     = v40->x;
            double dist2  = (px - cx) * (px - cx) + (py - cy) * (py - cy);
            double dist   = sqrt(dist2);

            if (v14[0] >= fabs(dist - radius))
            {
                ARC_SPLINE_ask_parm_at_a_point_2d(a1, v40, v14, v12, v10, v15,
                                                  (int*)&a8);
                if ((int)a8 > 0)
                {
                    *v16 = 2;
                    return;
                }
                if (!a3)
                {
                    *v15 = -1;
                    *a5  = 1;
                    return;
                }
                if (*v15 != 1)
                    *a5 = 1;
                return;
            }

            if (radius > dist)
                return;

            {
                double dist2b = (cx - px) * (cx - px) + (cy - py) * (cy - py);
                double half   = sqrt(dist2b) * 0.5;
                ARC_SPLINE_1_seg_2d_s seg1;
                ARC_SPLINE_1_seg_2d_s seg2;

                ARC_SPLINE_cre_circle_thru_2_points_and_radius(
                    &center, v40, half, 1, v14, (int*)&a9, &seg1, &seg2, (int*)&a8);
                if ((int)a8 > 0)
                {
                    *v16 = 3;
                    return;
                }

                {
                    double parm2[2];
                    ARC_SPLINE_inter_of_2_circular_arcs_2d(
                        a1, &seg1, 0, 0, v14, (int*)&a9, v12, &center.x, (int*)&a6,
                        v13, parm2, (int*)&a7, (int*)&a8);
                    if ((int)a8 > 0 || (int)a9 < 2)
                    {
                        *v16 = 4;
                        return;
                    }

                    v10[0] = center.x;
                    v10[1] = parm2[0];
                    *v15   = (int)a6;
                    v15[1] = (int)a7;

                    if (a3)
                    {
                        *v15 = ARC_SPLINE_ask_is_parm_in_arc_domain(a1, v14[1], v10);
                        int in_domain =
                            ARC_SPLINE_ask_is_parm_in_arc_domain(a1, v14[1], v10 + 1);
                        v15[1] = in_domain;
                        if (*v15 == 1)
                        {
                            if (in_domain == 1)
                                return;
                            *a5 = 1;
                            goto SWAP;
                        }
                        if (in_domain == 1)
                        {
                            *a5 = 1;
                            return;
                        }
                    }

                    *a5 = 2;
                    {
                        int dir = a1->dir;
                        if (dir > 0)
                        {
                            if (!(v10[0] > v10[1]))
                                return;
                        }
                        else if (dir == 0)
                        {
                            return;
                        }
                        else
                        {
                            if (!(v10[1] > v10[0]))
                                return;
                        }
                    }

                SWAP:
                    {
                        Point2 tp = *v12;
                        *v12      = *v13;
                        *v13      = tp;
                        double td = v10[0];
                        v10[0]    = v10[1];
                        v10[1]    = td;
                        int ti    = v15[0];
                        v15[0]    = v15[1];
                        v15[1]    = ti;
                    }
                }
            }
        }
    }
    return;

BAD_INPUT:
    *v16 = 1;
}
