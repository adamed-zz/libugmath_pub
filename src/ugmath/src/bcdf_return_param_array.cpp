







struct BCDF_s;

double* BCDF_return_param_array(struct BCDF_s* a, int* count)
{
    *count = 0;
    double** node = *reinterpret_cast<double***>(reinterpret_cast<char*>(a) + 16);
    if (!node)
        return nullptr;
    *count = *reinterpret_cast<int*>(reinterpret_cast<char*>(node) + 8);
    return *node;
}
