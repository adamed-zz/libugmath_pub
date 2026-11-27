






#include <emmintrin.h>
#include <cstdint>
#include <cstring>

extern "C" void* g_b15_raw_base;

static float negf(float v)
{
    uint32_t u;
    memcpy(&u, &v, 4);
    u ^= 0x80000000u;
    float f;
    memcpy(&f, &u, 4);
    return f;
}


static int c7e0(double p0x, double p0y, double p1x, double p1y,
                double p2x, double p2y, double p3x, double p3y)
{
    __m128d a = _mm_sub_sd(_mm_load_sd(&p3x), _mm_load_sd(&p2x));
    __m128d b = _mm_mul_sd(_mm_load_sd(&p2x), _mm_load_sd(&p3y));
    __m128d c = _mm_sub_sd(_mm_load_sd(&p2y), _mm_load_sd(&p3y));
    __m128d d = _mm_mul_sd(_mm_load_sd(&p2y), _mm_load_sd(&p3x));
    __m128d e = _mm_mul_sd(c, _mm_load_sd(&p0x));
    __m128d f = _mm_mul_sd(c, _mm_load_sd(&p1x));
    __m128d g = _mm_mul_sd(a, _mm_load_sd(&p0y));
    __m128d h = _mm_mul_sd(a, _mm_load_sd(&p1y));
    b = _mm_sub_sd(b, d);
    e = _mm_add_sd(e, g);
    f = _mm_add_sd(f, h);
    e = _mm_add_sd(e, b);
    f = _mm_add_sd(f, b);
    __m128d r = _mm_mul_sd(e, f);
    return _mm_comigt_sd(r, _mm_setzero_pd()) != 0;
}

extern "C" long long sub_18004AE50(int a1, float** a2, float* a3, float* a4,
                                    float* a5)
{
    const int useNorm = *(int*)((char*)g_b15_raw_base + 0xE07A4);

    double ax = a3[0], ay = a3[1];
    double bx = a4[0], by = a4[1];
    double cx = a5[0], cy = a5[1];
    if (useNorm)
    {
        double z3 = negf(a3[2]);
        ax /= z3;
        ay /= z3;
        double z4 = negf(a4[2]);
        bx /= z4;
        by /= z4;
        double z5 = negf(a5[2]);
        cx /= z5;
        cy /= z5;
    }

    if (a1 <= 0)
        return 0;

    int* cell = *(int**)((char*)g_b15_raw_base + 0xE0798);
    float** pp = a2;
    for (int i = 0; i < a1; ++i, ++cell, ++pp)
    {
        if (*cell)
            continue;
        float* p = *pp;
        if (p == a3 || p == a4 || p == a5)
            continue;
        double px = p[0], py = p[1];
        if (useNorm)
        {
            double z = negf(p[2]);
            px /= z;
            py /= z;
        }
        if (c7e0(ax, ay, px, py, bx, by, cx, cy) &&
            c7e0(bx, by, px, py, cx, cy, ax, ay) &&
            c7e0(cx, cy, px, py, ax, ay, bx, by))
            return 1;
    }
    return 0;
}
