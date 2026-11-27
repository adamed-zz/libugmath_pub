#include "ugmath/mc_ops.h"












double __cdecl MC_triple_product(double* const a1, double* const a2, double* const a3)
{
    return (*a2 * a1[2] - *a1 * a2[2]) * a3[1]
         + (a2[2] * a1[1] - a2[1] * a1[2]) * *a3
         + (*a1 * a2[1] - *a2 * a1[1]) * a3[2];
}
















double __cdecl MC_determinant(double (*const m)[4])
{
    return m[0][0] * m[1][1] * m[2][2]
         + m[0][1] * m[1][2] * m[2][0]
         + m[0][2] * m[1][0] * m[2][1]
         - m[1][1] * m[2][0] * m[0][2]
         - m[2][1] * m[1][2] * m[0][0]
         - m[1][0] * m[2][2] * m[0][1];
}










void __cdecl MC_apply_transform_to_point(double (* const a1)[4], double* const a2, double* const a3)
{
    *a3 = (*a1)[1] * a2[1] + (*a1)[0] * *a2 + (*a1)[2] * a2[2] + (*a1)[3];
    a3[1] = (*a1)[5] * a2[1] + (*a1)[4] * *a2 + (*a1)[6] * a2[2] + (*a1)[7];
    a3[2] = (*a1)[9] * a2[1] + (*a1)[8] * *a2 + (*a1)[10] * a2[2] + (*a1)[11];
}









void __cdecl MC_apply_transform_to_vector(double (* const a1)[4], double * const a2, double * const a3)
{
    *a3 = (*a1)[1] * a2[1] + (*a1)[0] * *a2 + (*a1)[2] * a2[2];
    a3[1] = (*a1)[5] * a2[1] + (*a1)[4] * *a2 + (*a1)[6] * a2[2];
    a3[2] = (*a1)[9] * a2[1] + (*a1)[8] * *a2 + (*a1)[10] * a2[2];
}
