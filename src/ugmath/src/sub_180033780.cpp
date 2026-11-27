







#include <cstdlib>

#include <intrin.h>
extern "C" void _invalid_parameter_noinfo_noreturn(void);

extern "C" void sub_180033780(void* self, void* p, unsigned __int64 n)
{
    unsigned __int64 bytes = n << 4;
    if (bytes >= 0x1000) {
        void* base = *(void**)((char*)p - 8);
        unsigned __int64 d = (unsigned __int64)((char*)p - (char*)base) - 8;
        if (d > 0x1F)
            _invalid_parameter_noinfo_noreturn();
        p = base;
    }
    free(p);
}
