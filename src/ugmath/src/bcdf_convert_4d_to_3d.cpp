








struct BCDF_s;
struct PNTLST_s;




void PNTLST_convert_4d_to_3d(struct PNTLST_s*);
double* BCDF_return_slope_array(struct BCDF_s*, int*, int*);

void BCDF_convert_4d_to_3d(struct BCDF_s* a)
{

    PNTLST_s* node = *reinterpret_cast<PNTLST_s**>(a);
    if (*reinterpret_cast<int*>(reinterpret_cast<char*>(node) + 0x10) == 4)
        PNTLST_convert_4d_to_3d(node);

    int num;
    int dim;
    double* slopes = BCDF_return_slope_array(a, &num, &dim);
    if (dim == 4)
    {
        int i = 1;
        if (num > 1)
        {
            __int64* q = reinterpret_cast<__int64*>(slopes);
            __int64* dx = q + 3;
            __int64* sx = q + 4;
            do
            {
                *dx = *sx;
                q[3 * i + 1] = q[4 * i + 1];
                q[3 * i + 2] = q[4 * i + 2];
                sx += 4; dx += 3;
                ++i;
            } while (i < num);
        }

        *reinterpret_cast<int*>(
            reinterpret_cast<char*>(
                *reinterpret_cast<void**>(reinterpret_cast<char*>(a) + 0x18)) + 0x10) = 3;
    }
}
