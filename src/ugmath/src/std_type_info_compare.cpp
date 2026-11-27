



























extern "C" int __cdecl __std_type_info_compare(const void* lhs, const void* rhs)
{
    if (lhs == rhs)
        return 0;
    const unsigned char* a = static_cast<const unsigned char*>(lhs) + 9;
    const unsigned char* b = static_cast<const unsigned char*>(rhs) + 9;
    while (*a == *b)
    {
        if (!*a)
            return 0;
        ++a;
        ++b;
    }
    return *a < *b ? -1 : 1;
}
