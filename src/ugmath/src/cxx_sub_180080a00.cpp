


#include <cstdint>
#include <cstdlib>
#include <malloc.h>

struct B30In
{
    long long a;
    long long b;
    long long c;
    long long d;
    long long e;
    long long f;
    void*     p;
    long long g;
};

struct B30Work
{
    void*  buf;
    size_t n;
};

extern "C" __declspec(noreturn) void sub_180093FC0(void*);
extern "C" long long sub_18008E820(long long, long long, long long, long long,
                                   long long, long long, double);

extern "C" long long sub_180080A00(B30In* a1, B30Work* a2, long long* a3, double* a4)
{
    B30In v1 = *a1;
    B30Work v2 = *a2;
    const double s = *a4;
    if (v2.n > 0x1FFFFFFFFFFFFFFFull)
        sub_180093FC0(nullptr);
    void* work;
    if (v2.buf)
        work = v2.buf;
    else if (8ull * v2.n > 0x20000ull)
    {
        work = std::malloc(8ull * v2.n);
        if (!work)
            sub_180093FC0(nullptr);
    }
    else
        work = _alloca(8ull * v2.n + 15);
    long long v18[2] = {v1.a, *(long long*)((char*)v1.p + 8)};
    long long v17[2] = {(long long)work, 1};
    sub_18008E820(v1.c, v1.b, (long long)v18, (long long)v17, *a3, 1, s);
    if (!v2.buf && 8ull * v2.n > 0x20000ull)
        std::free(work);
    return (long long)(8ull * v2.n);
}
