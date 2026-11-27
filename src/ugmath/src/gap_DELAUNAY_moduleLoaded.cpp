






#include "b37_math.h"

extern "C" int b37_delaunay_loaded;

bool DELAUNAY_moduleLoaded() {
    return b37_delaunay_loaded != 0;
}
