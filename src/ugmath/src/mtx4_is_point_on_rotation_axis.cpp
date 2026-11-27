








#include <cmath>
#include <intrin.h>

namespace UGS { namespace Math { struct TransformMatrix; } }


double __cdecl EQ_ask_length_tolerance();



extern "C" double* sub_180063A60(double* dst, const double* src, const void* mtx);

bool __cdecl MTX4_is_point_on_rotation_axis(
    UGS::Math::TransformMatrix* a1,
    double* const a2)
{
    double tol = EQ_ask_length_tolerance();
    double x = a2[0];
    double y = a2[1];
    double z = a2[2];
    double pt[3] = { x, y, z };
    double tp[3];
    const double* q = sub_180063A60(tp, pt, a1);
    __m128d q01 = _mm_loadu_pd(q);
    double dx = x - q01.m128d_f64[0];
    double dy = y - _mm_unpackhi_pd(q01, q01).m128d_f64[0];
    double dz = z - q[2];
    return tol >= sqrt(dx * dx + dy * dy + dz * dz);
}
