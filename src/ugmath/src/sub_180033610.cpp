






#include <cstdlib>

#include <exception>
#include <new>

extern "C" __int64 sub_180033610(void* self, const void* other)
{
    new (self) std::exception(*(const std::exception*)other);
    return (__int64)self;
}
