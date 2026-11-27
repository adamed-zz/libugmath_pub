















#include <math.h>
#include <intrin.h>

__declspec(dllimport) void ERROR_raise(const char* file, int line, int code,
                                       const char* msg, ...);

void BCDF_CALC_unitize_slope(double* in, double* out)
{
    double len = sqrt(in[0] * in[0] + in[1] * in[1] + in[2] * in[2]);
    if (len <= 1.0e-10)
    {
        ERROR_raise("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_calc.c",
                    1248, 1005314, "The Input Slope Has Zero Length");
        __debugbreak();
        __assume(0);
    }
    out[0] = in[0] / len;
    out[1] = in[1] / len;
    out[2] = in[2] / len;
}
