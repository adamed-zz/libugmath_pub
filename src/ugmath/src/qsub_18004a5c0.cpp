




#include <cstring>
#include <emmintrin.h>



extern "C" {
extern int g_ugm_hlr_E004C;
extern int g_ugm_hlr_E0768;
extern int g_ugm_hlr_E0770;
extern int g_ugm_hlr_E0774;
extern unsigned long long g_ugm_hlr_E0778;
extern unsigned long long g_ugm_hlr_E0780;
extern unsigned long long g_ugm_hlr_E0788;
extern unsigned long long g_ugm_hlr_E0790;
extern int g_ugm_hlr_vloc_norm;
extern double g_ugm_hlr_E07C8;
extern unsigned long long g_ugm_hlr_E0848;
extern unsigned long long g_ugm_hlr_E0850;
extern unsigned long long g_ugm_hlr_E0858;
extern float g_ugm_hlr_min_x, g_ugm_hlr_min_y, g_ugm_hlr_max_x, g_ugm_hlr_max_y;
extern double g_ugm_hlr_E0880;
extern int g_ugm_hlr_E08B0;
extern int (*g_ugm_hlr_diag_cb)(int, int, const char*);
extern unsigned long long g_ugm_hlr_span[15];
}
__declspec(dllimport) void* SM_alloc(unsigned __int64 size);

static __forceinline void* G(unsigned rva)
{
    switch (rva)
    {
    case 0xE004C: return (void*)&g_ugm_hlr_E004C;
    case 0xE0768: return (void*)&g_ugm_hlr_E0768;
    case 0xE0770: return (void*)&g_ugm_hlr_E0770;
    case 0xE0774: return (void*)&g_ugm_hlr_E0774;
    case 0xE0778: return (void*)&g_ugm_hlr_E0778;
    case 0xE0780: return (void*)&g_ugm_hlr_E0780;
    case 0xE0788: return (void*)&g_ugm_hlr_E0788;
    case 0xE0790: return (void*)&g_ugm_hlr_E0790;
    case 0xE07A4: return (void*)&g_ugm_hlr_vloc_norm;
    case 0xE07C8: return (void*)&g_ugm_hlr_E07C8;
    case 0xE0848: return (void*)&g_ugm_hlr_E0848;
    case 0xE0850: return (void*)&g_ugm_hlr_E0850;
    case 0xE0858: return (void*)&g_ugm_hlr_E0858;
    case 0xE0870: return (void*)&g_ugm_hlr_min_x;
    case 0xE0874: return (void*)&g_ugm_hlr_min_y;
    case 0xE0878: return (void*)&g_ugm_hlr_max_x;
    case 0xE087C: return (void*)&g_ugm_hlr_max_y;
    case 0xE0880: return (void*)&g_ugm_hlr_E0880;
    case 0xE08B0: return (void*)&g_ugm_hlr_E08B0;
    case 0xE08D8: return (void*)&g_ugm_hlr_diag_cb;
    }
    if (rva >= 0xE07D0 && rva <= 0xE0840)
        return (void*)&g_ugm_hlr_span[(rva - 0xE07D0) / 8];
    return nullptr;
}
static void* Slot(unsigned rva) { return *(void**)G(rva); }


static int cvtt(double d) { return _mm_cvttsd_si32(_mm_set_sd(d)); }

static void st8(unsigned rva, double v) { *(double*)G(rva) = v; }
static void st4(unsigned rva, int v) { *(int*)G(rva) = v; }

static void store_span(unsigned rva, double a, double b)
{
    *(double*)G(rva) = a;
    *(double*)G(rva + 8) = b;
}

extern "C" long long sub_18004A5C0(float** a1)
{
    typedef void* (*Fn_alloc)(unsigned long long);
    typedef void (*Fn_hook)(int, int, const char*);
    Fn_alloc sm_alloc = (Fn_alloc)SM_alloc;
    Fn_hook hook = (Fn_hook)g_ugm_hlr_diag_cb;

    const double kC = -1000000.0;

    double x0 = (double)a1[0][0], y0 = (double)a1[0][1];
    double x1 = (double)a1[1][0], y1 = (double)a1[1][1];
    double x2 = (double)a1[2][0], y2 = (double)a1[2][1];
    if (*(int*)G(0xE07A4))
    {
        __m128 s = _mm_set_ss(-0.0f);
        double nz0 = (double)_mm_cvtss_f32(_mm_xor_ps(_mm_load_ss(&a1[0][2]), s));
        double nz1 = (double)_mm_cvtss_f32(_mm_xor_ps(_mm_load_ss(&a1[1][2]), s));
        double nz2 = (double)_mm_cvtss_f32(_mm_xor_ps(_mm_load_ss(&a1[2][2]), s));
        x0 /= nz0; y0 /= nz0;
        x1 /= nz1; y1 /= nz1;
        x2 /= nz2; y2 /= nz2;
    }

    st8(0xE07F8, x1); st8(0xE0828, y1);
    st8(0xE07F0, x1); st8(0xE0820, y1);
    store_span(0xE07E0, x0, x0);
    store_span(0xE0810, y0, y0);
    store_span(0xE0800, x2, x2);
    store_span(0xE0830, y2, y2);

    double v16 = y2 * x1 - x2 * y1;
    double v17 = x2 * y0 - y2 * x0;
    double v18 = y1 * x0 - x1 * y0;
    double v19 = (v17 + v16) + v18;

    int flags[3];
    flags[0] = ((v18 - (x0 - x1) * kC) * v19) > 0.0;
    flags[1] = ((v17 - (x2 - x0) * kC) * v19) > 0.0;
    flags[2] = ((v16 - (x1 - x2) * kC) * v19) > 0.0;

    const double eps = *(double*)G(0xE0880);

    if (x0 > x1 || (eps >= (x0 - x1 < 0.0 ? -(x0 - x1) : (x0 - x1)) && y0 > y1))
    {
        st8(0xE07E0, x1); st8(0xE07F8, x0);
        st8(0xE0810, y1); st8(0xE0828, y0);
    }
    if (x0 > x2 || (eps >= (x0 - x2 < 0.0 ? -(x0 - x2) : (x0 - x2)) && y0 > y2))
    {
        st8(0xE07E8, x2); st8(0xE0800, x0);
        st8(0xE0818, y2); st8(0xE0830, y0);
    }
    if (x1 > x2 || (eps >= (x1 - x2 < 0.0 ? -(x1 - x2) : (x1 - x2)) && y1 > y2))
    {
        st8(0xE07F0, x2); st8(0xE0808, x1);
        st8(0xE0820, y2); st8(0xE0838, y1);
    }

    const double xo = (double)*(float*)G(0xE0870);
    const double yo = (double)*(float*)G(0xE0874);
    const double delta = *(double*)G(0xE07C8);

    double v0 = (x1 > x0) ? x0 : x1;
    v0 = (v0 < x2) ? v0 : x2;
    int i0 = cvtt((v0 - xo) / delta);
    *(int*)G(0xE0770) = i0;

    double v1;
    if (!(x0 > x1)) v1 = (x1 < x2) ? x2 : x1;
    else            v1 = (x0 < x2) ? x2 : x0;
    int i1 = cvtt((v1 - xo) / delta);
    *(int*)G(0xE0774) = i1;

    int* A778 = (int*)Slot(0xE0778);
    int* A780 = (int*)Slot(0xE0780);
    int* A788 = (int*)Slot(0xE0788);
    int* A790 = (int*)Slot(0xE0790);
    void** grid = (void**)Slot(0xE0848);
    if (i0 <= i1)
    {
        for (int x = i0; x <= i1; ++x)
        {
            A778[x] = 10000;
            A790[x] = 10000;
            A780[x] = -10000;
            A788[x] = -10000;
        }
    }

    double slope = *(double*)G(0xE07D8);
    for (int k = 0; k < 3; ++k)
    {
        double xlo = *(double*)G(0xE07E0 + 8 * k);
        double xhi = *(double*)G(0xE07F8 + 8 * k);
        double ylo = *(double*)G(0xE0810 + 8 * k);
        double yhi = *(double*)G(0xE0828 + 8 * k);
        int ia = cvtt((xlo - xo) / delta);
        int ib = cvtt((xhi - xo) / delta);
        st8(0xE07D0, xhi - xlo);
        if (ia != ib)
        {
            slope = (yhi - ylo) / (xhi - xlo);
            st8(0xE07D8, slope);
        }
        int prev = cvtt((ylo - yo) / delta);
        const int flag = flags[k];
        if (ia <= ib)
        {
            int xn = ia + 1;
            for (int x = ia; x <= ib; ++x, ++xn)
            {
                double yy;
                if (x == ib)
                    yy = yhi;
                else
                    yy = ((double)xn * delta + xo - xlo) * slope + ylo;
                int yj = cvtt((yy - yo) / delta);
                if (flag)
                {

                    if (prev > yj)
                    {
                        int a = A780[x];
                        A780[x] = (prev <= a) ? a : prev;
                        int b = A790[x];
                        A790[x] = (yj < b) ? yj : b;
                    }
                    else
                    {
                        int a = A780[x];
                        A780[x] = (yj > a) ? yj : a;
                        int b = A790[x];
                        if (prev < yj)
                            A790[x] = (prev >= b) ? b : prev;
                        else
                            A790[x] = (yj < b) ? yj : b;
                    }
                }
                else
                {

                    if (prev < yj)
                    {
                        int a = A778[x];
                        A778[x] = (prev >= a) ? a : prev;
                        int b = A788[x];
                        A788[x] = (yj > b) ? yj : b;
                    }
                    else
                    {
                        int a = A778[x];
                        A778[x] = (yj < a) ? yj : a;
                        int b = A788[x];
                        if (prev > yj)
                            A788[x] = (prev <= b) ? b : prev;
                        else
                            A788[x] = (yj > b) ? yj : b;
                    }
                }
                prev = yj;
            }
        }
    }

    if (i0 > *(int*)G(0xE0774))
        return 1;

    int used = *(int*)G(0xE004C);
    int cap = *(int*)G(0xE08B0);
    char* blk = (char*)*(void**)G(0xE0858);
    for (int x = i0; x <= *(int*)G(0xE0774); ++x)
    {
        for (int y = A778[x]; y <= A780[x]; ++y)
        {
            int cell = y + x * *(int*)G(0xE0768);
            if (used >= cap)
            {
                void** desc = (void**)sm_alloc(16);
                if (!desc) hook(2, 3, "");
                desc[1] = *(void**)G(0xE0850);
                *(void**)G(0xE0850) = desc;
                void* b = sm_alloc(0x2AF80);
                if (!b) hook(2, 3, "");
                desc[0] = b;
                used = 0;
                cap = 11000;
                blk = (char*)b;
                *(void**)G(0xE0858) = b;
                *(int*)G(0xE08B0) = cap;
            }
            char* c = blk + 16 * used;
            ++used;
            *(int*)G(0xE004C) = used;
            *(void**)c = (void*)a1;
            *(void**)(c + 8) = grid[cell];
            grid[cell] = c;
        }
    }
    return 1;
}
