

















#pragma once











struct ARC_SPLINE_1_seg_2d_s
{
    int    tag;
    int    count;
    unsigned char pad0[0x10];
    double start_parm;
    unsigned char pad1[0x28];
    double radius;
};



double ARC_SPLINE_ask_central_angle_of_1_seg_2d(ARC_SPLINE_1_seg_2d_s* segment_ptr);


double ARC_SPLINE_ask_arcl_of_1_seg_2d(ARC_SPLINE_1_seg_2d_s* a1, int* a2)
{
    double parm = 0.0;
    *a2 = 0;

    if (!a1)
    {
        *a2 = 1;
        return 0.0;
    }

    if (a1->tag == 0)
    {
        parm = a1->radius;
    }
    else if (a1->tag == 1)
    {
        double r = a1->radius;
        if (r < 1.0e-10)
        {
            *a2 = 2;
            return 0.0;
        }
        parm = ARC_SPLINE_ask_central_angle_of_1_seg_2d(a1) * (r * 0.01745329251994328);
    }
    else
    {
        *a2 = 3;
    }
    return parm;
}
