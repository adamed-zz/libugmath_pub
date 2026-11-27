#pragma once

namespace UGS
{
namespace Math
{
struct Vector2
{
    double x;
    double y;
};
struct Vector3
{
    double x;
    double y;
    double z;
};
}
}

#ifdef B41_DLLIMPORT
extern __declspec(dllimport) int MACH__checking_level;
__declspec(dllimport) void ERROR_assertion_failed(const char*, int, const char*, ...);
#else
extern int MACH__checking_level;
void ERROR_assertion_failed(const char*, int, const char*, ...);
#endif



double EQ_ask_length_tolerance();
