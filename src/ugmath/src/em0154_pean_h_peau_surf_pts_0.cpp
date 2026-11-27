













#include <math.h>
#include <string.h>

struct XY
{
    double a;
    double b;
};

struct SURF_PTS
{
    double u;
    double v;
    double x;
    double y;
    double z;
};

void em0154(double* a1, int a2, SURF_PTS* a3, double* a4)
{
    double best = 1.0e19;
    double regs[2];

    if (a2 > 0)
    {
        double v7 = regs[1];
        double v8 = regs[0];
        double qx = a1[0];
        double qy = a1[1];
        double qz = a1[2];
        __int64 n = (unsigned int)a2;
        double* p = (double*)((char*)a3 + 32);
        do
        {
            double dx = *(p - 2) - qx;
            double dy = *(p - 1) - qy;
            double dz = *p - qz;
            double d = sqrt((dy * dy + dx * dx) + dz * dz);
            if (best > d)
            {
                v8 = *(p - 4);
                v7 = *(p - 3);
                best = d;
            }
            p += 5;
            --n;
        } while (n);
        a4[0] = v8;
        a4[1] = v7;
    }
    else
    {
        *(XY*)a4 = *(XY*)regs;
    }
}
