





extern "C" void sub_180081600(long long a1, long long i, long long j)
{
    if (i < j)
    {
        void** dstslot = *(void***)a1;
        char* cont = *(char**)(a1 + 8);
        long long* holder = *(long long**)(cont + 8);
        double* dst = (double*)*dstslot;
        long long n = holder[1];
        double divisor = *(double*)(cont + 24);
        for (; i < j; ++i)
        {
            double* row = (double*)(holder[0] + 8 * i);
            double sum;
            if (n)
            {
                sum = row[0];
                for (long long k = 1; k < n; ++k)
                    sum = sum + row[3 * k];
            }
            else
                sum = 0.0;
            dst[i] = sum / divisor;
        }
    }
}
