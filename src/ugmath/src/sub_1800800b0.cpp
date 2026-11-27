






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

extern "C" long long sub_1800800B0(long long* a1, long long** a2, long long* a3, long long* a4)
{
    long long* v6 = *a2;
    long long v16 = *a4;
    const long long v7 = v6[2];
    const long long v8 = a3[2];
    long long v9 = v6[1];
    if (v7 < v9)
        v9 = v7;

    Desc d;
    d.scratch0 = 0;
    d.scratch1 = 0;
    d.nfirst = v7;
    d.nsecond = v8;
    d.plan = v9;
    d.planA = 0;
    d.planB = 0;

    long long v15 = v8;
    sub_18007B930(&d.plan, &d.nfirst, &v15, 1);
    d.planA = d.nfirst * d.plan;
    d.planB = d.nsecond * d.plan;

    sub_1800906D0(v7, v8, v9, v6[0], v6[2], a3[0], a3[1],
                  a1[0], 1, a1[1], (long long)&v16, (long long)&d);
    std::free((void*)d.scratch0);
    std::free((void*)d.scratch1);
    return 0;
}
