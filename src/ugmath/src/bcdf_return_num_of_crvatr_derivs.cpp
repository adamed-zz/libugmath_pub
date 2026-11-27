








struct BCDF_s;

int BCDF_return_num_of_crvatr_derivs(struct BCDF_s* a1)
{
    __int64 result = *((__int64*)a1 + 7);
    if (result)
        return *(unsigned int*)(result + 8);
    return (int)result;
}
