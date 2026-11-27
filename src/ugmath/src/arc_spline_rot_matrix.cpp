

















#include "ugmath/arc_spline.h"

void ARC_SPLINE_cre_matrix_of_rotation_around_axis(UGS::Math::Vector3* axis,
                                                   double angle_deg,
                                                   UGS::Math::Matrix3* out)
{
    MTX3_rot_about_axis(angle_deg * 0.01745329251994328, axis, out);
}
