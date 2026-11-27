











#include <intrin.h>

extern "C" __declspec(noinline) long long sub_18008CC80(int* a1, int* a2, int* a3);

extern "C" __declspec(noinline) long long sub_18008CB70(int* a1, int* a2, int* a3, int level)
{
    long long result = 0;
    int iter;
    int type;
    int regs[4];
    if (level < 4) {
        if (level < 2) {
            *a3 = 0;
            *a2 = 0;
            *a1 = 0;
            return 0;
        }
        return sub_18008CC80(a1, a2, a3);
    }
    *a3 = 0;
    iter = 0;
    *a2 = 0;
    *a1 = 0;
    do {
        __cpuidex(regs, 4, iter);
        int eax = regs[0];
        type = eax & 0xF;
        result = (unsigned int)eax;
        if (((type - 1) & 0xFFFFFFFD) == 0) {
            unsigned int ebx = (unsigned int)regs[1];
            int size = (int)((unsigned int)(regs[2] + 1) * ((ebx & 0xFFF) + 1) *
                             ((ebx >> 22) + 1) * (((ebx >> 12) & 0x3FF) + 1));
            result = (unsigned int)(regs[2] + 1);
            int lvl = ((eax >> 5) & 7) - 1;
            if (lvl) {
                int l2 = lvl - 1;
                if (l2) {
                    if (l2 == 1)
                        *a3 = size;
                } else {
                    *a2 = size;
                }
            } else {
                *a1 = size;
            }
        }
        ++iter;
    } while (type && iter < 16);
    return result;
}
