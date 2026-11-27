








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
    int,
    UGS::Math::Point3*,
    int,
    double,
    UGS::Math::Point3*,
    UGS::Math::Vector3*,
    UGS::Math::Point3*,
    double*,
    int*,
    double*,
    CSYS_s*);


void __cdecl LSFIT_circle_to_points_3d(
    UGS::Math::Point3*  pts,
    int                 count,
    UGS::Math::Point3*  a3,
    UGS::Math::Vector3* a4,
    UGS::Math::Point3*  a5,
    double*             a6,
    int*                a7,
    double*             a8,
    CSYS_s*             a9)
{
    LSFIT_circle_to_points_3d(0, pts, count, 0.01, a3, a4, a5, a6, a7, a8, a9);
}
