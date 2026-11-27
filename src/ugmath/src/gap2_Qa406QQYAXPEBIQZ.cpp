#include "kits/b18_kit/b18_support.h"





void a406(const unsigned int *a1)
{
    __int64 v1 = g_acom.count;
    __int64 v3 = 0;
    __int64 v4 = -1;
    int *v5;
    int v6;
LABEL_2:
    v5 = (int *)((char *)g_acom.arr + 4 * v3);
    ++v4;
    while (v3 != v1)
    {
        v6 = *v5;
        ++v3;
        ++v5;
        ((int *)g_acom.arr)[v4] = v6;
        if (v6 != (int)*a1)
            goto LABEL_2;
        --g_acom.count;
    }
}
