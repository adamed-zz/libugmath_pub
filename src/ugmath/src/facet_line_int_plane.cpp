
















#include <math.h>
#include <emmintrin.h>

namespace UGS
{
namespace Math
{

struct Point3
{
    double x;
    double y;
    double z;
};

struct Vector3
{
    double x;
    double y;
    double z;
};

}
}

int __cdecl FACET_line_int_plane(UGS::Math::Point3* a1, UGS::Math::Point3* a2,
                                 UGS::Math::Vector3* a3, double a4,
                                 UGS::Math::Point3* a5, double* a6)
{
    UGS::Math::Point3 v14 = *a1;
    double v6 = a2->x - a1->x;
    double v7 = a2->y - a1->y;
    double v8 = a2->z - a1->z;
    double v9 = a3->y;
    double v10 = a3->z;
    double v11 = v9 * v7 + a3->x * v6 + v10 * v8;
    if (fabs(v11) < 1.0e-10)
        return 1;
    double v13 = -(a3->x * v14.x + v9 * v14.y + v10 * v14.z + a4) / v11;
    *a6 = v13;



    __m128d px = _mm_mul_sd(_mm_set_sd(v6), _mm_set_sd(v13));
    __m128d py = _mm_mul_sd(_mm_set_sd(v7), _mm_set_sd(v13));
    __m128d pz = _mm_mul_sd(_mm_set_sd(v8), _mm_set_sd(v13));
    a5->x = _mm_cvtsd_f64(_mm_add_sd(px, _mm_set_sd(v14.x)));
    a5->y = _mm_cvtsd_f64(_mm_add_sd(py, _mm_set_sd(v14.y)));
    a5->z = _mm_cvtsd_f64(_mm_add_sd(pz, _mm_set_sd(v14.z)));
    return 0;
}
