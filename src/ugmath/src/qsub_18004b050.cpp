









#include <emmintrin.h>
#include <cmath>
#include <cstring>



extern "C" {
extern int g_ugm_hlr_E06BC;
extern int g_ugm_hlr_E0768;
extern int g_ugm_hlr_E076C;
extern unsigned long long g_ugm_hlr_E0778;
extern unsigned long long g_ugm_hlr_E0780;
extern unsigned long long g_ugm_hlr_E0788;
extern unsigned long long g_ugm_hlr_E0790;
extern double g_ugm_hlr_E07C8;
extern unsigned long long g_ugm_hlr_E0848;
extern float g_ugm_hlr_min_x, g_ugm_hlr_min_y, g_ugm_hlr_max_x, g_ugm_hlr_max_y;
extern int (*g_ugm_hlr_diag_cb)(int, int, const char*);
}
extern int g_ugm_hlr_debug_level;
__declspec(dllimport) void* SM_alloc(unsigned __int64 size);
__declspec(dllimport) int STR_snprintf(char* buf, size_t n, const char* fmt, ...);

static __forceinline void* G(unsigned rva)
{
    switch (rva)
    {
    case 0xE06BC: return (void*)&g_ugm_hlr_E06BC;
    case 0xE0768: return (void*)&g_ugm_hlr_E0768;
    case 0xE076C: return (void*)&g_ugm_hlr_E076C;
    case 0xE0778: return (void*)&g_ugm_hlr_E0778;
    case 0xE0780: return (void*)&g_ugm_hlr_E0780;
    case 0xE0788: return (void*)&g_ugm_hlr_E0788;
    case 0xE0790: return (void*)&g_ugm_hlr_E0790;
    case 0xE07C8: return (void*)&g_ugm_hlr_E07C8;
    case 0xE0848: return (void*)&g_ugm_hlr_E0848;
    case 0xE0870: return (void*)&g_ugm_hlr_min_x;
    case 0xE0874: return (void*)&g_ugm_hlr_min_y;
    case 0xE0878: return (void*)&g_ugm_hlr_max_x;
    case 0xE087C: return (void*)&g_ugm_hlr_max_y;
    case 0xE08AC: return (void*)&g_ugm_hlr_debug_level;
    case 0xE08D8: return (void*)&g_ugm_hlr_diag_cb;
    }
    return nullptr;
}
static void* Slot(unsigned rva) { return *(void**)G(rva); }


static void* sm_alloc(long long n)
{
    typedef void* (*Fn_err)(int, int, const char*);
    void* p = SM_alloc((unsigned __int64)n);
    if (!p && n)
    {
        ((Fn_err)g_ugm_hlr_diag_cb)(2, 3, "");
        return nullptr;
    }
    return p;
}

extern "C" void* sub_18004B050()
{

    const double kOne = 1.0;
    const double kTwo = 2.0;
    const double kCap = 1440000.0;

    double delta = *(double*)G(0xE07C8);
    const double dx = (double)(float)(*(float*)G(0xE0878) - *(float*)G(0xE0870));
    const double dy = (double)(float)(*(float*)G(0xE087C) - *(float*)G(0xE0874));
    int retries = 0;
    void* p = nullptr;

    for (;;)
    {
        for (;;)
        {
            __m128d d = _mm_load_sd(&delta);
            __m128d ty = _mm_add_sd(_mm_div_sd(_mm_load_sd(&dy), d),
                                    _mm_load_sd(&kOne));
            __m128d tx = _mm_add_sd(_mm_div_sd(_mm_load_sd(&dx), d),
                                    _mm_load_sd(&kOne));
            int ny = _mm_cvttsd_si32(ty);
            int nx = _mm_cvttsd_si32(tx);
            int v5 = (int)((unsigned)nx * (unsigned)ny);
            *(int*)G(0xE0768) = ny;
            *(int*)G(0xE06BC) = nx;
            *(int*)G(0xE076C) = v5;

            double dv = (double)v5;
            if (_mm_comigt_sd(_mm_load_sd(&dv), _mm_load_sd(&kCap)))
            {
                double q;
                __m128d qv = _mm_div_sd(_mm_load_sd(&dv), _mm_load_sd(&kCap));
                _mm_store_sd(&q, qv);
                double root;
                if (_mm_comigt_sd(_mm_setzero_pd(), _mm_load_sd(&q)))
                    root = ::sqrt(q);
                else
                {
                    __m128d r = _mm_sqrt_sd(_mm_load_sd(&q), _mm_load_sd(&q));
                    _mm_store_sd(&root, r);
                }
                delta = delta * root;
                d = _mm_load_sd(&delta);
                ty = _mm_add_sd(_mm_div_sd(_mm_load_sd(&dy), d),
                                _mm_load_sd(&kOne));
                tx = _mm_add_sd(_mm_div_sd(_mm_load_sd(&dx), d),
                                _mm_load_sd(&kOne));
                *(double*)G(0xE07C8) = delta;
                ny = _mm_cvttsd_si32(ty);
                nx = _mm_cvttsd_si32(tx);
                v5 = (int)((unsigned)nx * (unsigned)ny);
                *(int*)G(0xE0768) = ny;
                *(int*)G(0xE06BC) = nx;
                *(int*)G(0xE076C) = v5;
            }

            p = sm_alloc(8LL * v5);
            *(void**)G(0xE0848) = p;
            if (p)
                break;
            ++retries;
            delta = *(double*)G(0xE07C8) * kTwo;
            *(double*)G(0xE07C8) = delta;
        }

        if (retries <= 0)
            break;
        delta = *(double*)G(0xE07C8) * kTwo;
        *(double*)G(0xE07C8) = delta;
        retries = 0;
    }

    if (*(int*)G(0xE08AC) > 0)
    {
        typedef int (*Fn_hook)(int, int, const char*);
        char buf[0x64];
        STR_snprintf(buf, 0x64ull, "delta=%f, nx=%d, ny=%d",
                     *(double*)G(0xE07C8), *(int*)G(0xE06BC), *(int*)G(0xE0768));
        ((Fn_hook)g_ugm_hlr_diag_cb)(0, 0, buf);
        p = *(void**)G(0xE0848);
    }

    const int cells = *(int*)G(0xE076C);
    if (cells > 0)
        memset(p, 0, 8ull * (unsigned)cells);

    const int nx = *(int*)G(0xE06BC);
    *(void**)G(0xE0778) = sm_alloc(4LL * nx);
    *(void**)G(0xE0780) = sm_alloc(4LL * nx);
    *(void**)G(0xE0788) = sm_alloc(4LL * nx);
    void* last = sm_alloc(4LL * nx);
    *(void**)G(0xE0790) = last;
    return last;
}
