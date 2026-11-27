






#include <math.h>
#include <intrin.h>



__declspec(dllimport) void ERROR_internal(const char* file, int line, const char* msg, ...);

double ARC_SPLINE_ask_min_central_angle(double radius, double chord)
{
    double v;
    if ( radius < 1.0e-10 )
    {
        ERROR_internal(
            "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\arc_spline_apollonian_constructions.c",
            16136,
            "The radius is zero.");
        __debugbreak();
        __assume(0);
    }
    v = 1.0 - chord * chord * 0.5 / (radius * radius);


    return acos((v > 1.0) ? 1.0 : ((v < -1.0) ? -1.0 : v)) * 57.29577951308235;
}
