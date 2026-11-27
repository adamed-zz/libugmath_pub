









namespace UGS {
namespace Math {


struct Point3
{
    double x;
    double y;
    double z;
};

struct Vector3
{
    double x;
    double y;
    double z;
};

}
}

struct CSYS_s;


void __cdecl LSFIT_circle_to_points_3d(
    int                 count,
    UGS::Math::Point3*  pts,
    int                 closed,
    double              tolerance,
    UGS::Math::Point3*  center,
    UGS::Math::Vector3* normal,
    UGS::Math::Point3*  a6,
    double*             a7,
    int*                a8,
    double*             a9,
    CSYS_s*             a10);


void __cdecl LSFIT_circle_to_points_3d(
    int                 count,
    UGS::Math::Point3*  pts,
    int                 closed,
    UGS::Math::Point3*  center,
    UGS::Math::Vector3* normal,
    UGS::Math::Point3*  a6,
    double*             a7,
    int*                a8,
    double*             a9,
    CSYS_s*             a10)
{
    LSFIT_circle_to_points_3d(count, pts, closed, 0.01, center, normal, a6, a7, a8, a9, a10);
}
