







#include <cmath>
#include <intrin.h>

struct ARC_SPLINE_1_seg_2d_s
{
    int    m_type;
    int    m_sense;
    double m_org_x;
    double m_org_y;
    double m_inclin_deg;
    double m_parm0_deg;
    double m_parm1_deg;
    double m_pt_x;
    double m_pt_y;
    double m_unk_40;
    double m_radius;
};

namespace UGS
{
namespace Math
{
struct Point2  { double x; double y; };
struct Vector2 { double x; double y; };
}
}



#ifdef ARC_DEV_SELFTEST
extern "C" void ERROR_internal(const char* file, int line, const char* msg, ...);
#else
__declspec(dllimport) void ERROR_internal(const char* file, int line, const char* msg, ...);
#endif


void ARC_SPLINE_evaluate_arc_seg_2d(struct ARC_SPLINE_1_seg_2d_s* seg, int index, double parm,
                                    UGS::Math::Point2* pt, UGS::Math::Vector2* tan, int* status);
void ARC_SPLINE_cre_circle_from_point_tangent_radius_2d(const UGS::Math::Point2* pt,
                                                        const UGS::Math::Vector2* tan,
                                                        double radius, int sense,
                                                        struct ARC_SPLINE_1_seg_2d_s* seg);

void ARC_SPLINE_reverse_parm_of_arc_2d(struct ARC_SPLINE_1_seg_2d_s* a1)
{
    int v1 = *((int*)a1 + 1);
    UGS::Math::Point2 v11;
    _mm_storeu_ps((float*)&v11, _mm_loadu_ps((const float*)((char*)a1 + 8)));
    double v3 = *((double*)a1 + 3) * 0.01745329251994328;
    double v4 = *((double*)a1 + 4);
    UGS::Math::Vector2 v10;
    v10.x = std::cos(v3);
    double v5 = std::sin(v3);
    bool v6 = *((int*)a1) == 0;
    double v7 = *((double*)a1 + 9);
    v10.y = v5;
    if (!v6)
    {
        UGS::Math::Point2 v13;
        UGS::Math::Vector2 v12;
        int v14;
        ARC_SPLINE_evaluate_arc_seg_2d(a1, 0, v4, &v13, &v12, &v14);
        if (v14 > 0)
        {
            ERROR_internal(
                "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\arc_spline_apollonian_constructions.c",
                14205,
                "The function ARC_SPLINE_evaluate_1_seg_2d failed.");
            __debugbreak();
            __assume(0);
        }
    }


    const __m128 kSignMask = _mm_castsi128_ps(
        _mm_set_epi64x((long long)0x8000000000000000ULL, (long long)0x8000000000000000ULL));
    __m128d v8 = _mm_castps_pd(_mm_xor_ps(_mm_loadu_ps((const float*)&v10), kSignMask));
    _mm_store_sd(&v10.x, v8);
    _mm_store_sd(&v10.y, _mm_unpackhi_pd(v8, v8));
    ARC_SPLINE_cre_circle_from_point_tangent_radius_2d(&v11, &v10, v7, -v1, a1);
    double v9;
    if (v1 == -1)
        v9 = v4 + 360.0;
    else
        v9 = v4 - 360.0;
    *((double*)a1 + 4) = v9;
}
