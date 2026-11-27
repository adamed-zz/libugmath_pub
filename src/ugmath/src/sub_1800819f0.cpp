





extern "C" void sub_1800819F0(long long a1, long long i, long long j)
{
    if (i < j)
    {
        double** dstslot = *(double***)a1;
        char* cont = *(char**)(a1 + 8);
        for (; i < j; ++i)
            (*dstslot)[i] = (*(double**)(cont + 8))[i] - (*(double**)(cont + 24))[i];
    }
}
