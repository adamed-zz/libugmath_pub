







#include <cstdint>
#include <cstring>
#include <emmintrin.h>




extern "C" {
int g_ugm_hlr_E06BC = 0;
int g_ugm_hlr_E0768 = 0;
int g_ugm_hlr_E076C = 0;
int g_ugm_hlr_E0770 = 0;
int g_ugm_hlr_E0774 = 0;
unsigned long long g_ugm_hlr_E0858 = 0;
int g_ugm_hlr_E0908 = 0;
unsigned long long g_ugm_hlr_span[15] = {0};
unsigned long long g_ugm_hlr_sentinel[8] = {0};
}


extern "C" {
extern unsigned long long g_ugm_hlr_E0778;
extern unsigned long long g_ugm_hlr_E0780;
extern int g_ugm_hlr_vloc_norm;
extern double g_ugm_hlr_E07C8;
extern unsigned long long g_ugm_hlr_E0848;
extern unsigned long long g_ugm_hlr_geom_desc;
extern float g_ugm_hlr_min_x, g_ugm_hlr_min_y;
extern double g_ugm_hlr_E0880;
}

extern "C" long long sub_18004B2C0(double, double, double, double, double, double,
                                   void*, long long);
extern "C" void b15_free_rec(void*);

static inline int b15_cvtt(double d) { return _mm_cvttsd_si32(_mm_set_sd(d)); }
static inline double b15_absd(double x)
{
    uint64_t u;
    memcpy(&u, &x, 8);
    u &= 0x7FFFFFFFFFFFFFFFull;
    memcpy(&x, &u, 8);
    return x;
}
static __forceinline char* b15_G(unsigned rva)
{
    switch (rva)
    {
    case 0xE0768: return (char*)&g_ugm_hlr_E0768;
    case 0xE0770: return (char*)&g_ugm_hlr_E0770;
    case 0xE0774: return (char*)&g_ugm_hlr_E0774;
    case 0xE0778: return (char*)&g_ugm_hlr_E0778;
    case 0xE0780: return (char*)&g_ugm_hlr_E0780;
    case 0xE07A4: return (char*)&g_ugm_hlr_vloc_norm;
    case 0xE07C8: return (char*)&g_ugm_hlr_E07C8;
    case 0xE0848: return (char*)&g_ugm_hlr_E0848;
    case 0xE0860: return (char*)&g_ugm_hlr_geom_desc;
    case 0xE0870: return (char*)&g_ugm_hlr_min_x;
    case 0xE0874: return (char*)&g_ugm_hlr_min_y;
    case 0xE0880: return (char*)&g_ugm_hlr_E0880;
    case 0xE08E0: return (char*)&g_ugm_hlr_sentinel[0];
    case 0xE0908: return (char*)&g_ugm_hlr_E0908;
    }
    if (rva >= 0xE07D0 && rva <= 0xE0840)
        return (char*)&g_ugm_hlr_span[(rva - 0xE07D0) / 8];
    return nullptr;
}
static inline double b15_Gd(char* b, unsigned rva) { (void)b; double v; memcpy(&v, b15_G(rva), 8); return v; }
static inline int b15_Gi(char* b, unsigned rva) { (void)b; int v; memcpy(&v, b15_G(rva), 4); return v; }
static inline void b15_Sd(char* b, unsigned rva, double v) { (void)b; memcpy(b15_G(rva), &v, 8); }
static inline void b15_Si(char* b, unsigned rva, int v) { (void)b; memcpy(b15_G(rva), &v, 4); }

enum
{
    B15_OBJ_ARRAY = 0x00,
    B15_OBJ_NEXT = 0x10,
    B15_OBJ_A8 = 0x20,
    B15_OBJ_COUNT = 0x28,
    B15_VERT_CHAIN = 0x10,
    B15_INNER_NEXT = 0x18,
    B15_NODE_LINK = 0x28,
    B15_REC_NODE = 0x30,
    B15_REC_PREV = 0x38
};

extern "C" long long sub_18004C2D0(void)
{
    char* b = nullptr;
    void* const sentinel = (void*)g_ugm_hlr_sentinel;

    void* obj = *(void**)&g_ugm_hlr_geom_desc;
    *(void**)&g_ugm_hlr_span[14] = nullptr;
    if (!obj)
    {


        return 0;
    }

    long long rax = 0;
    for (;;)
    {
        unsigned char* arr = *(unsigned char**)obj;
        int count = *(int*)((char*)obj + B15_OBJ_COUNT);
        rax = (long long)(uintptr_t)arr;
        if (count <= 0)
            goto next_object;

        {
            unsigned char* vrec = arr;
            for (; count > 0; --count)
            {
                void* chain = *(void**)(vrec + B15_VERT_CHAIN);
                rax = (long long)(uintptr_t)(vrec + 0x20);
                if (chain)
                {
                    const int persp = b15_Gi(b, 0xE07A4);
                    const double ox = (double)*(const float*)(vrec + 0);
                    const double oy = (double)*(const float*)(vrec + 4);
                    const double oz = (double)*(const float*)(vrec + 8);
                    double px = ox, py = oy;
                    if (persp)
                    {
                        const double nz = -oz;
                        px = ox / nz;
                        py = oy / nz;
                    }

                    for (;;)
                    {
                        unsigned char* node = (unsigned char*)chain;
                        const float* f = *(const float**)node;
                        const double ix = (double)f[0];
                        const double iy = (double)f[1];
                        const double iz = (double)f[2];
                        double qx = ix, qy = iy;
                        if (persp)
                        {
                            const double nz = -iz;
                            qx = ix / nz;
                            qy = iy / nz;
                        }



                        const double eps = b15_Gd(b, 0xE0880);
                        bool swap;
                        if (qx > px)
                            swap = true;
                        else if (!(eps < b15_absd(px - qx)))
                            swap = (qy > py);
                        else
                            swap = false;

                        double x0, y0, x1, y1;
                        if (!swap) { x0 = qx; y0 = qy; x1 = px; y1 = py; }
                        else       { x0 = px; y0 = py; x1 = qx; y1 = qy; }

                        const double delta = b15_Gd(b, 0xE07C8);
                        const double xo = (double)g_ugm_hlr_min_x;
                        const double yo = (double)g_ugm_hlr_min_y;
                        const double dx = x1 - x0;
                        b15_Sd(b, 0xE07D0, dx);
                        const int i0 = b15_cvtt((x0 - xo) / delta);
                        const int i1 = b15_cvtt((x1 - xo) / delta);
                        double slope;
                        if (i0 != i1)
                        {
                            slope = (y1 - y0) / dx;
                            b15_Sd(b, 0xE07D8, slope);
                        }
                        else
                        {
                            slope = b15_Gd(b, 0xE07D8);
                        }
                        int prev = b15_cvtt((y0 - yo) / delta);
                        int prev2 = prev;


                        if (i0 <= i1)
                        {
                            int* upper = (int*)g_ugm_hlr_E0780;
                            int* lower = (int*)g_ugm_hlr_E0778;
                            int k = i0 + 1;
                            for (int i = i0; i <= i1; ++i, ++k)
                            {
                                double yy;
                                if (i == i1)
                                    yy = y1;
                                else
                                    yy = ((double)k * delta + xo - x0) * slope + y0;
                                const int yj = b15_cvtt((yy - yo) / delta);
                                lower[i] = (prev < yj) ? prev : yj;
                                prev = yj;
                                upper[i] = (prev2 > yj) ? prev2 : yj;
                                prev2 = yj;
                            }
                        }


                        const int ny = b15_Gi(b, 0xE0768);
                        void** grid = (void**)g_ugm_hlr_E0848;
                        int* lower = (int*)g_ugm_hlr_E0778;
                        int* upper = (int*)g_ugm_hlr_E0780;
                        unsigned char fake[0x30];
                        memset(fake, 0, sizeof(fake));
                        *(void**)(fake + B15_NODE_LINK) = sentinel;
                        void* tail = fake;
                        b15_Si(b, 0xE0908, 0);
                        if (i0 <= i1)
                        {
                            int cellBase = ny * i0;
                            for (int i = i0; i <= i1; ++i, cellBase += ny)
                            {
                                const int lo = lower[i];
                                const int hi = upper[i];
                                if (lo > hi)
                                    continue;
                                int cell = cellBase + lo;
                                for (int y = lo; y <= hi; ++y, ++cell)
                                {
                                    void** bucket = (void**)grid[cell];
                                    while (bucket)
                                    {
                                        void* payload = bucket[0];
                                        if (*(void**)((char*)payload + B15_NODE_LINK) == nullptr)
                                        {
                                            *(void**)((char*)tail + B15_NODE_LINK) = payload;
                                            tail = payload;
                                            *(void**)((char*)payload + B15_NODE_LINK) = sentinel;
                                        }
                                        bucket = (void**)bucket[1];
                                    }
                                }
                            }
                        }
                        void* chainHead = *(void**)(fake + B15_NODE_LINK);
                        const long long a8 = *(long long*)((char*)obj + B15_OBJ_A8);

                        sub_18004B2C0(ox, oy, oz, ix, iy, iz, chainHead, a8);


                        for (void* rp = *(void**)&g_ugm_hlr_span[14]; rp;
                             rp = *(void**)&g_ugm_hlr_span[14])
                        {
                            const double r0 = ((const double*)rp)[0];
                            const double r1 = ((const double*)rp)[1];
                            const double r2 = ((const double*)rp)[2];
                            const double r3 = ((const double*)rp)[3];
                            const double r4 = ((const double*)rp)[4];
                            const double r5 = ((const double*)rp)[5];
                            void* nxt = *(void**)((char*)rp + B15_REC_NODE);
                            void* prv = *(void**)((char*)rp + B15_REC_PREV);
                            *(void**)&g_ugm_hlr_span[14] = prv;
                            b15_free_rec(rp);
                            sub_18004B2C0(r0, r1, r2, r3, r4, r5, nxt, a8);
                        }


                        if (chainHead != sentinel)
                        {
                            void* p = chainHead;
                            do
                            {
                                void** slot = (void**)((char*)p + B15_NODE_LINK);
                                p = *slot;
                                *slot = nullptr;
                            } while (p != sentinel);
                        }

                        chain = *(void**)((char*)node + B15_INNER_NEXT);
                        if (!chain)
                            break;
                    }
                }
                vrec += 0x20;
            }
        }

    next_object:
        obj = *(void**)((char*)obj + B15_OBJ_NEXT);
        if (!obj)
            break;
    }
    return rax;
}
