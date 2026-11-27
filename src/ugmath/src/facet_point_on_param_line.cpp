









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

void __cdecl FACET_point_on_param_line(UGS::Math::Point3* p, UGS::Math::Vector3* v,
                                       double t, UGS::Math::Point3* out)
{
    out->x = t * v->x + p->x;
    out->y = t * v->y + p->y;
    out->z = t * v->z + p->z;
}
