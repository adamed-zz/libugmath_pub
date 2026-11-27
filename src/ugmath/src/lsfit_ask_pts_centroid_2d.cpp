














#include <intrin.h>

namespace UGS
{
namespace Math
{
struct Point2
{
    double x;
    double y;
};
}
}

void __cdecl LSFIT_ask_pts_centroid_2d(int n, UGS::Math::Point2* pts,
                                       UGS::Math::Point2* centroid)
{

    __m128i cnt = _mm_shuffle_epi32(_mm_cvtsi32_si128(n), 0);


    __m128d acc = _mm_setzero_pd();
    if (n > 0)
    {
        double sx = 0.0;
        UGS::Math::Point2* p = pts;
        __int64 k = n;
        do
        {
            sx += p->x;
            acc.m128d_f64[0] += p->y;
            ++p;
        } while (--k);

        acc.m128d_f64[1] = acc.m128d_f64[0];
        acc.m128d_f64[0] = sx;
    }

    _mm_storeu_pd(&centroid->x,
                  _mm_div_pd(acc, _mm_cvtepi32_pd(_mm_move_epi64(cnt))));
}
