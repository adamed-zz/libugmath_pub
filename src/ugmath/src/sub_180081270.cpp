





extern "C" void sub_180081270(double*** a1, long long i, long long j)
{
    if (i < j)
    {
        double* dest = **a1;
        double* src = *a1[1];
        for (; i < j; ++i)
            dest[i] = src[i] + dest[i];
    }
}
