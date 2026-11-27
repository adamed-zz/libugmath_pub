







#include <cstdlib>

#include <intrin.h>
extern "C" void _invalid_parameter_noinfo_noreturn(void);

extern "C" void sub_180033650(void* vec)
{
    unsigned __int64* v = (unsigned __int64*)vec;
    char* p = (char*)v[0];
    if (!p)
        return;
    unsigned __int64 bytes = (unsigned __int64)((char*)v[2] - p) & ~15ull;
    if (bytes >= 0x1000) {
        char* base = *(char**)(p - 8);
        unsigned __int64 d = (unsigned __int64)(p - base) - 8;
        if (d > 0x1F)
            _invalid_parameter_noinfo_noreturn();
        p = base;
    }
    free(p);
    v[0] = 0;
    v[1] = 0;
    v[2] = 0;
}
