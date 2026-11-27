










namespace UGS { namespace Math { struct Point3; } }

namespace UGS { namespace Math {
struct Point3
{
    double c[3];
};
} }



void ARC_SPLINE_convert_circle_to_3d_pt(UGS::Math::Point3* src, double r, UGS::Math::Point3* dst)
{
    dst->c[0] = src->c[0];
    dst->c[1] = src->c[1];
    dst->c[2] = src->c[0] * src->c[0] + src->c[1] * src->c[1] - r * r;
}
