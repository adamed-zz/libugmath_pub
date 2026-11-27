







#include <exception>
#include <ostream>

extern "C" __declspec(noinline) void b48_ios_forward(void* p) {
    int unc = std::uncaught_exceptions();
    char* obj = *(char**)p;
    if (unc == 0) {
        ((std::basic_ostream<char>*)obj)->_Osfx();
    }
    char* inner = *(char**)(obj + *(int*)(*(char**)obj + 4) + 0x48);
    if (inner) {
        typedef void(__fastcall* VFn)(void*);
        ((VFn*)*(void***)inner)[2](inner);
    }
}
