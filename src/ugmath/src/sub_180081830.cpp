









extern "C" void sub_180081830(long long a1, long long i, long long j)
{
    if (i < j)
    {
        double** dstslot = *(double***)a1;
        char* cont = *(char**)(a1 + 8);
        double* src = *(double**)(cont + 24);
        double s = *(double*)(cont + 8);
        for (; i < j; ++i)
            (*dstslot)[i] = src[i] * s;
    }
}
