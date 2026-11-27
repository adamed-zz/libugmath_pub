



typedef struct { long long q[6]; } Params;

extern "C" void sub_1800811B0(long long** a1, long long first, long long last)
{
    if (first < last)
    {
        Params* p = (Params*)a1[1];
        long long* other = (long long*)p->q[0];
        long long* dst = (long long*)**a1;
        long long i = first;
        for (; i + 4 <= last; i += 4)
        {
            long long a0 = dst[i], b0 = other[i];
            dst[i] = b0; other[i] = a0;
            long long a1v = dst[i + 1], b1 = other[i + 1];
            dst[i + 1] = b1; other[i + 1] = a1v;
            long long a2 = dst[i + 2], b2 = other[i + 2];
            dst[i + 2] = b2; other[i + 2] = a2;
            long long a3 = dst[i + 3], b3 = other[i + 3];
            dst[i + 3] = b3; other[i + 3] = a3;
        }
        if (i < last)
        {
            do
            {
                long long a = dst[i], b = other[i];
                dst[i] = b;
                other[i] = a;
                ++i;
            } while (i < last);
        }
    }
}
