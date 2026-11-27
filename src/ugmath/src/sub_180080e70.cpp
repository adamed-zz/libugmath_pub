



typedef struct { long long q[6]; } Params;

extern "C" void sub_180080E70(long long** a1, long long first, long long last)
{
    if (first < last)
    {
        Params* p = (Params*)a1[1];
        const double* src = (const double*)p->q[1];
        double* dst = (double*)**a1;
        long long i = first;
        for (; i + 4 <= last; i += 4)
        {
            dst[i] = src[i] / ((double*)p)[4];
            dst[i + 1] = src[i + 1] / ((double*)p)[4];
            dst[i + 2] = src[i + 2] / ((double*)p)[4];
            dst[i + 3] = src[i + 3] / ((double*)p)[4];
        }
        if (i < last)
        {
            do
            {
                dst[i] = src[i] / ((double*)p)[4];
                ++i;
            } while (i < last);
        }
    }
}
