









#include <emmintrin.h>
#include <intrin.h>

namespace UGS { namespace Math { struct Point3; } }

struct ARC_SPLINE_monge_plane_s
{
    __m128d       n;
    double        nz;
    double        d;
    unsigned char flag;
};

void ARC_SPLINE_ask_polar_plane_of_circle(UGS::Math::Point3* c, double r,
                                          ARC_SPLINE_monge_plane_s* pln)
{
    const double* p = reinterpret_cast<const double*>(c);
    double x = p[0];
    double y = p[1];

    pln->flag = 0;

    alignas(16) static const double kTwo[2] = { 2.0, 2.0 };
    __m128d two = _mm_load_pd(kTwo);
    __m128d xy = _mm_set_pd(y, x);

    pln->n  = _mm_mul_pd(two, xy);
    pln->nz = -1.0;
    pln->d  = -(x * x + y * y - r * r);
}
