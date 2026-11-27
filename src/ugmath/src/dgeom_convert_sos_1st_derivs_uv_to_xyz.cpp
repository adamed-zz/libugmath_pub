


















#include <cstring>


struct PLN3_s {
    double origin[3];
    double normal[3];
};


namespace UGS {
namespace Math {
struct Point3 {
    double x;
    double y;
    double z;
};
struct Vector3 {
    double x;
    double y;
    double z;
};
}
}

bool __cdecl PLN3_init_from_equation(PLN3_s& plane, const double* const equation);
int __cdecl PLN3_intersect_plane(const PLN3_s* plane1, const PLN3_s* plane2,
                                 UGS::Math::Point3& point, UGS::Math::Vector3& direction);
bool __cdecl PNT3_proj_to_plane(const UGS::Math::Point3* point, const PLN3_s* plane,
                                UGS::Math::Point3* out);

bool __cdecl DGEOM_convert_SOS_1st_derivs_uv_to_xyz(
    const double* const a1, const double* const a2, const double* const a3,
    const double* const a4, double* const a5, double* const a6, double* const a7)
{
    UGS::Math::Point3 out;
    for (int k = 0; k < 3; ++k) {
        const double u1 = a1[k];
        const double u2 = a2[k];
        PLN3_s p1 = {};
        PLN3_s p2 = {};
        double eq1[4] = { a3[0], a3[1], a3[2], u1 };
        double eq2[4] = { a4[0], a4[1], a4[2], u2 };
        PLN3_init_from_equation(p1, eq1);
        PLN3_init_from_equation(p2, eq2);

        UGS::Math::Point3 pt = { 0.0, 0.0, 0.0 };
        UGS::Math::Vector3 dir = { 0.0, 0.0, 0.0 };
        int rc = PLN3_intersect_plane(&p1, &p2, pt, dir);
        if (rc == 2) {
            memcpy(&out, &pt, sizeof(out));
        } else if (rc == 3) {
            double eq3[4] = { a3[0], a3[1], a3[2], u1 };
            PLN3_s p3 = {};
            if (!PLN3_init_from_equation(p3, eq3))
                return false;
            UGS::Math::Point3 org = { 0.0, 0.0, 0.0 };
            PNT3_proj_to_plane(&org, &p3, &out);
        } else {
            return false;
        }
        a5[k] = out.x;
        a6[k] = out.y;
        a7[k] = out.z;
    }
    return true;
}
