





















#include "ugmath/matrix3.h"
#include "ugmath/mtx3.h"

#include <cmath>

#include "mtx3_rpy_extract.h"

void MTX3_ask_roll_pitch_yaw(const UGS::Math::Matrix3* m, double* roll, double* pitch,
                             double* yaw) {
    double v11;
    double v12;
    double v13;
    double v14;
    double v15;
    double v16;

    MTX3_rpy_extract(m, &v14, &v15, &v16, &v11, &v12, &v13);

    *roll = atan2(v15, v14);
    *pitch = atan2(v11, v16);
    *yaw = atan2(v13, v12);
}
