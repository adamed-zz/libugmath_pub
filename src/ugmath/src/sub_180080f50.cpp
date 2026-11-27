



typedef struct { long long q[6]; } Params;

extern "C" void sub_180080F50(long long** a1, long long first, long long last)
{
    if (first < last)
    {
        Params* p = (Params*)a1[1];
        const double* s = (const double*)p->q[3];
        double* dst = (double*)**a1;
        long long i = first;
        for (; i + 4 <= last; i += 4)
        {
            dst[i] = dst[i] - s[i] * ((double*)p)[1];
            dst[i + 1] = dst[i + 1] - s[i + 1] * ((double*)p)[1];
            dst[i + 2] = dst[i + 2] - s[i + 2] * ((double*)p)[1];
            dst[i + 3] = dst[i + 3] - s[i + 3] * ((double*)p)[1];
        }
        if (i < last)
        {
            do
            {
                dst[i] = dst[i] - s[i] * ((double*)p)[1];
                ++i;
            } while (i < last);
        }
    }
}
