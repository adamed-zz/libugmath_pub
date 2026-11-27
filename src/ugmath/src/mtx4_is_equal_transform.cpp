






















#include "ugmath/matrix3.h"
#include "ugmath/mtx4.h"
#include "ugmath/tolerance.h"

bool MTX4_is_equal_transform(UGS::Math::TransformMatrix* a1,
                             UGS::Math::TransformMatrix* a2)
{
    return MTX4_is_equal_transform(a1, a2, 1.0e-10, EQ_ask_length_tolerance(), 1.0e-10) != 0;
}
