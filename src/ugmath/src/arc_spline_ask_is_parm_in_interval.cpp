







#include <math.h>

int ARC_SPLINE_ask_is_parm_in_interval(double parm, double start, double end, double period)
{
    int result = 0;

    if (fabs(period - 0.0) <= 1.0e-10)
    {
        if (!(end >= start))
            return result;
        if (fabs(parm - start) <= 1.0e-10)
            result = 11;
        if (fabs(parm - end) <= 1.0e-10)
            goto ret_end_parm;
        if (parm > start)
            goto interval_tail;
        return result;
    }

    if (fabs(parm - start) <= 1.0e-10)
        result = 11;
    if (fabs(parm - end) <= 1.0e-10)
        goto ret_end_parm;
    if (end >= start)
    {
        if (parm > start)
            goto interval_tail;
        return result;
    }

    if (fabs(parm - 0.0) <= 1.0e-10)
        return 1;
    if (fabs(parm - period) <= 1.0e-10)
        return 1;
    if (parm > start && period > parm)
        return 1;
    if (!(parm >= 0.0))
        return result;

interval_tail:
    if (!(end > parm))
        return result;
    return 1;

ret_end_parm:
    return 12;
}
