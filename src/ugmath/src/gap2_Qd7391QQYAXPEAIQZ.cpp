#include "kits/b18_kit/b18_support.h"





void d7391(unsigned int *a1)
{
    int v1 = g_acom.count;
    if (g_acom.count == 512)
    {
        if (g_cb)
            g_cb();
        v1 = 0;
    }
    g_acom.count = v1 + 1;
    g_acom.arr[v1] = *a1;
}
