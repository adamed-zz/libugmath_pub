













#include <emmintrin.h>

namespace UGS
{
namespace Math
{
struct Vector3
{
    double x;
    double y;
    double z;
};
}
}

void ARC_SPLINE_proj_vec_to_pln(UGS::Math::Vector3* a1, UGS::Math::Vector3* a2, UGS::Math::Vector3* a3)
{
    volatile double* pm = reinterpret_cast<volatile double*>(a2);
    volatile double* pn = reinterpret_cast<volatile double*>(a1);
    volatile double* po = reinterpret_cast<volatile double*>(a3);


    const double mx = pm[0];
    const double my = pm[1];
    const double mz = pm[2];
    const double nz = pn[2];
    const double nx = pn[0];
    const double ny = pn[1];


    const __m128d p1 = _mm_mul_sd(_mm_set_sd(mx), _mm_set_sd(nx));
    const __m128d p2 = _mm_mul_sd(_mm_set_sd(my), _mm_set_sd(ny));
    const __m128d p3 = _mm_mul_sd(_mm_set_sd(mz), _mm_set_sd(nz));
    const __m128d dsum = _mm_add_sd(_mm_add_sd(p1, p2), p3);
    const double t = -_mm_cvtsd_f64(dsum);


    const __m128d tv = _mm_set_sd(t);
    const double outx = _mm_cvtsd_f64(_mm_add_sd(_mm_mul_sd(_mm_set_sd(nx), tv), _mm_set_sd(mx)));
    const double outy = _mm_cvtsd_f64(_mm_add_sd(_mm_mul_sd(_mm_set_sd(ny), tv), _mm_set_sd(my)));
    const double outz = _mm_cvtsd_f64(_mm_add_sd(_mm_mul_sd(_mm_set_sd(nz), tv), _mm_set_sd(mz)));


    po[0] = outx;
    po[1] = outy;
    po[2] = outz;
}
