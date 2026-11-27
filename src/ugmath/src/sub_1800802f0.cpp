





#include <cstdint>
#include <cstdlib>

typedef long long (*KernFn)(long long, long long, long long, long long, long long, long long,
                            long long, long long, long long, long long, long long, long long);
extern "C" long long sub_1800923B0(long long, long long, long long, long long, long long, long long,
                                   long long, long long, long long, long long, long long, long long);
extern "C" long long sub_1800906D0(long long, long long, long long, long long, long long, long long,
                                   long long, long long, long long, long long, long long, long long);
extern "C" long long sub_180091070(long long, long long, long long, long long, long long, long long,
                                   long long, long long, long long, long long, long long, long long);

extern "C" long long sub_18007B930(long long* a1, long long* a2, long long* a3, long long n);

struct Desc
{
    long long scratch0;
    long long scratch1;
    long long nfirst;
    long long nsecond;
    long long plan;
    long long planA;
    long long planB;
};

extern "C" long long sub_1800802F0(long long* a1, long long* a2, long long* a3, long long* a4)
{
    long long v16 = *a4;
    const long long v7 = a2[2];
    long long v8 = a2[1];
    if (v7 < v8)
        v8 = v7;
    const long long v9 = a3[2];

    Desc d;
    d.scratch0 = 0;
    d.scratch1 = 0;
    d.nfirst = v8;
    d.nsecond = v9;
    d.plan = v7;
    d.planA = 0;
    d.planB = 0;

    long long v15 = v9;
    sub_18007B930(&d.plan, &d.nfirst, &v15, 1);
    d.planA = d.nfirst * d.plan;
    d.planB = d.nsecond * d.plan;

    sub_180091070(v8, v9, v7, a2[0], a2[2], a3[0], a3[1],
                  a1[0], 1, a1[1], (long long)&v16, (long long)&d);
    std::free((void*)d.scratch0);
    std::free((void*)d.scratch1);
    return 0;
}
