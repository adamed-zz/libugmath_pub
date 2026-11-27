




#include <windows.h>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <malloc.h>
#include <intrin.h>
#include <emmintrin.h>
extern "C" void sub_180082970(long long a1)
{
    if (*(unsigned char*)(a1 + 0x10))
        free(*(void**)a1);
}
