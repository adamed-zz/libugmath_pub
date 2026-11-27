









struct BCDF_s;

double* BCDF_return_crvatr_deriv_array(struct BCDF_s* a, int* count1, int* count2)
{
    unsigned char* node = *(unsigned char**)((char*)a + 0x38);
    double* data;
    if (node)
    {
        *count1 = *(int*)(node + 8);
        *count2 = *(int*)(node + 16);
        data = *(double**)node;
    }
    else
    {
        *count1 = 0;
        *count2 = 0;
        data = 0;
    }
    return data;
}
