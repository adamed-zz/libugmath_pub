




#include <windows.h>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <malloc.h>
#include <intrin.h>
#include <emmintrin.h>
extern "C" void sub_18008CB70(int* a1, int* a2, int* a3, int a4);
extern "C" void sub_18008CC80(int* a1, int* a2, int* a3);

extern "C" long long* sub_180082450(long long* a1)
{
    int r[4];
    a1[0] = -1;
    a1[1] = -1;
    a1[2] = -1;
    __cpuid(r, 0);
    unsigned int maxb = (unsigned int)r[0];
    int l1 = 0, l2 = 0, l3 = 0;
    if (r[1] == 0x756e6547 && r[3] == 0x49656e69 && r[2] == 0x6c65746e)
    {
        if ((int)maxb >= 4)
        {
            unsigned int sub = 0;
            for (;;)
            {
                __cpuidex(r, 4, (int)sub);
                unsigned int type = (unsigned int)r[0] & 0xFu;
                if (((type - 1u) & 0xFFFFFFFDu) == 0)
                {
                    unsigned int c = (unsigned int)r[2] + 1u;
                    c *= ((unsigned int)r[1] & 0xFFFu) + 1u;
                    c *= (((unsigned int)r[1] >> 10) & 0x3FFu) + 1u;
                    c *= (((unsigned int)r[1] >> 12) & 0x3FFu) + 1u;
                    unsigned int lvl = ((unsigned int)r[0] >> 5) & 7u;
                    if (lvl == 1)
                        l1 = (int)c;
                    else if (lvl == 2)
                        l2 = (int)c;
                    else if (lvl == 3)
                        l3 = (int)c;
                }
                ++sub;
                if (type == 0 || sub >= 16)
                    break;
            }
        }
        else if ((int)maxb >= 2)
        {
            sub_18008CC80(&l1, &l2, &l3);
        }
    }
    else if ((r[1] == 0x68747541 && r[3] == 0x69746e65 && r[2] == 0x444d4163) ||
             (r[1] == 0x69444d41 && r[3] == 0x74656273 && r[2] == 0x21726574))
    {
        __cpuid(r, 0x80000000);
        if ((unsigned int)r[0] >= 0x80000006u)
        {
            __cpuid(r, 0x80000005);
            l1 = (int)(((unsigned int)r[2] >> 24) << 10);
            __cpuid(r, 0x80000006);
            l2 = (int)(((unsigned int)r[2] >> 16) << 10);
            l3 = (int)((((unsigned int)r[3] >> 18) & 0x3FFu) << 19);
        }
    }
    else
    {
        sub_18008CB70(&l1, &l2, &l3, (int)maxb);
    }
    a1[0] = l1 > 0 ? l1 : 0x8000;
    a1[1] = l2 > 0 ? l2 : 0x40000;
    a1[2] = l3 > 0 ? l3 : 0x200000;
    return a1;
}
