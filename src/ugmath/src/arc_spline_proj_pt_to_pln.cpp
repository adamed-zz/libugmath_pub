




















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

struct Point3
{
    double x;
    double y;
    double z;
};
}
}

void __cdecl ARC_SPLINE_proj_pt_to_pln(const UGS::Math::Vector3* n,
                                       const UGS::Math::Point3* base,
                                       const UGS::Math::Point3* p,
                                       UGS::Math::Point3* out)
{

    const double nx = *(volatile const double*)&n->x;
    const double py = *(volatile const double*)&p->y;
    const double by = *(volatile const double*)&base->y;
    const double px = *(volatile const double*)&p->x;
    const double bx = *(volatile const double*)&base->x;
    const double pz = *(volatile const double*)&p->z;
    const double bz = *(volatile const double*)&base->z;
    const double nz = *(volatile const double*)&n->z;
    const double ny = *(volatile const double*)&n->y;

    const __m128d dy = _mm_sub_sd(_mm_set_sd(py), _mm_set_sd(by));
    const __m128d dx = _mm_sub_sd(_mm_set_sd(px), _mm_set_sd(bx));
    const __m128d dz = _mm_sub_sd(_mm_set_sd(pz), _mm_set_sd(bz));

    __m128d acc = _mm_mul_sd(dy, _mm_set_sd(ny));
    acc = _mm_add_sd(acc, _mm_mul_sd(dx, _mm_set_sd(nx)));
    acc = _mm_add_sd(acc, _mm_mul_sd(dz, _mm_set_sd(nz)));

    const __m128d t = _mm_castps_pd(_mm_xor_ps(_mm_castpd_ps(acc),
                     _mm_castsi128_ps(_mm_set1_epi64x((long long)0x8000000000000000ULL))));

    const __m128d ry = _mm_add_sd(_mm_mul_sd(_mm_set_sd(ny), t), _mm_set_sd(py));
    const __m128d rz = _mm_add_sd(_mm_mul_sd(_mm_set_sd(nz), t), _mm_set_sd(pz));
    const __m128d rx = _mm_add_sd(_mm_mul_sd(_mm_set_sd(nx), t), _mm_set_sd(px));

    *(volatile double*)&out->x = _mm_cvtsd_f64(rx);
    *(volatile double*)&out->y = _mm_cvtsd_f64(ry);
    *(volatile double*)&out->z = _mm_cvtsd_f64(rz);
}
