








namespace UGS {
namespace Math {


struct Point2
{
    double x;
    double y;
};

}
}


void __cdecl LSFIT_circle_to_points_2d(
    UGS::Math::Point2* pts,
    int                count,
    double             tolerance,
    UGS::Math::Point2* result,
    double*            a4,
    int*               a5,
    double*            a6);


void __cdecl LSFIT_circle_to_points_2d(
    UGS::Math::Point2* pts,
    int                count,
    UGS::Math::Point2* result,
    double*            a4,
    int*               a5,
    double*            a6)
{
    LSFIT_circle_to_points_2d(pts, count, 0.01, result, a4, a5, a6);
}
