














struct BCDF_s;


struct BCDF_pars_array_s
{
    double* pars;
    int     count;
};

double* BCDF_return_crvatr_pars_array(BCDF_s* a, int* count)
{
    *count = 0;
    BCDF_pars_array_s* node =
        *reinterpret_cast<BCDF_pars_array_s**>(reinterpret_cast<char*>(a) + 0x30);
    if (node == nullptr)
        return nullptr;
    *count = node->count;
    return node->pars;
}
