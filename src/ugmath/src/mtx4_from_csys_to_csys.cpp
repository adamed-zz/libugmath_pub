








struct CSYS_s
{
    double origin[3];
    double axes[3][3];
};

namespace UGS
{
namespace Math
{
struct TransformMatrix
{
    double m[16];
};
}
}


extern void sub_18009FBD0(const double* p1_origin, const double* p1_axes,
                          const double* p2_origin, const double* p2_axes,
                          double* out);

using UGS::Math::TransformMatrix;

TransformMatrix MTX4_from_csys_to_csys(const CSYS_s& csys1, const CSYS_s& csys2)
{
    TransformMatrix m;
    sub_18009FBD0(&csys1.origin[0], &csys1.axes[0][0],
                  &csys2.origin[0], &csys2.axes[0][0],
                  &m.m[0]);
    return m;
}
