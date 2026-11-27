








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
    int                 mode,
    UGS::Math::Point3*  pts,
    int                 count,
    double              tolerance,
    UGS::Math::Point3*  a4,
    UGS::Math::Vector3* a5,
    UGS::Math::Point3*  a6,
    double*             a7,
    int*                a8,
    double*             a9,
    CSYS_s*             csys);


void __cdecl LSFIT_circle_to_points_3d(
    UGS::Math::Point3*  pts,
    int                 count,
    double              tolerance,
    UGS::Math::Point3*  a4,
    UGS::Math::Vector3* a5,
    UGS::Math::Point3*  a6,
    double*             a7,
    int*                a8,
    double*             a9,
    CSYS_s*             csys)
{
    LSFIT_circle_to_points_3d(0, pts, count, tolerance, a4, a5, a6, a7, a8, a9, csys);
}
