





























struct BCDF_s;

int* BCDF_return_constraint_type_array(BCDF_s* a, int* count)
{
    if (*reinterpret_cast<void**>(reinterpret_cast<char*>(a) + 0x80) &&
        *reinterpret_cast<void**>(a))
    {
        *count = *reinterpret_cast<int*>(
            reinterpret_cast<char*>(*reinterpret_cast<void**>(a)) + 8);
        return *reinterpret_cast<int**>(reinterpret_cast<char*>(a) + 0x80);
    }
    *count = 0;
    return *reinterpret_cast<int**>(reinterpret_cast<char*>(a) + 0x80);
}
