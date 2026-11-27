




extern "C" void sub_180081400(long long a1, long long i, long long j)
{
    if (i < j)
    {
        long long* cont = *(long long**)(a1 + 8);
        double* dst = *(double**)*(void**)a1;
        do
        {
            long long n = cont[14];
            double* coef = (double*)cont[13];
            double* row = (double*)(cont[0] + 8 * i);
            double acc;
            if (n)
            {
                acc = row[0] * coef[0];
                for (long long k = 1; k < n; ++k)
                    acc = acc + coef[k] * row[3 * k];
            }
            else
                acc = 0.0;
            dst[i++] = acc;
        } while (i < j);
    }
}
