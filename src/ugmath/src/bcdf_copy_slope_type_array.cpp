







#include <cstddef>

struct BCDF_s;

__declspec(dllimport) void* SM_alloc(size_t size);




int* __cdecl BCDF_copy_slope_type_array(BCDF_s* a)
{
    unsigned long long v1 = *reinterpret_cast<unsigned long long*>(reinterpret_cast<char*>(a) + 0x18);
    if (v1)
        v1 = *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(v1) + 8);
    int count = static_cast<int>(v1);

    int* src = *reinterpret_cast<int**>(reinterpret_cast<char*>(a) + 0x48);

    int* result = static_cast<int*>(SM_alloc(4LL * count));

    for (int i = 0; i < count; ++i)
        result[i] = src[i];
    return result;
}
