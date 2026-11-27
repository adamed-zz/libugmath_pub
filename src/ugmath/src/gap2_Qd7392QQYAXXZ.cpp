#include "kits/b18_kit/b18_support.h"


void d7392()
{
    if (g_acom.count > 0 && g_cb)
        g_cb();
    g_acom.count = 0;
}
