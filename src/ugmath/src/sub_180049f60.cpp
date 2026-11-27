






#include <cmath>

extern "C" void sub_180049F60(double* a1)
{
    double x = a1[0];
    double y = a1[1];
    double z = a1[2];
    double s = x * x + y * y;
    s = s + z * z;
    double len = sqrt(s);
    if (len > 0.0)
    {
        x = x / len;
        y = y / len;
        z = z / len;
    }
    else
    {
        x = 1.0;
        y = 0.0;
        z = 0.0;
    }
    a1[0] = x;
    a1[1] = y;
    a1[2] = z;
}
