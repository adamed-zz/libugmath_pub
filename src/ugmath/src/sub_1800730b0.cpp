








#include <ostream>

extern "C" void* __fastcall b27_ostream_insert(void* os, const char* s) {
    std::ostream& out = *static_cast<std::ostream*>(os);
    out << s;
    return &out;
}
