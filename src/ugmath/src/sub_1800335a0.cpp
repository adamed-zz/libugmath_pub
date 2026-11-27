







#include <cstdlib>

#include <exception>
#include <new>

extern "C" __int64 sub_1800335A0(void* self, const void* other)
{
    new (self) std::bad_array_new_length(*(const std::bad_array_new_length*)other);
    return (__int64)self;
}
