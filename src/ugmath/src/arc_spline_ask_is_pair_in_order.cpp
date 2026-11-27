







#include <cmath>

bool ARC_SPLINE_ask_is_pair_in_order(double a1, double a2, double tol)
{
    double t = std::fabs(tol);
    bool result = true;
    if (t < 1.0e-10)
    {
        if (a1 > a2)
            result = false;
    }
    else if (t * 0.5 > std::fabs(a2 - a1))
    {
        if (a1 > a2)
            result = false;
    }
    else
    {
        if (a2 > a1)
            result = false;
    }
    return result;
}
