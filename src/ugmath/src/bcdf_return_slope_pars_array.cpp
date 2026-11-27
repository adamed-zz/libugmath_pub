





struct BCDF_s;

double* BCDF_return_slope_pars_array(BCDF_s* a, int* count)
{
    *count = 0;
    double** node = *(double***)((char*)a + 0x20);
    if (!node)
        return 0;
    *count = *((int*)node + 2);
    return *node;
}
