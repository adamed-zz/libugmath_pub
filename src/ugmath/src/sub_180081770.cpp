





extern "C" void sub_180081770(long long a1, long long i, long long j)
{
    if (i < j)
    {
        char* cont = *(char**)(a1 + 8);
        double** dstslot = *(double***)a1;
        for (; i < j; ++i)
            (*dstslot)[i] = (*(double**)(cont + 8))[i] / *(double*)(cont + 16);
    }
}
