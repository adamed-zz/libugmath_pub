









struct BCDF_s;

int* BCDF_return_crvatr_type_array(BCDF_s* a)
{
    return *reinterpret_cast<int**>(reinterpret_cast<char*>(a) + 0x50);
}
