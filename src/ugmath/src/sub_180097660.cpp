
















#include <intrin.h>

__declspec(dllimport) void SM_free(void* p);

extern "C" void sub_180097660(void** a1)
{
    SM_free(*a1);
    __nop();
}
