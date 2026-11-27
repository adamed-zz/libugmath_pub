





extern "C" void sub_180081950(long long a1, long long i, long long j)
{
    if (i < j)
    {
        double** dstslot = *(double***)a1;
        double* s = *(double**)(a1 + 8);
        for (; i < j; ++i)
            (*dstslot)[i] = (*dstslot)[i] * *s;
    }
}
