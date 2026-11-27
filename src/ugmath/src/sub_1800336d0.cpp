







#include <cstdlib>

#include <emmintrin.h>
struct __std_exception_data { const char* what; bool dofree; };
extern "C" const unsigned char exc_vftable[8];
extern "C" const unsigned char bad_alloc_vftable[8];
extern "C" const unsigned char bad_array_new_length_vftable[8];
extern "C" void __std_exception_copy(const __std_exception_data* src, __std_exception_data* dst);
extern "C" void __std_exception_destroy(__std_exception_data* p);



#pragma comment(linker, "/alternatename:exc_vftable=??_7exception@std@@6B@")
#pragma comment(linker, "/alternatename:bad_alloc_vftable=??_7bad_alloc@std@@6B@")
#pragma comment(linker, "/alternatename:bad_array_new_length_vftable=??_7bad_array_new_length@std@@6B@")

#include <intrin.h>

extern "C" void* sub_1800336D0(void* self, int flags)
{
    *(const void**)self = (const void*)exc_vftable;
    __std_exception_destroy((__std_exception_data*)((char*)self + 8));
    __nop();
    if (flags & 1)
        free(self);
    return self;
}
