








struct BCDF_s;

double* BCDF_return_crvatr_deriv_pars_array(BCDF_s* a, int* count)
{
    unsigned char* node = *(unsigned char**)((char*)a + 0x40);
    double* data;
    if (node)
    {
        *count = *(int*)(node + 8);
        data = *(double**)node;
    }
    else
    {
        *count = 0;
        data = 0;
    }
    return data;
}
