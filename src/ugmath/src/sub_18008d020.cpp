



typedef long long i64;

extern "C" __declspec(noinline) i64 sub_18008D020(double* x, i64 sx, double* y, i64 sy,
                                                 i64 n, double cs, double sn)
{
    i64 result = n;
    i64 done = 0;
    if (n >= 4) {
        i64 groups = ((unsigned long long)(n - 4) >> 2) + 1;
        done = 4 * groups;
        do {
            double a = *x, b = *y;
            *x = a * cs + b * sn;
            x += sx;
            *y = b * cs - a * sn;
            y += sy;
            a = *x; b = *y;
            *x = a * cs + b * sn;
            x += sx;
            *y = b * cs - a * sn;
            y += sy;
            a = *x; b = *y;
            *x = a * cs + b * sn;
            x += sx;
            *y = b * cs - a * sn;
            y += sy;
            a = *x; b = *y;
            *x = a * cs + b * sn;
            x += sx;
            *y = b * cs - a * sn;
            y += sy;
            --groups;
        } while (groups);
    }
    if (done < n) {
        result = n - done;
        do {
            double a = *x, b = *y;
            *x = a * cs + b * sn;
            x += sx;
            *y = b * cs - a * sn;
            y += sy;
            --result;
        } while (result);
    }
    return result;
}
