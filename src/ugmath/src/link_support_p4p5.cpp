








#include "ugmath/tolerance.h"

#include <cmath>
#include <cstddef>
#include <cstdlib>







extern "C" void* B22RawAlloc(std::size_t n)
{
    return std::malloc(n != 0 ? n : 1);
}

extern "C" void B22RawFree(void* p)
{
    std::free(p);
}








extern "C" void b15_free_rec(void* p)
{
    std::free(p);
}










double EQ_ask_number_tolerance(void);

extern "C" double ds_eq_num()
{
    return EQ_ask_number_tolerance();
}


extern double __cdecl EQ_ask_length_tolerance(void);

extern "C" double ds_eq_len()
{
    return EQ_ask_length_tolerance();
}













static unsigned char g_b15_mirror[0x1000000];

extern "C" void* g_b15_raw_base = g_b15_mirror;





extern "C" void g_ugm_hlr_normalize(double* v)
{
    const double len = std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    if (len > 0.0)
    {
        v[0] /= len;
        v[1] /= len;
        v[2] /= len;
    }
}
