









struct BCDF_s;

int* BCDF_return_slope_type_array(struct BCDF_s* a)
{
    return *reinterpret_cast<int**>(reinterpret_cast<char*>(a) + 0x48);
}
