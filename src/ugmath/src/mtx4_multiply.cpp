















#include <emmintrin.h>

namespace UGS
{
namespace Math
{

struct TransformMatrix
{
    double m[4][4];
};

}
}

void MTX4_multiply(const UGS::Math::TransformMatrix *a1,
                   const UGS::Math::TransformMatrix *a2,
                   UGS::Math::TransformMatrix *a3)
{
    const double *A = &a1->m[0][0];
    const double *B = &a2->m[0][0];

    UGS::Math::TransformMatrix t;

    t.m[0][0] = _mm_cvtsd_f64(_mm_add_sd(_mm_add_sd(_mm_add_sd(_mm_mul_sd(_mm_load_sd(&B[0]), _mm_load_sd(&A[0])),
                _mm_mul_sd(_mm_load_sd(&B[1]), _mm_load_sd(&A[4]))),
                _mm_mul_sd(_mm_load_sd(&B[2]), _mm_load_sd(&A[8]))),
                _mm_mul_sd(_mm_load_sd(&B[3]), _mm_load_sd(&A[12]))));

    t.m[0][1] = _mm_cvtsd_f64(_mm_add_sd(_mm_add_sd(_mm_add_sd(_mm_mul_sd(_mm_load_sd(&A[1]), _mm_load_sd(&B[0])),
                _mm_mul_sd(_mm_load_sd(&A[5]), _mm_load_sd(&B[1]))),
                _mm_mul_sd(_mm_load_sd(&A[9]), _mm_load_sd(&B[2]))),
                _mm_mul_sd(_mm_load_sd(&A[13]), _mm_load_sd(&B[3]))));

    t.m[0][2] = _mm_cvtsd_f64(_mm_add_sd(_mm_add_sd(_mm_add_sd(_mm_mul_sd(_mm_load_sd(&A[2]), _mm_load_sd(&B[0])),
                _mm_mul_sd(_mm_load_sd(&A[6]), _mm_load_sd(&B[1]))),
                _mm_mul_sd(_mm_load_sd(&A[10]), _mm_load_sd(&B[2]))),
                _mm_mul_sd(_mm_load_sd(&A[14]), _mm_load_sd(&B[3]))));

    t.m[0][3] = _mm_cvtsd_f64(_mm_add_sd(_mm_add_sd(_mm_add_sd(_mm_mul_sd(_mm_load_sd(&A[3]), _mm_load_sd(&B[0])),
                _mm_mul_sd(_mm_load_sd(&A[7]), _mm_load_sd(&B[1]))),
                _mm_mul_sd(_mm_load_sd(&A[11]), _mm_load_sd(&B[2]))),
                _mm_mul_sd(_mm_load_sd(&A[15]), _mm_load_sd(&B[3]))));

    t.m[1][0] = _mm_cvtsd_f64(_mm_add_sd(_mm_add_sd(_mm_add_sd(_mm_mul_sd(_mm_load_sd(&B[4]), _mm_load_sd(&A[0])),
                _mm_mul_sd(_mm_load_sd(&B[5]), _mm_load_sd(&A[4]))),
                _mm_mul_sd(_mm_load_sd(&B[6]), _mm_load_sd(&A[8]))),
                _mm_mul_sd(_mm_load_sd(&B[7]), _mm_load_sd(&A[12]))));

    t.m[1][1] = _mm_cvtsd_f64(_mm_add_sd(_mm_add_sd(_mm_add_sd(_mm_mul_sd(_mm_load_sd(&B[4]), _mm_load_sd(&A[1])),
                _mm_mul_sd(_mm_load_sd(&B[5]), _mm_load_sd(&A[5]))),
                _mm_mul_sd(_mm_load_sd(&B[6]), _mm_load_sd(&A[9]))),
                _mm_mul_sd(_mm_load_sd(&B[7]), _mm_load_sd(&A[13]))));

    t.m[1][2] = _mm_cvtsd_f64(_mm_add_sd(_mm_add_sd(_mm_add_sd(_mm_mul_sd(_mm_load_sd(&B[4]), _mm_load_sd(&A[2])),
                _mm_mul_sd(_mm_load_sd(&B[5]), _mm_load_sd(&A[6]))),
                _mm_mul_sd(_mm_load_sd(&B[6]), _mm_load_sd(&A[10]))),
                _mm_mul_sd(_mm_load_sd(&B[7]), _mm_load_sd(&A[14]))));

    t.m[1][3] = _mm_cvtsd_f64(_mm_add_sd(_mm_add_sd(_mm_add_sd(_mm_mul_sd(_mm_load_sd(&B[4]), _mm_load_sd(&A[3])),
                _mm_mul_sd(_mm_load_sd(&B[5]), _mm_load_sd(&A[7]))),
                _mm_mul_sd(_mm_load_sd(&B[6]), _mm_load_sd(&A[11]))),
                _mm_mul_sd(_mm_load_sd(&B[7]), _mm_load_sd(&A[15]))));

    t.m[2][0] = _mm_cvtsd_f64(_mm_add_sd(_mm_add_sd(_mm_add_sd(_mm_mul_sd(_mm_load_sd(&B[8]), _mm_load_sd(&A[0])),
                _mm_mul_sd(_mm_load_sd(&B[9]), _mm_load_sd(&A[4]))),
                _mm_mul_sd(_mm_load_sd(&B[10]), _mm_load_sd(&A[8]))),
                _mm_mul_sd(_mm_load_sd(&B[11]), _mm_load_sd(&A[12]))));

    t.m[2][1] = _mm_cvtsd_f64(_mm_add_sd(_mm_add_sd(_mm_add_sd(_mm_mul_sd(_mm_load_sd(&B[8]), _mm_load_sd(&A[1])),
                _mm_mul_sd(_mm_load_sd(&B[9]), _mm_load_sd(&A[5]))),
                _mm_mul_sd(_mm_load_sd(&B[10]), _mm_load_sd(&A[9]))),
                _mm_mul_sd(_mm_load_sd(&B[11]), _mm_load_sd(&A[13]))));

    t.m[2][2] = _mm_cvtsd_f64(_mm_add_sd(_mm_add_sd(_mm_add_sd(_mm_mul_sd(_mm_load_sd(&B[8]), _mm_load_sd(&A[2])),
                _mm_mul_sd(_mm_load_sd(&B[9]), _mm_load_sd(&A[6]))),
                _mm_mul_sd(_mm_load_sd(&B[10]), _mm_load_sd(&A[10]))),
                _mm_mul_sd(_mm_load_sd(&B[11]), _mm_load_sd(&A[14]))));

    t.m[2][3] = _mm_cvtsd_f64(_mm_add_sd(_mm_add_sd(_mm_add_sd(_mm_mul_sd(_mm_load_sd(&B[8]), _mm_load_sd(&A[3])),
                _mm_mul_sd(_mm_load_sd(&B[9]), _mm_load_sd(&A[7]))),
                _mm_mul_sd(_mm_load_sd(&B[10]), _mm_load_sd(&A[11]))),
                _mm_mul_sd(_mm_load_sd(&B[11]), _mm_load_sd(&A[15]))));

    t.m[3][0] = _mm_cvtsd_f64(_mm_add_sd(_mm_add_sd(_mm_add_sd(_mm_mul_sd(_mm_load_sd(&B[12]), _mm_load_sd(&A[0])),
                _mm_mul_sd(_mm_load_sd(&B[13]), _mm_load_sd(&A[4]))),
                _mm_mul_sd(_mm_load_sd(&B[14]), _mm_load_sd(&A[8]))),
                _mm_mul_sd(_mm_load_sd(&B[15]), _mm_load_sd(&A[12]))));

    t.m[3][1] = _mm_cvtsd_f64(_mm_add_sd(_mm_add_sd(_mm_add_sd(_mm_mul_sd(_mm_load_sd(&B[12]), _mm_load_sd(&A[1])),
                _mm_mul_sd(_mm_load_sd(&B[13]), _mm_load_sd(&A[5]))),
                _mm_mul_sd(_mm_load_sd(&B[14]), _mm_load_sd(&A[9]))),
                _mm_mul_sd(_mm_load_sd(&B[15]), _mm_load_sd(&A[13]))));

    t.m[3][2] = _mm_cvtsd_f64(_mm_add_sd(_mm_add_sd(_mm_add_sd(_mm_mul_sd(_mm_load_sd(&B[12]), _mm_load_sd(&A[2])),
                _mm_mul_sd(_mm_load_sd(&B[13]), _mm_load_sd(&A[6]))),
                _mm_mul_sd(_mm_load_sd(&B[14]), _mm_load_sd(&A[10]))),
                _mm_mul_sd(_mm_load_sd(&B[15]), _mm_load_sd(&A[14]))));

    t.m[3][3] = _mm_cvtsd_f64(_mm_add_sd(_mm_add_sd(_mm_add_sd(_mm_mul_sd(_mm_load_sd(&B[12]), _mm_load_sd(&A[3])),
                _mm_mul_sd(_mm_load_sd(&B[13]), _mm_load_sd(&A[7]))),
                _mm_mul_sd(_mm_load_sd(&B[14]), _mm_load_sd(&A[11]))),
                _mm_mul_sd(_mm_load_sd(&B[15]), _mm_load_sd(&A[15]))));

    *a3 = t;
}
