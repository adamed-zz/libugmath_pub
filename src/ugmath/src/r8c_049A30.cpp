


#include <cstring>

extern "C" void* g_b15_raw_base;
extern "C" bool sub_18004C110(double* a1, float* a2, float* a3, float* a4);
extern "C" long long sub_18004AE50(int a1, float** a2, float* a3, float* a4,
                                   float* a5);
extern "C" long long sub_18004C8B0(float* a, float* b, float* c);

static char* G(unsigned rva) { return (char*)g_b15_raw_base + rva; }
static void* Slot(unsigned rva) { return *(void**)G(rva); }


static float orient3(const float* p, const float* c, const float* nx)
{
    float a = c[1] - nx[1];
    float b = p[1] - nx[1];
    float d = p[1] - c[1];
    return (float)((float)(a * p[0]) - (float)(b * c[0])) + (float)(d * nx[0]);
}

extern "C" long long sub_180049A30(double* a1, int a2, float** a3)
{
    typedef void (*Fn_free)(void*);
    typedef void* (*Fn_calloc)(unsigned long long, unsigned long long);
    Fn_free SM_free = (Fn_free)Slot(0xB9440);
    Fn_calloc SM_calloc = (Fn_calloc)Slot(0xB9400);

    long long n = a2;
    if (a2 > *(int*)G(0xE07A0))
    {
        SM_free(*(void**)G(0xE0798));
        void* p = SM_calloc((unsigned long long)(unsigned)a2, 4ull);
        *(void**)G(0xE0798) = p;
        *(int*)G(0xE07A0) = a2;
    }

    if (a2 <= 3)
    {
        float* p0 = a3[0];
        float* p1 = a3[1];
        long long ret = (long long)a1;
        if (p0 != p1)
        {
            float* p2 = a3[2];
            if (p0 != p2 && p1 != p2)
            {
                sub_18004C110(a1, p0, p1, p2);


                ret = sub_18004C8B0(p0, p1, p2);
            }
        }
        return ret;
    }

    long long live = n;
    int v74 = (int)(n - 1);
    int v6 = -1;
    int v8 = 0;
    int v71 = -1;
    int v9 = v74;
    long long v10 = -1;
    long long v59 = 0;
    int v58 = 0;
    int v70 = 0;

    do
    {
        v70 = v9;
        if (!v8)
        {
            long long v12 = 0;
            int v11 = 0;
            v8 = 1;
            for (; v12 < live; ++v12)
            {
                long long prev = (v12 != 0) ? v12 : live;
                long long next = (v11 != v9) ? v12 + 1 : 0;
                float* cur = a3[v12];

                float ov = orient3(a3[prev - 1], cur, a3[next]);
                bool in = !(0.0f > ov);
                *(int*)((char*)*(void**)G(0xE0798) + 4 * v12) = in ? 1 : 0;
                ++v11;
                v8 = in ? v8 : 0;
            }
            v6 = v71;
        }

        const int v69 = v9 + 1;
        int v54 = v69;
        int v55 = v69;
        int v76 = 0;
        long long v57 = live;
        long long v60 = 0;
        for (;;)
        {
            long long v56 = v10 + 1;
            v57 = live;
            v10 = 0;
            if (v56 < live)
                v10 = v56;
            v58 = 0;
            v59 = v10;
            if (v56 < live)
                v58 = v6 + 1;
            if (v10)
                v57 = v10;
            v60 = 0;
            if (v58 != v74)
                v60 = v10 + 1;
            v76 = --v55;
            if (!v55)
                break;
            if (v8)
                break;
            v6 = v58;
            if (*(int*)((char*)*(void**)G(0xE0798) + 4 * v10))
            {
                int v61 = (int)sub_18004AE50(v54, a3, a3[v57 - 1], a3[v10],
                                             a3[v60]);
                v6 = v58;
                v55 = v76;
                v54 = v69;
                if (!v61)
                    break;
            }
        }

        float* v62 = a3[v57 - 1];
        float* v63 = a3[v10];
        if (v62 != v63)
        {
            float* v64 = a3[v60];
            if (v62 != v64 && v63 != v64)
            {
                sub_18004C110(a1, v62, v63, v64);
                sub_18004C8B0(v62, v63, v64);
            }
        }

        --v74;
        long long v72 = live;
        live = v72 - 1;
        if (v59 < live)
            memmove(&a3[v59], &a3[v59 + 1], 8ull * (size_t)(live - v59));
        v6 = v58;
        v9 = v74;
        v10 = v59;
        v71 = v6;
    } while (v70 > 2);

    return (long long)&a3[v59];
}
