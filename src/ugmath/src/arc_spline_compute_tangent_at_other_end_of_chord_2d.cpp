















namespace UGS
{
namespace Math
{
struct Point2
{
    double x;
    double y;
};
struct Vector2
{
    double x;
    double y;
};
}
}

struct ARC_SPLINE_1_seg_2d_s
{
    int tag;
};


void ARC_SPLINE_cre_circle_thru_pt_and_tangent_to_line_at_pt_2d(
    const UGS::Math::Point2*  a1,
    const UGS::Math::Vector2* a2,
    const UGS::Math::Point2*  a3,
    const double* const       a4,
    ARC_SPLINE_1_seg_2d_s*    a6,
    int*                      a7);

void ARC_SPLINE_ask_parm_at_a_point_2d(
    const ARC_SPLINE_1_seg_2d_s* a1,
    const UGS::Math::Point2*     a2,
    const double* const          a3,
    UGS::Math::Point2*           a4,
    double*                      a5,
    int*                         a6,
    int*                         a7);

void ARC_SPLINE_evaluate_arc_seg_2d(
    const ARC_SPLINE_1_seg_2d_s* a1,
    int                          a2,
    double                       a3,
    UGS::Math::Point2*           a4,
    UGS::Math::Vector2*          a5,
    int*                         a6);

int VEC2_unitize(
    const UGS::Math::Vector2* a1,
    double                    a2,
    double*                   a3,
    UGS::Math::Vector2*       a4);


__declspec(dllimport) void ERROR_internal(const char* file, int line, const char* msg, ...);

void ARC_SPLINE_compute_tangent_at_other_end_of_chord_2d(
    UGS::Math::Point2*  a1,
    UGS::Math::Vector2* a2,
    UGS::Math::Point2*  a3,
    double* const       a4,
    UGS::Math::Vector2* a5,
    ARC_SPLINE_1_seg_2d_s* a6)
{
    int status = 0;
    ARC_SPLINE_cre_circle_thru_pt_and_tangent_to_line_at_pt_2d(a1, a2, a3, a4, a6, &status);

    const int tag = a6->tag;
    if (tag == 0)
    {

        a5->x = a2->x;
        a5->y = a2->y;
    }
    else if (tag == 1)
    {
        int               dummy = 0;
        double            parm  = 0.0;
        UGS::Math::Point2 pt    = {};
        ARC_SPLINE_ask_parm_at_a_point_2d(a6, a3, a4, &pt, &parm, &dummy, &status);
        if (status > 0)
        {
            ERROR_internal(
                "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\arc_spline_apollonian_constructions.c",
                18225,
                "The call to ARC_SPLINE_ask_parm_at_a_point_2d failed.");
            __debugbreak();
            __assume(0);
        }
        ARC_SPLINE_evaluate_arc_seg_2d(a6, 1, parm, &pt, a5, &status);
        if (status > 0)
        {
            ERROR_internal(
                "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\arc_spline_apollonian_constructions.c",
                18236,
                "The call to ARC_SPLINE_evaluate_arc_seg_2d failed.");
            __debugbreak();
            __assume(0);
        }
    }
    else
    {
        ERROR_internal(
            "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\arc_spline_apollonian_constructions.c",
            18240,
            "Unexpected conic arc type.");
        __debugbreak();
        __assume(0);
    }

    double length;
    VEC2_unitize(a5, 1.0e-10, &length, a5);
}
