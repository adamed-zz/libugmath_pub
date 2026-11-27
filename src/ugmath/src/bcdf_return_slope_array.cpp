








struct BCDF_s;

double* BCDF_return_slope_array(struct BCDF_s* a, int* count1, int* count2)
{
    *count1 = 0;
    *count2 = 0;
    double** node = *reinterpret_cast<double***>(reinterpret_cast<char*>(a) + 0x18);
    if (!node)
        return nullptr;
    *count1 = *reinterpret_cast<int*>(reinterpret_cast<char*>(node) + 8);
    *count2 = *reinterpret_cast<int*>(reinterpret_cast<char*>(node) + 16);
    return *node;
}
