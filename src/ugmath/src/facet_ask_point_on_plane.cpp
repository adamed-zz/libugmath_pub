






















namespace UGS {
namespace Math {

struct Vector3 { double x, y, z; };
struct Point3  { double x, y, z; };

}
}

int VEC3_unitize(const UGS::Math::Vector3* v, double eps, double* len_out, UGS::Math::Vector3* out);

void FACET_ask_point_on_plane(UGS::Math::Vector3* normal, double d, UGS::Math::Point3* out)
{
    UGS::Math::Vector3 tmp = { 0.0, 0.0, 0.0 };
    double len;
    VEC3_unitize(normal, 1e-10, &len, &tmp);
    const double nd = -d;
    out->x = tmp.x * nd;
    out->y = tmp.y * nd;
    const double z = *(const volatile double*)&tmp.z;
    out->z = z * nd;
}
