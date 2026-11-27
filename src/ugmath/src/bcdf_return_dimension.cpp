




















struct BCDF_s;

int BCDF_return_dimension(struct BCDF_s* a)
{
    unsigned long long result = *reinterpret_cast<const unsigned long long*>(a);
    if (!result)
        return 0;
    return *reinterpret_cast<const unsigned int*>(result + 16);
}
