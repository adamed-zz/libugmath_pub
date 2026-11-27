



































namespace UGS
{
namespace Math
{
struct Point3
{
    double x, y, z;
};
struct Vector3
{
    double x, y, z;
};
}
}


struct PLN3_s;


int VEC3_unitize(const UGS::Math::Vector3* u, double tol, double* len_out,
                 UGS::Math::Vector3* out);



void ARC_SPLINE_ask_bisector_of_inscribed_angle(
    UGS::Math::Vector3* a1, UGS::Math::Vector3* a2, UGS::Math::Point3* a3,
    UGS::Math::Vector3* a4, double a5, double* a6, double* a7, int* a8,
    UGS::Math::Vector3* a9, PLN3_s* a10);

void ARC_SPLINE_ask_bisector_of_polygon_angle(
    UGS::Math::Point3* a1,
    UGS::Math::Point3* a2,
    UGS::Math::Point3* a3,
    UGS::Math::Vector3* a4,
    double a5,
    double* a6,
    double* a7,
    int* a8,
    UGS::Math::Vector3* a9,
    PLN3_s* a10)
{
    *a6 = 0.0;
    *a7 = 0.0;
    *a8 = -2;

    UGS::Math::Vector3 v21;
    if (a4)
    {
        v21.x = a4->x;
        v21.y = a4->y;
        v21.z = a4->z;
        double len;
        VEC3_unitize(&v21, 1.0e-10, &len, &v21);
    }
    else
    {
        v21.x = 0.0;
        v21.y = 0.0;
        v21.z = 1.0;
    }

    UGS::Math::Vector3 v24;
    v24.z = a2->z - a1->z;
    v24.x = a2->x - a1->x;
    v24.y = a2->y - a1->y;

    UGS::Math::Vector3 v23;
    v23.z = a3->z - a2->z;
    v23.x = a3->x - a2->x;
    v23.y = a3->y - a2->y;

    ARC_SPLINE_ask_bisector_of_inscribed_angle(&v24, &v23, a2, &v21, a5, a6,
                                               a7, a8, a9, a10);
}
