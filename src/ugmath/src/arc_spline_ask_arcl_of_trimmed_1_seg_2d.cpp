






#include <cmath>


struct ARC_SPLINE_1_seg_2d_s
{
    int type;
    int idx;
    unsigned char pad[0x40];
    double radius;
};


double ARC_SPLINE_ask_central_angle_from_inclination_angles(double angle, double *incl, int num);

double ARC_SPLINE_ask_arcl_of_trimmed_1_seg_2d(ARC_SPLINE_1_seg_2d_s *arc, double *const angles, int *status)
{
    double result = 0.0;
    *status = 0;
    if (!arc)
    {
        *status = 1;
        return 0.0;
    }
    if (arc->type == 0)
    {
        result = fabs(angles[1] - angles[0]);
    }
    else if (arc->type == 1)
    {
        double radius = arc->radius;
        if (1.0e-10 > radius)
        {
            *status = 2;
            return 0.0;
        }
        result = ARC_SPLINE_ask_central_angle_from_inclination_angles(angles[0], angles + 1, arc->idx)
               * (radius * 0.01745329251994328);
    }
    else
    {
        *status = 3;
    }
    return result;
}
