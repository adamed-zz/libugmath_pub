













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



extern "C" void sub_180001B00(double* c1, double r1, unsigned long long* c2, double r2,
                              double* pt, int* n_out, UGS::Math::Point3* pts_out);


void ARC_SPLINE_convert_3d_pt_to_circle_2d(UGS::Math::Point3* p, bool* created,
                                           ARC_SPLINE_1_seg_2d_s* seg);

void __cdecl ARC_SPLINE_cre_circle_tangent_to_2_circles_and_a_pt(
    UGS::Math::Point3* a1, double a2, UGS::Math::Point3* a3, double a4, UGS::Math::Point3* a5,
    int* a6, ARC_SPLINE_1_seg_2d_s* a7)
{
    UGS::Math::Point3 pts[4];
    {


        volatile double* q = (volatile double*)pts;
        for (long long i = 4; i != 0; --i)
        {
            q[0] = 0.0;
            q[1] = 0.0;
            q[2] = 0.0;
            q += 3;
        }
    }
    ARC_SPLINE_1_seg_2d_s segs[4];
    int*                  out = a6;
    *out                       = 0;
    int n;
    sub_180001B00((double*)a1, a2, (unsigned long long*)a3, a4, (double*)a5, &n, pts);
    if (n > 0)
    {
        UGS::Math::Point3*     pp     = pts;
        ARC_SPLINE_1_seg_2d_s* sp     = segs;
        long long              remain = (unsigned int)n;
        do
        {
            ARC_SPLINE_convert_3d_pt_to_circle_2d(pp, (bool*)&n, sp);
            const char* s4 = (const char*)sp + 4;
            if (*(bool*)&n)
            {
                int            k = *out;
                *out             = k + 1;
                volatile char* d = (volatile char*)(a7 + k);

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
