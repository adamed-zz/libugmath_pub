









struct ARC_SPLINE_1_seg_2d_s;
namespace UGS { namespace Math { struct Point2; } }

double ARC_SPLINE_ask_power_of_a_point_2d(const struct UGS::Math::Point2* p,
                                          const struct ARC_SPLINE_1_seg_2d_s* seg)
{
    const double* s = reinterpret_cast<const double*>(seg);
    const double* q = reinterpret_cast<const double*>(p);
    double fx = s[5];
    double fy = s[6];
    double v = *reinterpret_cast<const unsigned int*>(seg) == 0 ? 1.0e19 : s[9];
    return (fx - q[0]) * (fx - q[0])
         + (fy - q[1]) * (fy - q[1])
         - v * v;
}
