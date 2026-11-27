









struct BCDF_s;

int BCDF_return_num_of_crvatrs(struct BCDF_s* a1)
{
    unsigned long long result = *reinterpret_cast<unsigned long long*>(
        reinterpret_cast<char*>(a1) + 0x28);
    if (result == 0)
        return 0;
    return static_cast<int>(*reinterpret_cast<unsigned int*>(
        reinterpret_cast<char*>(result) + 8));
}
