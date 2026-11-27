





extern "C" void sub_180081BB0(long long a1, long long i, long long j)
{
    if (i < j)
    {
        long long** dstslot = *(long long***)a1;
        long long* src = **(long long***)(a1 + 8);
        for (; i < j; ++i)
            (*dstslot)[i] = src[i];
    }
}
