


















#include "ugmath/matrix3.h"
#include "ugmath/mtx3.h"

#include <cmath>

void MTX3_init_roll_pitch_yaw(double roll, double pitch, double yaw,
                              UGS::Math::Matrix3* out)
{
    MTX3_init_roll_pitch_yaw_impl(std::cos(roll), std::sin(roll), std::cos(pitch),
                                  std::sin(pitch), std::cos(yaw), std::sin(yaw), out);
}
