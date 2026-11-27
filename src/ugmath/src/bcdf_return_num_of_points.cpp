







struct BCDF_s;

int BCDF_return_num_of_points(struct BCDF_s* a)
{
    struct BCDF_s* result = *reinterpret_cast<struct BCDF_s**>(a);
    if (!result)
        return 0;
    return *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(result) + 8);
}
