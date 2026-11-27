









struct BCDF_s;

int BCDF_ask_algorithm_version(struct BCDF_s* a)
{
    return *reinterpret_cast<int*>(reinterpret_cast<char*>(a) + 0x8c);
}
