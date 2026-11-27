#include "kits/b18_kit/b18_support.h"



void b120a()
{
    __m128 z = _mm_setzero_ps();
    _mm_storeu_ps((float *)g_b120.q[0], z);
    g_b120.x = 0;
    _mm_storeu_ps((float *)g_b120.q[1], z);
    g_b120.n = 0;
    _mm_storeu_ps((float *)g_b120.q[2], z);
    _mm_storeu_ps((float *)g_b120.q[3], z);
    _mm_storeu_ps((float *)g_b120.q[4], z);
    _mm_storeu_ps((float *)g_b120.q[5], z);
    _mm_storeu_ps((float *)g_b120.q[6], z);
    _mm_storeu_ps((float *)g_b120.q[7], z);
}
