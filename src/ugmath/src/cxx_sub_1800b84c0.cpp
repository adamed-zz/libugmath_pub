








#include <exception>
#include <ostream>

extern "C" void b48_ios_forward(void* p);


extern "C" void __fastcall sub_1800B84C0(void* self, void* p) {
    b48_ios_forward((char*)p + 0x20);
}
