







#include <cmath>

double EQ_ask_number_tolerance(void);

void h014(double *a1, double *a2, double *a3, int *a4, int *a5, int *a6)
{
    *a6 = 0;
    *a5 = 0;
    *a4 = 1;
    a2[0] = 0.0;
    a2[1] = 0.0;
    a3[0] = 0.0;
    a3[1] = 0.0;
    double len = sqrt(a1[0] * a1[0] + a1[1] * a1[1] + a1[2] * a1[2]);
    if (EQ_ask_number_tolerance() >= fabs(len))
    {
        *a4 = 4;
        return;
    }
    double nx = a1[0] / len;
    double ny = a1[1] / len;
    double nz = a1[2] / len;
    if (!(EQ_ask_number_tolerance() >= fabs(nz)))
    {
        *a5 = 2;
        double v16 = nz + nz;
        double d;
        if (!(EQ_ask_number_tolerance() >= fabs(ny)))
            d = ny * ny - nz * 4.0 * nx;
        else
            d = nz * -4.0 * nx;
        double ad = fabs(d);
        double sq;
        if (!(EQ_ask_number_tolerance() >= ad))
            sq = sqrt(ad);
        else
            sq = 0.0;
        double v19 = -ny;
        if (!(d > 0.0 - EQ_ask_number_tolerance()))
        {
            *a4 = 2;
            *a2 = v19 / v16;
            *a3 = sq / v16;
            a2[1] = *a2;
            a3[1] = -*a3;
        }
        else
        {
            *a4 = 3;
            *a6 = 2;
            *a2 = (sq - ny) / v16;
            a2[1] = (v19 - sq) / v16;
        }
        return;
    }
    if (!(EQ_ask_number_tolerance() >= fabs(ny)))
    {
        *a4 = 3;
        *a5 = 1;
        *a6 = 1;
        *a2 = -nx / ny;
        return;
    }
    if (EQ_ask_number_tolerance() >= fabs(nx))
        *a4 = 4;
}
