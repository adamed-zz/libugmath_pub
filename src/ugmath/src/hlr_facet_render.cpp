








#include <math.h>

typedef unsigned long long u64;


__declspec(dllimport) void SM_free(void* p);
__declspec(dllimport) int STR_snprintf(char* buf, size_t n, const char* fmt, ...);



extern "C" u64 g_ugm_hlr_geom_desc;
extern "C" u64 g_ugm_hlr_geom_list;
extern "C" int g_ugm_hlr_E0584;
extern "C" int g_ugm_hlr_E06B8;
extern "C" int g_ugm_hlr_vloc_norm;
extern "C" double g_ugm_hlr_E06B0;
extern "C" double g_ugm_hlr_E07C8;
extern "C" float g_ugm_hlr_E0050;
extern "C" float g_ugm_hlr_E0054;
extern "C" float g_ugm_hlr_E0058;
extern "C" float g_ugm_hlr_E005C;
extern "C" float g_ugm_hlr_E0060;
extern "C" float g_ugm_hlr_E0064;
extern "C" float g_ugm_hlr_E0068;
extern "C" float g_ugm_hlr_E006C;
extern "C" float g_ugm_hlr_E0070;
extern "C" float g_ugm_hlr_E0074;
extern "C" float g_ugm_hlr_E0078;
extern "C" float g_ugm_hlr_E007C;
extern "C" double g_ugm_hlr_E08A0;
extern "C" int g_ugm_hlr_E08A8;
extern "C" int g_ugm_hlr_E08B0;
extern "C" int g_ugm_hlr_E08B4;
extern "C" int g_ugm_hlr_E08B8;
extern "C" int g_ugm_hlr_E08BC;
extern "C" int g_ugm_hlr_E08C0;
extern "C" int g_ugm_hlr_E08C4;
extern "C" int g_ugm_hlr_E08C8;
extern "C" u64 g_ugm_hlr_E0850;
extern "C" u64 g_ugm_hlr_E0848;
extern "C" u64 g_ugm_hlr_E0778;
extern "C" u64 g_ugm_hlr_E0780;
extern "C" u64 g_ugm_hlr_E0788;
extern "C" u64 g_ugm_hlr_E0790;
extern "C" int g_ugm_hlr_E004C;


extern "C" void (*g_ugm_hlr_diag_cb)(int, int, const char*);


extern "C" long long sub_18004A4B0(float* a1, float* a2);
extern "C" long long sub_18004A5C0(void* a1);
extern "C" long long sub_18004B050(float a1, float a2);
extern "C" long long sub_18004C2D0();

void __cdecl HLR_FACET_render()
{
    char buf[200];
    float v12;
    float v13;

    if (g_ugm_hlr_geom_desc)
    {
        if (*(int*)(g_ugm_hlr_geom_desc + 0x2C) > 0)
        {
            SM_free(*(void**)(g_ugm_hlr_geom_desc + 8));
            *(int*)(g_ugm_hlr_geom_desc + 0x2C) = 0;
        }
        if (g_ugm_hlr_E0584)
        {
            STR_snprintf(buf, 0xC8, "Facets culled (outside current partition):  %d",
                         g_ugm_hlr_E06B8);
            g_ugm_hlr_diag_cb(0, 0, buf);
        }
        double v0 = 1.0;
        if (g_ugm_hlr_vloc_norm)
            v0 = 1.0 / g_ugm_hlr_E06B0;
        g_ugm_hlr_E07C8 = v0;
        sub_18004A4B0(&v12, &v13);
        float v1 = (100000.0f < v12) ? 100000.0f : v12;
        float v2 = 1.0f;
        if (v1 > g_ugm_hlr_E0050 && g_ugm_hlr_E0054 >= v1)
            v2 = (v1 - g_ugm_hlr_E0050) / (g_ugm_hlr_E0054 - g_ugm_hlr_E0050)
                 * (g_ugm_hlr_E006C - g_ugm_hlr_E0068) + g_ugm_hlr_E0068;
        if (v1 > g_ugm_hlr_E0054 && g_ugm_hlr_E0058 >= v1)
            v2 = (v1 - g_ugm_hlr_E0054) / (g_ugm_hlr_E0058 - g_ugm_hlr_E0054)
                 * (g_ugm_hlr_E0070 - g_ugm_hlr_E006C) + g_ugm_hlr_E006C;
        if (v1 > g_ugm_hlr_E0058 && g_ugm_hlr_E005C >= v1)
            v2 = (v1 - g_ugm_hlr_E0058) / (g_ugm_hlr_E005C - g_ugm_hlr_E0058)
                 * (g_ugm_hlr_E0074 - g_ugm_hlr_E0070) + g_ugm_hlr_E0070;
        if (v1 > g_ugm_hlr_E005C && g_ugm_hlr_E0060 >= v1)
            v2 = (v1 - g_ugm_hlr_E005C) / (g_ugm_hlr_E0060 - g_ugm_hlr_E005C)
                 * (g_ugm_hlr_E0078 - g_ugm_hlr_E0074) + g_ugm_hlr_E0074;
        if (v1 > g_ugm_hlr_E0060 && g_ugm_hlr_E0064 >= v1)
            v2 = (v1 - g_ugm_hlr_E0060) / (g_ugm_hlr_E0064 - g_ugm_hlr_E0060)
                 * (g_ugm_hlr_E007C - g_ugm_hlr_E0078) + g_ugm_hlr_E0078;
        double v4;
        if (g_ugm_hlr_E08A0 == 0.0)
        {
            v4 = 1000000000.0;
        }
        else
        {
            double q = g_ugm_hlr_E08A0 / (double)(g_ugm_hlr_E08A8 + 1);
            v4 = sqrt(q) * v2;
        }
        g_ugm_hlr_E07C8 = v4;
        sub_18004B050(v12, v13);
        for (u64 i = g_ugm_hlr_geom_list; i; i = *(u64*)(i + 8))
        {
            int v7 = *(int*)(i + 16);
            for (u64 j = *(u64*)i; v7 > 0; j += 48)
            {
                sub_18004A5C0((void*)j);
                --v7;
            }
        }
        sub_18004A4B0(&v12, &v13);
        g_ugm_hlr_E08C8 = 0;
        g_ugm_hlr_E08C4 = 0;
        g_ugm_hlr_E08C0 = 0;
        g_ugm_hlr_E08BC = 0;
        g_ugm_hlr_E08B8 = 0;
        g_ugm_hlr_E08B4 = 0;
        sub_18004C2D0();
        STR_snprintf(buf, 0xC8, "render test counts:  %d %d %d %d %d %d",
                     g_ugm_hlr_E08B4, g_ugm_hlr_E08B8, g_ugm_hlr_E08BC,
                     g_ugm_hlr_E08C0, g_ugm_hlr_E08C4, g_ugm_hlr_E08C8);
        g_ugm_hlr_diag_cb(0, 0, buf);
        u64 v9 = g_ugm_hlr_E0850;
        if (g_ugm_hlr_E0850)
        {
            u64 v10;
            do
            {
                v10 = *(u64*)(v9 + 8);
                SM_free(*(void**)v9);
                SM_free((void*)v9);
                v9 = v10;
            } while (v10);
        }
        g_ugm_hlr_E0850 = 0;
        g_ugm_hlr_E004C = 1;
        g_ugm_hlr_E08B0 = 0;
        SM_free((void*)g_ugm_hlr_E0848);
        SM_free((void*)g_ugm_hlr_E0778);
        SM_free((void*)g_ugm_hlr_E0780);
        SM_free((void*)g_ugm_hlr_E0788);
        SM_free((void*)g_ugm_hlr_E0790);
    }
}
