






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


extern "C" __int64 sub_1800335E0(void* self)
{
    *(const char**)((char*)self + 0x10) = 0;
    *(const char**)((char*)self + 8) = "bad array new length";
    *(const void**)self = (const void*)bad_array_new_length_vftable;
    return (__int64)self;
}
