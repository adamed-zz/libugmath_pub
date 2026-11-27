







#include <cstdlib>

extern "C" bool sub_180033740(const void* a1, const void* a2)
{
    double k1 = *(const double*)a1;
    double k2 = *(const double*)a2;
    if (k2 > k1)
        return true;
    if (!(k1 > k2) && *(const int*)((const char*)a1 + 8) < *(const int*)((const char*)a2 + 8))
        return true;
    return false;
}
