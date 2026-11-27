








#include <math.h>
#include <cstdint>

extern "C" double sub_18007EC20(void* ws, void* unused, void* cfg);

extern "C" __declspec(noinline) double sub_18008BA10(long long* a1)
{
    long long v1 = a1[0];
    long long v2 = a1[1];
    long long ws[7] = {0, v1, v2, v1, v2, 0, 0};
    long long out = 0;
    long long cfg[4] = {0, (long long)(std::uintptr_t)a1, (long long)(std::uintptr_t)a1, 0};
    double mean = sub_18007EC20(ws, &out, cfg) / (double)(4 * (int)v2);
    return sqrt(mean);
}
