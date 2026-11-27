






#include <cstdint>
#include <cstdlib>
#include <malloc.h>

extern "C" long long sub_180093A90(long long, long long, long long, long long, long long,
                                   long long, long long, long long, long long);
extern "C" long long sub_18008E820(long long, long long, long long, long long, long long,
                                   long long, long long);
extern "C" void sub_180093FC0(void*);








struct B30WorkPlan
{
    unsigned long long bytes;
    unsigned long long need;
    int heap;
    int supplied;
};

static inline B30WorkPlan b30_work_plan(long long buf, unsigned long long n)
{
    if (n > 0x1FFFFFFFFFFFFFFFULL)
        sub_180093FC0(nullptr);
    B30WorkPlan p;
    p.bytes = 8ull * n;
    p.heap = 0;
    p.supplied = (buf != 0);
    p.need = 0;
    if (!p.supplied)
    {
        if (p.bytes > 0x20000)
            p.heap = 1;
        else
            p.need = ((p.bytes + 15) + 15) & ~15ull;
    }
    return p;
}



static inline long long b30_work_done(const B30WorkPlan* p, unsigned char* work)
{
    if (p->heap)
    {
        std::free(work);


        return (long long)(p->bytes ? p->bytes : 1);
    }
    return (long long)p->bytes;
}

extern "C" long long sub_180080B80(long long* a1, long long* a2, long long* a3, long long* a4)
{
    const long long supplied = a2[0];
    const unsigned long long n = (unsigned long long)a2[1];

    B30WorkPlan p = b30_work_plan(supplied, n);
    unsigned char* work;
    if (p.supplied)
        work = (unsigned char*)supplied;
    else if (p.heap)
    {
        work = (unsigned char*)std::malloc((size_t)p.bytes);
        if (!work)
            sub_180093FC0(nullptr);
    }
    else
        work = (unsigned char*)_alloca((size_t)p.need);
    long long v18[2] = {a1[0], *(long long*)(a1[6] + 8)};
    long long v17[2] = {(long long)work, 1};
    sub_18008E820(a1[2], a1[1], (long long)v18, (long long)v17, a3[0], 1, a4[0]);
    return b30_work_done(&p, work);
}
