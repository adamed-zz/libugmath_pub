


#include <cstddef>

extern "C" __declspec(dllimport) void* SM_alloc(unsigned __int64 size);

void* SM_alloc(__int64 size) {
    return SM_alloc((unsigned __int64)size);
}

extern "C" void ERROR_internal_stub(const char*, int, const char*, ...) {}

extern "C" void (*__imp_ERROR_internal)(const char*, int, const char*, ...) = &ERROR_internal_stub;
