#include "kits/b18_kit/b18_support.h"






void map22(double *a1, double *a2)
{
    a2[0] = sqrt(a1[1] * a1[1] + a1[0] * a1[0] + a1[2] * a1[2]);
    h053(a1 + 1, a1, a2 + 1);
    double x = a1[0];
    double y = a1[1];
    double v8 = sqrt(x * x + y * y);
    h053(&v8, a1 + 2, a2 + 2);
}
