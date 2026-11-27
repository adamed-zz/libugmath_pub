
















#pragma once








struct _iobuf;

namespace UGS
{
namespace System
{
__declspec(dllimport) int SYSS_fprintf(::_iobuf* file, const char* fmt, ...);
}
}

__declspec(dllimport) __declspec(noreturn) void ERROR_raise(const char* file,
                                                            int line, int arg,
                                                            const char* expr, ...);


void MC_v_unit(double* const a);

#include <math.h>
#include <stdio.h>

void MC_v_unit(double* const a)
{
    double x = a[0];
    double y = a[1];
    double z = a[2];
    double len2 = x * x;
    len2 += y * y;
    len2 += z * z;
    double len = sqrt(len2);
    if (len < 0.0001)
    {
        UGS::System::SYSS_fprintf(stdout, "\nERROR: zero vector in unitize\n");
        ERROR_raise(R"(o:\nx2412\ip1700\src\ugmath\no\ind\mc_math.c)", 226, 17,
                    "tried to unitize null vector");
    }
    a[0] = x / len;
    a[1] = y / len;
    a[2] = z / len;
}
