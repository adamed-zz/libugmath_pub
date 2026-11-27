







#include <cmath>

static const double kLenTol = 1e-8;
static const double kNumTol = 1e-10;
static const double kHugeTol = 1e+19;
static const int kTolType0 = 0;
static const int kTolType1 = 1;
static const double kZero = 0.0;



void h805(const double* a1, const double* a2, const int* toltype, int* out);




__declspec(noinline) void vunt3(const double* a1, int* ok, double* a2)
{
    const double len = std::sqrt(a1[0] * a1[0] + a1[1] * a1[1] + a1[2] * a1[2]);



    if (!(kLenTol >= len))
    {
        const double inv = 1.0 / len;
        a2[0] = a1[0] * inv;
        a2[1] = a1[1] * inv;
        a2[2] = a1[2] * inv;
        *ok = 1;
    }
    else
    {
        a2[0] = 0.0;
        a2[1] = 0.0;
        a2[2] = 0.0;
        *ok = 0;
    }
}



void h431(const double* a1, const double* d, const double* a3, int* out1, double* out2, double* out3);




void h434(const double* a1, const double* a2, const double* a3, int* out1);

void k255b(double* a1, double* a2, double* a3, int* a4)
{
    const double d[3] = { a2[0] - a1[0], a2[1] - a1[1], 0.0 };
    const double p1[3] = { a1[0], a1[1], 0.0 };
    const double p2[3] = { a2[0], a2[1], 0.0 };
    const double p3[3] = { a3[0], a3[1], 0.0 };
    int mode = 0;
    double proj[3];
    double dist = 0.0;
    h431(p1, d, p3, &mode, proj, &dist);
    h434(p1, p2, proj, &mode);
    if (mode == 2)
    {
        const double len = std::sqrt(d[0] * d[0] + d[1] * d[1]);
        if (len == 0.0)
        {
            *a4 = 0;
            return;
        }
        const double ex = a3[0] - a1[0];
        const double ey = a3[1] - a1[1];
        const double dl = std::sqrt(ex * ex + ey * ey);
        double pct = dl * 100.0 / len;
        if (pct > 0.0)
            pct += 0.5;
        else
            pct -= 0.5;
        *a4 = (int)pct;
    }
    else
    {
        const double ex = a3[0] - a1[0];
        const double ey = a3[1] - a1[1];
        const double d1 = std::sqrt(ex * ex + ey * ey);
        const double fx = a3[0] - a2[0];
        const double fy = a3[1] - a2[1];
        const double d2 = std::sqrt(fx * fx + fy * fy);
        *a4 = (d2 > d1) ? 0 : 100;
    }
}
