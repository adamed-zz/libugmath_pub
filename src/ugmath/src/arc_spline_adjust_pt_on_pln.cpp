





















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

static double vload(const volatile double* p)
{
    return *p;
}

void ARC_SPLINE_adjust_pt_on_pln(UGS::Math::Vector3* n, UGS::Math::Point3* q, UGS::Math::Point3* p)
{

    const double ny = vload(&n->y);
    const double nx = vload(&n->x);
    const double py = vload(&p->y);
    const double qy = vload(&q->y);
    const double px = vload(&p->x);
    const double qx = vload(&q->x);
    const double pz = vload(&p->z);
    const double qz = vload(&q->z);

    const __m128d dy = _mm_sub_sd(_mm_set_sd(py), _mm_set_sd(qy));
    const __m128d dx = _mm_sub_sd(_mm_set_sd(px), _mm_set_sd(qx));
    const __m128d dz = _mm_sub_sd(_mm_set_sd(pz), _mm_set_sd(qz));

    const __m128d accY = _mm_mul_sd(dy, _mm_set_sd(ny));
    const __m128d accXY = _mm_add_sd(accY, _mm_mul_sd(dx, _mm_set_sd(nx)));
    const double nz = vload(&n->z);
    const __m128d acc = _mm_add_sd(accXY, _mm_mul_sd(dz, _mm_set_sd(nz)));

    const __m128d t = _mm_castps_pd(_mm_xor_ps(_mm_castpd_ps(acc),
                     _mm_castsi128_ps(_mm_set1_epi64x((long long)0x8000000000000000ULL))));


    const __m128d rz = _mm_add_sd(_mm_mul_sd(_mm_set_sd(nz), t), _mm_set_sd(pz));
    const __m128d rx = _mm_add_sd(_mm_mul_sd(_mm_set_sd(nx), t), _mm_set_sd(px));
    const __m128d ry = _mm_add_sd(_mm_mul_sd(_mm_set_sd(ny), t), _mm_set_sd(py));

    *(volatile double*)&p->z = _mm_cvtsd_f64(rz);
    *(volatile double*)&p->x = _mm_cvtsd_f64(rx);
    *(volatile double*)&p->y = _mm_cvtsd_f64(ry);
}
