#include "ugmath/tolerance.h"













double __cdecl EQ_ask_length_tolerance(void)
{
    return UGS::Math::GetThreadTolerances()->ask_length_tolerance();
}
