







#include <cmath>


extern void MC_v_unit(double* const a);

void MC_perp_vec(double* const a1, double* const a2)
{
    double x = a1[0];
    double y = a1[1];
    if (fabs(x) > 0.5)
    {
        a2[1] = 1.0;
        a2[0] = -y / x;
        a2[2] = 0.0;
    }
    else
    {
        a2[0] = 1.0;
        if (fabs(y) > 0.5)
        {
            a2[1] = -a1[0] / a1[1];
            a2[2] = 0.0;
        }
        else
        {
            a2[1] = 0.0;
            a2[2] = -a1[0] / a1[2];
        }
    }
    MC_v_unit(a2);
}
