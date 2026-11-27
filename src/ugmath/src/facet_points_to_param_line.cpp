




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

int __cdecl VEC3_unitize(const UGS::Math::Vector3* u, double tol, double* len_out,
                         UGS::Math::Vector3* out);

void __cdecl FACET_points_to_param_line(UGS::Math::Point3* p1, UGS::Math::Point3* p2,
                                        int flag, UGS::Math::Point3* out_pt,
                                        UGS::Math::Vector3* out_dir)
{
    UGS::Math::Vector3 dir;
    dir.z = p2->z - p1->z;
    dir.y = p2->y - p1->y;
    dir.x = p2->x - p1->x;
    *out_pt = *p1;
    if (flag == 1)
    {
        double len;
        if (VEC3_unitize(&dir, 1e-5, &len, out_dir) == 0)
        {
            *out_dir = dir;
        }
    }
    else
    {
        *out_dir = dir;
    }
}
