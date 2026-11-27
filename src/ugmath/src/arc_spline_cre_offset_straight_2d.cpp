




















#include <emmintrin.h>

struct ARC_SPLINE_1_seg_2d_s
{
    int    type;
    int    sense;
    double x;
    double y;
    double pad18[4];
    double dx;
    double dy;
    double parm;
};

namespace UGS {
namespace Math {
struct Point2 { double x, y; };
struct Vector2 { double x, y; };
}
}


__declspec(dllimport) void ERROR_internal(const char* file_name, int line,
                                                     const char* message, ...);


void ARC_SPLINE_cre_strt_seg_2d(const UGS::Math::Point2& strt,
                                const UGS::Math::Point2& end,
                                const UGS::Math::Vector2& dir,
                                struct ARC_SPLINE_1_seg_2d_s* seg);

void ARC_SPLINE_cre_offset_straight_2d(struct ARC_SPLINE_1_seg_2d_s* a1, double a2,
                                       struct ARC_SPLINE_1_seg_2d_s* a3)
{
    if (!a1)
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\arc_spline_apollonian_constructions.c",
                       14475, "The input segment is not available.");
        __debugbreak();
        __assume(0);
    }
    if (a1->type)
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\arc_spline_apollonian_constructions.c",
                       14478, "The input segment is not of straight type.");
        __debugbreak();
        __assume(0);
    }


    const double dyv = a1->dy;
    const double yv  = a1->y;
    const double q2y = dyv * a1->parm + yv;
    const double nx  = -dyv * a2;
    const double dxv = a1->dx;
    const double q2x = dxv * a1->parm + a1->x;
    const double ny  = dxv * a2;


    const __m128d np = _mm_unpacklo_pd(_mm_set_sd(nx), _mm_set_sd(ny));
    const __m128d q1p = _mm_add_pd(
        _mm_unpacklo_pd(_mm_load_sd(&a1->x), _mm_set_sd(yv)), np);

    UGS::Math::Point2 strt;
    strt.x = _mm_cvtsd_f64(q1p);
    strt.y = _mm_cvtsd_f64(_mm_unpackhi_pd(q1p, q1p));

    const __m128d q2p = _mm_add_pd(
        _mm_unpacklo_pd(_mm_set_sd(q2x), _mm_set_sd(q2y)),
        _mm_unpacklo_pd(_mm_set_sd(nx), _mm_set_sd(ny)));

    UGS::Math::Point2 end;
    end.x = _mm_cvtsd_f64(q2p);
    end.y = _mm_cvtsd_f64(_mm_unpackhi_pd(q2p, q2p));

    UGS::Math::Vector2 dir;
    dir.x = dxv;
    dir.y = dyv;

    ARC_SPLINE_cre_strt_seg_2d(strt, end, dir, a3);
}
