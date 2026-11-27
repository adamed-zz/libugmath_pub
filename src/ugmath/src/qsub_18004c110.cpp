







#include <emmintrin.h>

extern "C" void* g_b15_raw_base;

static double* G(unsigned rva) { return (double*)((char*)g_b15_raw_base + rva); }

extern "C" bool sub_18004C110(double* a1, float* a2, float* a3, float* a4)
{
    const double p0 = a2[0];
    const double p1 = a2[1];
    const double p2 = a2[2];
    const double u0 = (double)(float)(a3[0] - a2[0]);
    const double u1 = (double)(float)(a3[1] - a2[1]);
    const double u2 = (double)(float)(a3[2] - a2[2]);
    const double w0 = (double)(float)(a4[0] - a2[0]);
    const double w1 = (double)(float)(a4[1] - a2[1]);
    const double w2 = (double)(float)(a4[2] - a2[2]);

    __m128d v14 = _mm_sub_sd(_mm_mul_sd(_mm_load_sd(&w1), _mm_load_sd(&u0)),
                             _mm_mul_sd(_mm_load_sd(&w0), _mm_load_sd(&u1)));
    __m128d v15 = _mm_sub_sd(_mm_mul_sd(_mm_load_sd(&w0), _mm_load_sd(&u2)),
                             _mm_mul_sd(_mm_load_sd(&w2), _mm_load_sd(&u0)));
    __m128d v16 = _mm_sub_sd(_mm_mul_sd(_mm_load_sd(&w2), _mm_load_sd(&u1)),
                             _mm_mul_sd(_mm_load_sd(&w1), _mm_load_sd(&u2)));
    __m128d len2 = _mm_add_sd(_mm_mul_sd(v15, v15), _mm_mul_sd(v16, v16));
    len2 = _mm_add_sd(len2, _mm_mul_sd(v14, v14));

    const double kMinLen2 = 1.0e-10;
    const double kMinLen = 0.000001;
    double len;
    __m128d gx, gy, gz;

    if (_mm_comilt_sd(len2, _mm_load_sd(&kMinLen2)))
    {
        len = 1.0;
        gx = _mm_load_sd(a1);
        gy = _mm_load_sd(a1 + 1);
        gz = _mm_load_sd(a1 + 2);
    }
    else
    {
        __m128d l = _mm_sqrt_sd(len2, len2);
        _mm_store_sd(&len, l);
        gx = _mm_div_sd(v16, l);
        gy = _mm_div_sd(v15, l);
        gz = _mm_div_sd(v14, l);
    }

    _mm_store_sd(G(0xE07A8), gx);
    _mm_store_sd(G(0xE07B0), gy);
    _mm_store_sd(G(0xE07B8), gz);


    double p2d = p2;
    __m128d acc = _mm_mul_sd(_mm_load_sd(&p1), gy);
    acc = _mm_add_sd(acc, _mm_mul_sd(_mm_load_sd(&p0), gx));
    acc = _mm_add_sd(acc, _mm_mul_sd(_mm_load_sd(&p2d), gz));
    _mm_store_sd(G(0xE07C0), acc);

    return _mm_comilt_sd(_mm_load_sd(&len), _mm_load_sd(&kMinLen)) == 0;
}
