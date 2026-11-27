


















#include "ugmath/matrix3.h"
#include "ugmath/mtx3.h"

bool MTX3_init_tol(const UGS::Math::Vector3* a1, const UGS::Math::Vector3* a2,
                   UGS::Math::Matrix3* a3)
{
    return mtx3_init_common(a1, a2, a3, 1) == 1;
}
