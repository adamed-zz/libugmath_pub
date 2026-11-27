





extern "C" void sub_180081520(long long a1, long long i, long long j)
{
    if (i < j)
    {
        long long* cont = *(long long**)(a1 + 8);
        double* dst = *(double**)*(void**)a1;
        double* src = (double*)cont[3];
        double s = *(double*)(cont + 1);
        for (; i < j; ++i)
            dst[i] = src[i] * s;
    }
}
