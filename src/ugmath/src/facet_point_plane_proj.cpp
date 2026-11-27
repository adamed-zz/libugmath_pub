








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

struct Vector3
{
    double x;
    double y;
    double z;
};
}
}


int FACET_line_int_plane(UGS::Math::Point3* p, UGS::Math::Point3* q, UGS::Math::Vector3* n,
                         double d, UGS::Math::Point3* out, double* t);

void FACET_point_plane_proj(UGS::Math::Point3* a1, UGS::Math::Vector3* a2, double a3,
                            UGS::Math::Point3* a4)
{
    UGS::Math::Point3 tmp;
    tmp.x = a1->x + a2->x;
    tmp.y = a1->y + a2->y;
    tmp.z = a1->z + a2->z;
    double v7;
    FACET_line_int_plane(a1, &tmp, a2, a3, a4, &v7);
}
