




extern "C" void sub_180080DE0(long long** a1, long long first, long long last)
{
    if (first < last)
    {
        long long* p = (long long*)a1[1];
        long long* dst = (long long*)**a1;
        long long i = first;
        for (; i + 4 <= last; i += 4)
        {
            dst[i] = p[0];
            dst[i + 1] = p[0];
            dst[i + 2] = p[0];
            dst[i + 3] = p[0];
        }
        if (i < last)
        {
            do
            {
                dst[i] = p[0];
                ++i;
            } while (i < last);
        }
    }
}
