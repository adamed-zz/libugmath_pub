









#include <cstdint>

typedef long long (*Kern923B0)(long long, long long, long long, long long, long long,
                               long long, long long, long long, long long, long long,
                               long long, long long);

extern "C" long long sub_1800923B0(long long, long long, long long, long long, long long,
                                   long long, long long, long long, long long, long long,
                                   long long, long long);



struct Desc
{
    void* buf0;
    void* buf1;
    long long n2;
    long long n3;
    long long n4;
};

extern "C" long long sub_18007FD50(long long* a1, long long* a2, long long* a3, long long* a4)
{
    const long long v12 = a2[1];
    long long v7 = a2[2];
    const long long v8 = a2[0];
    const long long v10 = a3[2];
    const long long v11 = a3[0];
    long long v14 = a1[6];
    if (v12 < v7)
        v7 = v12;

    static char scratch[0x200];
    Desc desc;
    desc.buf0 = scratch + 0x10;
    desc.buf1 = scratch + 0x40;
    desc.n2 = 2;
    desc.n3 = 3;
    desc.n4 = 3;

    long long out = *a4;
    return sub_1800923B0(v7, v10, v12, v8, 3, v11, 3, (long long)a1, 1, v14,
                         (long long)&out, (long long)&desc);
}
