







void h808(const double* a1, const double* a2, const double* a3, const int* a4, int* a5)
{
    *a5 = 2;
    switch (*a4)
    {
    case 2:
        if (*a1 > *a2 + *a3)
            *a5 = 1;
        break;
    default:
        if (*a2 - *a3 > *a1)
            *a5 = 1;
        break;
    }
}
