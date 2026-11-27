









#include <emmintrin.h>

extern "C" {
extern double g_ugm_hlr_E07C8;
extern float g_ugm_hlr_max_x;
extern float g_ugm_hlr_min_x;
extern float g_ugm_hlr_max_y;
extern float g_ugm_hlr_min_y;
extern int g_ugm_hlr_vloc_norm;
extern int g_ugm_hlr_E0560;
extern double g_ugm_hlr_E06B0;
extern int g_ugm_hlr_E06BC;
extern int g_ugm_hlr_E0768;
extern int g_ugm_hlr_E076C;
extern int (*g_ugm_hlr_diag_cb)(int, int, const char*);
}
extern int g_ugm_hlr_debug_level;
__declspec(dllimport) int STR_snprintf(char* buf, size_t n, const char* fmt, ...);

static __forceinline void* G(unsigned rva)
{
    switch (rva)
    {
    case 0xE07C8: return (void*)&g_ugm_hlr_E07C8;
    case 0xE0870: return (void*)&g_ugm_hlr_min_x;
    case 0xE0874: return (void*)&g_ugm_hlr_min_y;
    case 0xE0878: return (void*)&g_ugm_hlr_max_x;
    case 0xE087C: return (void*)&g_ugm_hlr_max_y;
    case 0xE07A4: return (void*)&g_ugm_hlr_vloc_norm;
    case 0xE0560: return (void*)&g_ugm_hlr_E0560;
    case 0xE06B0: return (void*)&g_ugm_hlr_E06B0;
    case 0xE06BC: return (void*)&g_ugm_hlr_E06BC;
    case 0xE0768: return (void*)&g_ugm_hlr_E0768;
    case 0xE076C: return (void*)&g_ugm_hlr_E076C;
    case 0xE08AC: return (void*)&g_ugm_hlr_debug_level;
    }
    return nullptr;
}

static int cvtt(double v)
{
    return _mm_cvttsd_si32(_mm_load_sd(&v));
}

extern "C" long long sub_18004A4B0(float* a1, float* a2)
{
    const double kOne = 1.0;
    __m128d grid = _mm_load_sd((double*)G(0xE07C8));


    __m128 dxs = _mm_sub_ss(_mm_load_ss((float*)G(0xE0878)),
                            _mm_load_ss((float*)G(0xE0870)));
    __m128d t1 = _mm_div_sd(_mm_cvtps_pd(dxs), grid);
    t1 = _mm_add_sd(t1, _mm_load_sd(&kOne));
    int nx = _mm_cvttsd_si32(t1);

    __m128 dys = _mm_sub_ss(_mm_load_ss((float*)G(0xE087C)),
                            _mm_load_ss((float*)G(0xE0874)));
    __m128d t2 = _mm_div_sd(_mm_cvtps_pd(dys), grid);
    t2 = _mm_add_sd(t2, _mm_load_sd(&kOne));
    int ny = _mm_cvttsd_si32(t2);

    *(int*)G(0xE06BC) = nx;
    *(int*)G(0xE0768) = ny;
    int v4 = ny * nx;
    *(int*)G(0xE076C) = v4;

    float v5;
    if (*(int*)G(0xE07A4))
        v5 = _mm_cvtss_f32(_mm_cvtpd_ps(_mm_load_sd((double*)G(0xE06B0))));
    else
        v5 = 1.0f;

    float df = _mm_cvtss_f32(_mm_cvtpd_ps(grid));
    __m128 s = _mm_mul_ss(_mm_set_ss(v5), _mm_set_ss(df));
    s = _mm_mul_ss(s, s);

    const int facets = *(int*)G(0xE0560);
    __m128 vf = _mm_cvtepi32_ps(_mm_cvtsi32_si128(facets));
    __m128 sf = _mm_cvtepi32_ps(_mm_cvtsi32_si128(v4));
    float v9 = _mm_cvtss_f32(_mm_div_ss(vf, sf));

    *a1 = _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(v9), s));
    float sfs = _mm_cvtss_f32(sf);
    *a2 = _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(sfs), _mm_set_ss(sfs)));

    if (g_ugm_hlr_debug_level > 0)
    {
        char buf[0x64];

        STR_snprintf(buf, 0x64ull, "%d facets; %d cover squares; %f facets/square",
                     facets, v4, (double)v9);
        return (long long)g_ugm_hlr_diag_cb(0, 0, buf);
    }
    return (long long)(unsigned)nx;
}
