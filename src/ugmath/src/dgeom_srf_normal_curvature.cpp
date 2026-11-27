





#include <cmath>
#include <emmintrin.h>

int DGEOM_srf_normal_curvature(double *a1, double *a2, double *a3, double *a4,
                               double *a5, double *a6, double *a7, double *a8)
{
    __m128d p0 = _mm_load_sd(&a1[0]);
    __m128d p1 = _mm_load_sd(&a1[1]);
    __m128d p2 = _mm_load_sd(&a1[2]);
    __m128d q0 = _mm_load_sd(&a2[0]);
    __m128d q1 = _mm_load_sd(&a2[1]);
    __m128d q2 = _mm_load_sd(&a2[2]);

    __m128d E = _mm_add_sd(_mm_add_sd(_mm_mul_sd(p0, p0), _mm_mul_sd(p1, p1)),
                           _mm_mul_sd(p2, p2));
    __m128d F = _mm_add_sd(_mm_add_sd(_mm_mul_sd(q0, p0), _mm_mul_sd(q1, p1)),
                           _mm_mul_sd(q2, p2));
    __m128d G = _mm_add_sd(_mm_add_sd(_mm_mul_sd(q0, q0), _mm_mul_sd(q1, q1)),
                           _mm_mul_sd(q2, q2));
    __m128d den = _mm_sub_sd(_mm_mul_sd(G, E), _mm_mul_sd(F, F));
    if (_mm_cvtsd_f64(den) < 1.0e-10)
    {
        *a8 = 0.0;
        return 0;
    }

    __m128d cx = _mm_sub_sd(_mm_mul_sd(_mm_load_sd(&a7[1]), _mm_load_sd(&a6[2])),
                            _mm_mul_sd(_mm_load_sd(&a7[2]), _mm_load_sd(&a6[1])));
    __m128d cy = _mm_sub_sd(_mm_mul_sd(_mm_load_sd(&a6[0]), _mm_load_sd(&a7[2])),
                            _mm_mul_sd(_mm_load_sd(&a7[0]), _mm_load_sd(&a6[2])));
    __m128d cz = _mm_sub_sd(_mm_mul_sd(_mm_load_sd(&a7[0]), _mm_load_sd(&a6[1])),
                            _mm_mul_sd(_mm_load_sd(&a6[0]), _mm_load_sd(&a7[1])));

    __m128d len2 = _mm_add_sd(_mm_add_sd(_mm_mul_sd(cy, cy), _mm_mul_sd(cx, cx)),
                              _mm_mul_sd(cz, cz));
    double len = std::sqrt(_mm_cvtsd_f64(len2));
    if (len == 0.0)
    {
        *a8 = 0.0;
        return 0;
    }

    __m128d dp = _mm_add_sd(_mm_add_sd(_mm_mul_sd(_mm_load_sd(&a7[0]), p0),
                                       _mm_mul_sd(_mm_load_sd(&a7[1]), p1)),
                            _mm_mul_sd(_mm_load_sd(&a7[2]), p2));
    __m128d dq = _mm_add_sd(_mm_add_sd(_mm_mul_sd(_mm_load_sd(&a7[0]), q0),
                                       _mm_mul_sd(_mm_load_sd(&a7[1]), q1)),
                            _mm_mul_sd(_mm_load_sd(&a7[2]), q2));
    __m128d U = _mm_add_sd(_mm_add_sd(_mm_mul_sd(_mm_load_sd(&a6[1]), _mm_load_sd(&a3[1])),
                                      _mm_mul_sd(_mm_load_sd(&a6[0]), _mm_load_sd(&a3[0]))),
                           _mm_mul_sd(_mm_load_sd(&a6[2]), _mm_load_sd(&a3[2])));
    __m128d V = _mm_add_sd(_mm_add_sd(_mm_mul_sd(_mm_load_sd(&a6[1]), _mm_load_sd(&a4[1])),
                                      _mm_mul_sd(_mm_load_sd(&a6[0]), _mm_load_sd(&a4[0]))),
                           _mm_mul_sd(_mm_load_sd(&a6[2]), _mm_load_sd(&a4[2])));
    __m128d W = _mm_add_sd(_mm_add_sd(_mm_mul_sd(_mm_load_sd(&a6[1]), _mm_load_sd(&a5[1])),
                                      _mm_mul_sd(_mm_load_sd(&a6[0]), _mm_load_sd(&a5[0]))),
                           _mm_mul_sd(_mm_load_sd(&a6[2]), _mm_load_sd(&a5[2])));

    __m128d A = _mm_div_sd(_mm_sub_sd(_mm_mul_sd(dq, E), _mm_mul_sd(dp, F)), den);
    __m128d B = _mm_div_sd(_mm_sub_sd(_mm_mul_sd(dp, G), _mm_mul_sd(dq, F)), den);

    __m128d B2 = _mm_add_sd(B, B);
    __m128d BB = _mm_mul_sd(B, B);
    __m128d AB2 = _mm_mul_sd(B2, A);
    __m128d AA = _mm_mul_sd(A, A);

    __m128d den2 = _mm_add_sd(_mm_add_sd(_mm_mul_sd(BB, E), _mm_mul_sd(F, AB2)),
                              _mm_mul_sd(AA, G));
    if (_mm_cvtsd_f64(den2) == 0.0)
        *a8 = 0.0;
    else
        _mm_store_sd(a8, _mm_div_sd(_mm_add_sd(_mm_add_sd(_mm_mul_sd(BB, U),
                                                          _mm_mul_sd(V, AB2)),
                                               _mm_mul_sd(AA, W)),
                                    den2));
    return 0;
}
