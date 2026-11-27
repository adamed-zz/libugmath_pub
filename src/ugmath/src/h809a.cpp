





void h806(const double* a1, const double* a2, const double* a3, int* a4);

void h809a(const double* a1, const double* a2, const int* a3, int* a4)
{

    *a4 = 1;
    const double* v4 = a2 + 1;
    if (!(*a1 >= *a2) || !(*v4 >= *a1))
    {
        double v7 = (*a3 == 1) ? 0.005 : 0.00001;
        double v9 = v7;
        int v8;
        h806(a1, a2, &v9, &v8);
        if (!v8)
        {
            h806(a1, v4, &v9, &v8);
            if (!v8)
                *a4 = 0;
        }
    }
}
