







#include <cstdlib>

#include <exception>
#include <new>

extern "C" __int64 sub_180033560(void* self, const void* other)
{
    new (self) std::bad_alloc(*(const std::bad_alloc*)other);
    return (__int64)self;
}
