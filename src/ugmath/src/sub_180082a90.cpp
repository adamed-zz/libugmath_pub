



#include <cstdint>
#include <intrin.h>
extern "C" void __fastcall sub_180082A90(void** a1) {
    char* obj = (char*)*a1;
    char* vtbl = *(char**)obj;
    void* slot = *(void**)(obj + 0x48 + *(int*)(vtbl + 4));
    if (slot) {
        (*reinterpret_cast<void (__fastcall**)(void*)>(*(char**)slot + 0x10))(slot);
        _ReadWriteBarrier();
    }
}
