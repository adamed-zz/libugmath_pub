















struct ARC_SPLINE_1_seg_2d_s
{
    int    tag;
    int    direction;
    unsigned char pad0[0x10];
    double start_parm;
    double end_parm;
};

int ARC_SPLINE_ask_is_parm_in_arc_domain(const ARC_SPLINE_1_seg_2d_s* a1,
                                         double a2,
                                         double* a3)
{
    int v3 = a1->direction;
    int result = 1;
    double v5 = *a3;
    double v6 = a1->start_parm;
    double v7 = a1->end_parm;

    if (v3 > 0)
    {
        if (v5 >= v6 - a2 && v6 > v5)
        {
            result = 0;
            v5 = v6;
        }
        else if (v5 >= v6)
        {
            if (v6 + a2 >= v5)
                result = 0;
        }
        if (v5 > v7 && v7 + a2 >= v5)
        {
            *a3 = v7;
            v5 = v7;
            result = 0;
            return result;
        }
        if (v5 >= v7 - a2 && v7 >= v5)
            result = 0;
        else if (result && v5 > v6 && v7 > v5)
        {
            *a3 = v5;
            return -1;
        }
    }
    else
    {
        if (v3 >= 0)
            goto LABEL_33;
        int v8 = 0;
        if (v5 > v6 && v6 + a2 >= v5)
        {
            result = 0;
            v5 = v6;
        }
        else if (v5 >= v6 - a2 && v6 >= v5)
        {
            result = 0;
        }
        if (v5 >= v7 - a2 && v7 > v5)
        {
            *a3 = v7;
            v5 = v7;
            result = 0;
            return result;
        }
        if (v5 >= v7 && v7 + a2 >= v5)
            goto LABEL_32;
        if (!(result && v5 > v7))
            goto LABEL_33;
        v8 = result;
        if (v6 > v5)
            v8 = -1;
LABEL_32:
        result = v8;
    }
LABEL_33:
    *a3 = v5;
    return result;
}
