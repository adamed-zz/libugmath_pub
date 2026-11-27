










struct ARC_SPLINE_1_seg_2d_s
{
    int    tag;
    int    count;
    unsigned char pad0[0x10];
    double start_parm;
    unsigned char pad1[0x28];
    double radius;
};

double ARC_SPLINE_ask_arcl_to_parm_of_1_seg_2d(
    struct ARC_SPLINE_1_seg_2d_s* a1, double arc_len, int* a3)
{
    double parm = 0.0;
    *a3 = 0;
    if (!a1)
    {
        *a3 = 1;
        return 0.0;
    }
    if (a1->tag == 0)
    {
        parm = arc_len;
    }
    else if (a1->tag == 1)
    {
        double r = a1->radius;
        if (r < 1.0e-10)
        {
            *a3 = 2;
            return 0.0;
        }
        double v = (arc_len - a1->start_parm) * (double)a1->count;
        if (v < 0.0)
            v += 360.0;
        parm = r * 0.01745329251994328 * v;
    }
    else
    {
        *a3 = 3;
    }
    return parm;
}
