








#include "b37_math.h"

extern "C" {
extern void* b37_delaunay_slots[72];
extern int b37_delaunay_loaded;
}

void DELAUNAY_unloadModule() {
    if (b37_delaunay_loaded) {
        UGS::System::Loader::ldr_unload_module("libwm5");
        b37_delaunay_loaded = 0;
#ifndef B37_GATE_BUILD

        *(int*)((char*)b37_delaunay_slots + 0x240) = 0;
#endif
    }
}
