



#include <cmath>

void h923(double* a1, double* a2, double* a3)
{
    const double s = sin(*a2);
    const double c = cos(*a2);
    const double x = *a1;
    const double y = a1[1];
    const double z = a1[2];
    const double xs = x * s;
    const double zs = z * s;
    const double xom = x * (1.0 - c);
    const double yom = y * (1.0 - c);
    const double ys = y * s;
    a3[2] = ys + xom * z;
    *a3 = xom * x + c;
    a3[1] = xom * y - zs;
    a3[4] = yom * y + c;
    a3[6] = xom * z - ys;
    a3[5] = yom * z - xs;
    a3[7] = xs + yom * z;
    a3[3] = zs + xom * y;
    a3[8] = z * (1.0 - c) * z + c;
}
