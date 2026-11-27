









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

extern "C" long long sub_180080410(long long* a1, long long* a2, long long* a3, long long* a4)
{
    const long long v6lo = a2[0];
    const long long v6hi = a2[1];
    long long v17 = *a4;
    long long v7 = a2[2];
    if (v6hi < v7)
        v7 = v6hi;

    Desc d;
    d.scratch0 = 0;
    d.scratch1 = 0;
    d.nfirst = v7;
    d.nsecond = a3[2];
    d.plan = a2[1];
    d.planA = a2[5];
    d.planB = a2[6];

    long long v16 = a3[2];
    sub_18007B930(&d.plan, &d.nfirst, &v16, 1);
    d.planA = d.nfirst * d.plan;
    d.planB = d.nsecond * d.plan;

    sub_1800923B0(v7, a3[2], v6hi, v6lo, 3, a3[0], 3,
                  a1[0], 1, a1[1], (long long)&v17, (long long)&d);
    std::free((void*)d.scratch0);
    std::free((void*)d.scratch1);
    return 0;
}
