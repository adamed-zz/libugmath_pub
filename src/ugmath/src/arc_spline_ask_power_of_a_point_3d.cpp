













namespace UGS { namespace Math { struct Point3; } }

namespace UGS { namespace Math {
struct Point3
{
    double c[3];
};
} }



double ARC_SPLINE_ask_power_of_a_point_3d(const UGS::Math::Point3* p1, const UGS::Math::Point3* p2, double r)
{
    double dx = p2->c[0] - p1->c[0];
    double dy = p2->c[1] - p1->c[1];
    double dz = p2->c[2] - p1->c[2];
    return dx * dx + dy * dy + dz * dz - r * r;
}
