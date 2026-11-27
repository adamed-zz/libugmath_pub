






extern "C" void* g_b15_raw_base;

static double* G(unsigned rva) { return (double*)((char*)g_b15_raw_base + rva); }

static int clip_class(double v, double lo, double hi)
{
    if (lo <= v)
        return (v > hi) ? 2 : 0;
    return 1;
}

static int proj_code(const double* p)
{
    double z = -p[2];
    double x = p[0] / z;
    double y = p[1] / z;

    int c = clip_class(x, *G(0xE06C0), *G(0xE06D0));
    if (*G(0xE06C8) <= y)
    {
        if (y > *G(0xE06D8))
            c |= 8;
    }
    else
        c |= 4;
    return c;
}


static const unsigned kPlane[4][3] = {
    {0xE06E0, 0xE06E8, 0xE06F0},
    {0xE0710, 0xE0718, 0xE0720},
    {0xE06F8, 0xE0700, 0xE0708},
    {0xE0728, 0xE0730, 0xE0738}};
static const int kBit[4] = {1, 2, 4, 8};

extern "C" long long sub_18004BDF0(double* a1, double* a2, double* a3,
                                   double* a4, double* a5, double* a6)
{
    int c1 = proj_code(a1);
    int c2 = proj_code(a4);
    for (;;)
    {
        if (!c1 && !c2)
            return 0;
        double x = 0.0, y = 0.0;
        if ((c2 & c1) != 0)
            return 1;
        const int sel = c1 ? c1 : c2;
        for (int i = 0; i < 4; ++i)
        {
            if ((sel & kBit[i]) == 0)
                continue;
            const double* p = G(kPlane[i][0]);
            const double* q = G(kPlane[i][1]);
            const double* r = G(kPlane[i][2]);


            double d0 = *p * *a1 + *q * *a2 + *r * *a3;
            double d1 = *p * *a4 + *q * *a5 + *r * *a6;
            double t = (-0.000001 - d0) / (d1 - d0);
            double z = (*a6 - *a3) * t + *a3;
            x = (*a4 - *a1) * t + *a1;
            y = (*a5 - *a2) * t + *a2;
            if (sel == c1)
            {
                *a1 = x;
                *a2 = y;
                *a3 = z;
            }
            else
            {
                *a4 = x;
                *a5 = y;
                *a6 = z;
            }
            break;
        }
        if (sel == c1)
        {
            c1 = 0;
            double z = -*a3;
            double px = *a1 / z;
            double py = *a2 / z;
            if (*G(0xE06C0) <= px)
            {
                if (px > *G(0xE06D0))
                    c1 = 2;
            }
            else
                c1 = 1;
            if (*G(0xE06C8) <= py)
            {
                if (py > *G(0xE06D8))
                    c1 |= 8;
            }
            else
                c1 |= 4;
        }
        else
        {
            c2 = 0;
            double z = -*a6;
            double px = *a4 / z;
            double py = *a5 / z;
            if (*G(0xE06C0) <= px)
            {
                if (px > *G(0xE06D0))
                    c2 = 2;
            }
            else
                c2 = 1;
            if (*G(0xE06C8) <= py)
            {
                if (py > *G(0xE06D8))
                    c2 |= 8;
            }
            else
                c2 |= 4;
        }
    }
}
