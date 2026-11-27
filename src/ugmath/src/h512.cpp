










#include <math.h>

extern void h405(const int* a1, const double* a2, const double* a3, const double* a4,
                 const double* a5, const double* a6, const double* a7, int* a8, double* a9);
extern void h200(const double* a1, const double* a2, double* a3);

static const double kE0020 = 1.0e-6;

void h512(int const* a1, const double* a2, const double* a3, const double* a4,
          const double* a5, const double* a6, const double* a7, const double* a8,
          int* a9, double* a10)
{
    double* v10 = const_cast<double*>(a7);
    double* v11 = a10;
    const double* v12 = a8;
    double v16[10];
    int cnt = 0;
    h405(a1, a2, a3, a4, a5, a6, a7, &cnt, v16);
    switch (cnt)
    {
    case 1:
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    {
        double best;
        h200(v16, a8, &best);
        int m = cnt;
        if (m >= 1)
        {
            double* v14 = v16;
            int v15 = 0;
            do
            {
                double d;
                h200(&v16[v15], v12, &d);

                if (!(d >= best))
                {
                    best = d;
                    v16[0] = v14[0];
                    v16[1] = v14[1];
                }
                v15 += 2;
                v14 += 2;
                --m;
            } while (m);
        }
        break;
    }
    default:
        *a9 = 2;
        return;
    }
    double dist;
    h200(v16, v10, &dist);

    if (!(kE0020 >= fabs(dist)))
    {
        v11[0] = v16[0];
        v11[1] = v16[1];
        v11[2] = v10[2];
        *a9 = 1;
    }
    else
    {
        v11[0] = v10[0];
        v11[1] = v10[1];
        v11[2] = v10[2];
        *a9 = 3;
    }
}
