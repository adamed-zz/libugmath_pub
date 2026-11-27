#include "kits/b18_kit/b18_support.h"




void map23(double *a1, double *a2)
{
    a2[0] = sin(a1[2]) * a1[0] * cos(a1[1]);
    a2[1] = sin(a1[2]) * a1[0] * sin(a1[1]);
    a2[2] = cos(a1[2]) * a1[0];
}
