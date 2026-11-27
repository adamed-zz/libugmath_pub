




#include <windows.h>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <malloc.h>
#include <intrin.h>
#include <emmintrin.h>
extern "C" const void* g_raw_vftable_bad_alloc;
extern "C" const void* g_raw_bad_alloc_str;

extern "C" long long* sub_1800828E0(long long* a1)
{
    a1[2] = 0;
    a1[1] = (long long)g_raw_bad_alloc_str;
    a1[0] = (long long)g_raw_vftable_bad_alloc;
    return a1;
}
