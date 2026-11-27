













namespace UGS
{
namespace Math
{
struct Point2
{
    double x;
    double y;
};
}
}

struct ARC_SPLINE_1_seg_2d_s
{
    int    tag;
    int    d04;
    double d08;
    double d10;
    double d18;
    double d20;
    double d28;
    double d30;
    double d38;
    double d40;
    double d48;
    double d50;
};

extern "C" void sub_180002020(ARC_SPLINE_1_seg_2d_s* a1, ARC_SPLINE_1_seg_2d_s* a2, double a3,
                              double* a4, int a5, int a6, int a7, int* a8,
                              ARC_SPLINE_1_seg_2d_s* a9, UGS::Math::Point2* a10);

void __cdecl ARC_SPLINE_cre_circle_tangent_to_2_circles_and_given_radius_2d(
    ARC_SPLINE_1_seg_2d_s* a1, ARC_SPLINE_1_seg_2d_s* a2, double a3, double* a4, int a5,
    int a6, int a7, int* a8, ARC_SPLINE_1_seg_2d_s* a9, UGS::Math::Point2* a10)
{
    if (a7 != 0)
    {
        return sub_180002020(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
    }

    double pts_tmp[8];
    {
        volatile double* q = pts_tmp;
        for (long long k = 4; k != 0; --k)
        {
            q[0] = 0.0;
            q[1] = 0.0;
            q += 2;
        }
    }
    ARC_SPLINE_1_seg_2d_s seg_buf[2];
    volatile double*      p0 = (volatile double*)a10;
    volatile double*      p1 = p0 + 1;
    volatile double*      p2 = p0 + 2;
    volatile double*      p3 = p0 + 3;
    int                   total = 0;
    for (int i = 1; i <= 4; ++i)
    {
        int sel;
        if (i == 1)
            sel = -3;
        else if (i == 2)
            sel = 1;
        else if (i == 3)
            sel = -1;
        else
            sel = 3;

        sub_180002020(a1, a2, a3, a4, a5, a6, sel, &a7, seg_buf, (UGS::Math::Point2*)pts_tmp);

        if (a7 > 0)
        {
            a9[total] = seg_buf[0];
            *p0 = pts_tmp[0];
            *p1 = pts_tmp[1];
            *p2 = pts_tmp[2];
            *p3 = pts_tmp[3];
            p0 += 4;
            p1 += 4;
            p2 += 4;
            p3 += 4;
            ++total;
            if (a7 > 1)
            {
                a9[total] = seg_buf[1];
                *p0 = pts_tmp[4];
                *p1 = pts_tmp[5];
                *p2 = pts_tmp[6];
                *p3 = pts_tmp[7];
                p0 += 4;
                p1 += 4;
                p2 += 4;
                p3 += 4;
                ++total;
            }
        }
    }
    *a8 = total;
}
