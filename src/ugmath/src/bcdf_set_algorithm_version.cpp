









struct BCDF_s;


void BCDF_set_algorithm_version(struct BCDF_s* a, int v)
{
    *reinterpret_cast<int*>(reinterpret_cast<char*>(a) + 0x8c) = v;
}
