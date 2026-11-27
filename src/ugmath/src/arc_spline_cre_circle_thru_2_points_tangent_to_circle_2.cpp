












namespace UGS
{
namespace Math
{
struct Point3
{
    double x;
    double y;
    double z;
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

extern "C" void sub_180002A30(UGS::Math::Point3* a1, long long a2, double* a3, double* a4,
                              int* a5, UGS::Math::Point3* a6);

void ARC_SPLINE_convert_3d_pt_to_circle_2d(UGS::Math::Point3* p, bool* created,
                                           ARC_SPLINE_1_seg_2d_s* seg);

void __cdecl ARC_SPLINE_cre_circle_thru_2_points_tangent_to_circle_2(
    UGS::Math::Point3* a1, double a2, UGS::Math::Point3* a3, UGS::Math::Point3* a4, int* a5,
    ARC_SPLINE_1_seg_2d_s* a6)
{
    (void)a2;
    UGS::Math::Point3 pts[2];
    {


        volatile double* q = (volatile double*)pts;
        for (long long i = 2; i != 0; --i)
        {
            q[0] = 0.0;
            q[1] = 0.0;
            q[2] = 0.0;
            q += 3;
        }
    }
    ARC_SPLINE_1_seg_2d_s segs[2];
    int*                  out = a5;
    *out = 0;
    sub_180002A30(a1, 0, (double*)a3, (double*)a4, (int*)&a5, pts);
    if (*(int*)&a5 > 0)
    {
        UGS::Math::Point3*     pp      = pts;
        ARC_SPLINE_1_seg_2d_s* sp      = segs;
        long long              remain  = (unsigned int)*(int*)&a5;
        do
        {
            ARC_SPLINE_convert_3d_pt_to_circle_2d(pp, (bool*)&a5, sp);
            const char* s4 = (const char*)sp + 4;
            if (*(bool*)&a5)
            {
                int            k = *out;
                *out             = k + 1;
                volatile char* d = (volatile char*)(a6 + k);

                *(volatile int*)(d + 0)        = *(const int*)(s4 - 4);
                *(volatile int*)(d + 4)        = *(const int*)(s4);
                *(volatile long long*)(d + 8)  = *(const long long*)(s4 + 4);
                *(volatile long long*)(d + 16) = *(const long long*)(s4 + 12);
                *(volatile long long*)(d + 24) = *(const long long*)(s4 + 20);
                *(volatile long long*)(d + 32) = *(const long long*)(s4 + 28);
                *(volatile long long*)(d + 40) = *(const long long*)(s4 + 36);
                *(volatile long long*)(d + 48) = *(const long long*)(s4 + 44);
                *(volatile long long*)(d + 56) = *(const long long*)(s4 + 52);
                *(volatile long long*)(d + 64) = *(const long long*)(s4 + 60);
                *(volatile long long*)(d + 72) = *(const long long*)(s4 + 68);
                *(volatile long long*)(d + 80) = *(const long long*)(s4 + 76);
            }
            pp = (UGS::Math::Point3*)((const char*)pp + 0x18);
            ++sp;
            --remain;
        } while (remain);
    }
}
