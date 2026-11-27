











struct BCDF_s;

int* BCDF_return_crvatr_deriv_type_array(struct BCDF_s* a)
{

    return *reinterpret_cast<int**>(reinterpret_cast<unsigned char*>(a) + 0x58);
}
