





extern "C" void sub_1800816E0(long long a1, long long i, long long j)
{
    if (i < j)
    {
        do
        {
            (**(double***)a1)[i] = (**(double***)(a1 + 8))[i];
            ++i;
        } while (i < j);
    }
}
