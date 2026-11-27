






extern "C" void* g_b15_raw_base;

static double* G(unsigned rva) { return (double*)((char*)g_b15_raw_base + rva); }

static int clip_class(double v, double lo, double hi)
{

    if (lo <= v)
        return (v > hi) ? 2 : 0;
    return 1;
}

static int clip_code(const double* p)
{
    int c = clip_class(p[0], *G(0xE06C0), *G(0xE06D0));
    double y = p[1];
    if (*G(0xE06C8) <= y)
    {
        if (y > *G(0xE06D8))
            c |= 8;
    }
    else
        c |= 4;
    return c;
}

extern "C" long long sub_18004A260(double* a1, double* a2, double* a3,
                                   double* a4, double* a5, double* a6)
{
    const double xmin = *G(0xE06C0);
    const double xmax = *G(0xE06D0);
    const double ymin = *G(0xE06C8);
    const double ymax = *G(0xE06D8);
    int c1 = clip_code(a1);
    int c2 = clip_class(*a4, xmin, xmax);
    if (ymin <= *a5)
    {
        if (*a5 > ymax)
            c2 |= 8;
    }
    else
        c2 |= 4;

    for (;;)
    {
        if (!c1 && !c2)
            return 0;
        double x = 0.0, y = 0.0, z = 0.0;
        if ((c2 & c1) != 0)
            return 1;
        const int sel = c1 ? c1 : c2;
        if ((sel & 1) != 0)
        {
            x = xmin;
            double t = (xmin - *a1) / (*a4 - *a1);
            y = (*a5 - *a2) * t + *a2;
            z = (*a6 - *a3) * t + *a3;
        }
        else if ((sel & 2) != 0)
        {
            x = xmax;
            double t = (xmax - *a1) / (*a4 - *a1);
            y = (*a5 - *a2) * t + *a2;
            z = (*a6 - *a3) * t + *a3;
        }
        else if ((sel & 4) != 0)
        {
            y = ymin;
            double t = (ymin - *a2) / (*a5 - *a2);
            x = (*a4 - *a1) * t + *a1;
            z = (*a6 - *a3) * t + *a3;
        }
        else if ((sel & 8) != 0)
        {
            y = ymax;
            double t = (ymax - *a2) / (*a5 - *a2);
            x = (*a4 - *a1) * t + *a1;
            z = (*a6 - *a3) * t + *a3;
        }

        if (sel == c1)
        {
            *a1 = x;
            *a2 = y;
            *a3 = z;
            c1 = clip_class(x, xmin, xmax);
            if (ymin <= y)
            {
                if (y > ymax)
                    c1 |= 8;
            }
            else
                c1 |= 4;
        }
        else
        {
            *a4 = x;
            *a5 = y;
            *a6 = z;
            c2 = clip_class(x, xmin, xmax);
            if (ymin <= y)
            {
                if (y > ymax)
                    c2 |= 8;
            }
            else
                c2 |= 4;
        }
    }
}
