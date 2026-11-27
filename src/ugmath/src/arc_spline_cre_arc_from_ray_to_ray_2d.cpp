






#include <emmintrin.h>

namespace UGS { namespace Math {
struct alignas(16) Point2 { double x; double y; };
struct alignas(16) Vector2 { double x; double y; };
} }

struct ARC_SPLINE_1_seg_2d_s
{
    double f0; double f1; double f2; double f3; double f4;
    double f5; double f6; double f7; double f8; double f9; double f10;
};


extern "C" double tan(double);
extern "C" double fabs(double);

void ARC_SPLINE_inter_line_line_2d(
    double const* const radius,
    UGS::Math::Point2 const* p1,
    UGS::Math::Point2 const* p2,
    int which,
    UGS::Math::Vector2* d1,
    UGS::Math::Vector2* d2,
    UGS::Math::Point2* lin_pt,
    double* lin_parm,
    double* scratch,
    int* error);

double ARC_SPLINE_ask_central_angle_between_tangents_2d(
    UGS::Math::Vector2* d1,
    UGS::Math::Vector2* d2,
    int* dir);

void ARC_SPLINE_cre_circle_from_chord_end_data_2d(
    UGS::Math::Point2 const* pt1,
    UGS::Math::Vector2 const* d1,
    UGS::Math::Point2 const* pt2,
    UGS::Math::Vector2 const* d2,
    int dir,
    double* tol,
    ARC_SPLINE_1_seg_2d_s* seg,
    int* status);

__declspec(dllimport) void ERROR_internal(const char* file, int line, const char* msg, ...);

void ARC_SPLINE_cre_arc_from_ray_to_ray_2d(
    UGS::Math::Point2* p1,
    UGS::Math::Vector2* d1,
    UGS::Math::Point2* p2,
    UGS::Math::Vector2* d2,
    double* radius,
    double tol,
    int* error,
    UGS::Math::Point2* lin_pt,
    double* const lin_parm,
    UGS::Math::Point2* arc_pt1,
    UGS::Math::Point2* arc_pt2,
    int* arc_dir,
    ARC_SPLINE_1_seg_2d_s* seg)
{
    *error = 0;
    lin_pt->x = 0.0;
    lin_pt->y = 0.0;
    lin_parm[0] = 0.0;
    lin_parm[1] = 0.0;
    arc_pt1->x = 0.0;
    arc_pt1->y = 0.0;
    arc_pt2->x = 0.0;
    arc_pt2->y = 0.0;
    *arc_dir = 1;
    seg->f0 = 0.0;
    seg->f1 = 0.0;
    seg->f2 = 0.0;
    seg->f3 = 0.0;
    seg->f4 = 0.0;
    seg->f5 = 0.0;
    seg->f6 = 0.0;
    seg->f7 = 0.0;
    seg->f8 = 0.0;
    seg->f9 = 0.0;
    seg->f10 = 0.0;

    double scratch;
    ARC_SPLINE_inter_line_line_2d(radius, p1, p2, 1, d1, d2, lin_pt, lin_parm, &scratch, error);
    if (*error != 0)
        return;

    const double angle = ARC_SPLINE_ask_central_angle_between_tangents_2d(d1, d2, arc_dir);
    const double tan_half = tan(fabs(angle) * 0.008726646259971641);
    const double t = tan_half * tol;
    double tol_copy = tol;

    const __m128d tn = _mm_set1_pd(-t);
    const __m128d tp = _mm_set1_pd(t);
    _mm_storeu_pd(&arc_pt1->x,
                  _mm_add_pd(_mm_mul_pd(tn, _mm_loadu_pd(&d1->x)),
                             _mm_loadu_pd(&lin_pt->x)));
    _mm_storeu_pd(&arc_pt2->x,
                  _mm_add_pd(_mm_mul_pd(tp, _mm_loadu_pd(&d2->x)),
                             _mm_loadu_pd(&lin_pt->x)));

    ARC_SPLINE_cre_circle_from_chord_end_data_2d(arc_pt1, d1, arc_pt2, d2, *arc_dir, &tol_copy, seg, reinterpret_cast<int*>(&scratch));
    if (*reinterpret_cast<int*>(&scratch) != 0)
    {
        ERROR_internal(
            "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\arc_spline_apollonian_constructions.c",
            16085,
            "The call to ARC_SPLINE_cre_circle_from_chord_end_data_2d failed.");
        __debugbreak();
    }
}
