









struct ARC_SPLINE_1_seg_2d_s
{
    unsigned int tag;
    unsigned char pad[0x44];
    double       radius;
};

double ARC_SPLINE_ask_radius_of_1_seg_2d(const struct ARC_SPLINE_1_seg_2d_s* a)
{
    if (a->tag == 0)
        return 1.0e19;
    return a->radius;
}
