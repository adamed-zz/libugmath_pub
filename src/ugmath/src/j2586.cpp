












void h805(double* a1, double* a2, int* mode, int* eq);

void j2586(double* a1, double* a2, double* a3, double* a4)
{
    int v10;
    int v11 = 1;
    h805(a1, a2, &v11, &v10);
    if (v10 == 1)
    {
        h805(a1 + 1, a2 + 1, &v11, &v10);
        if (v10 == 1)
        {
            h805(a1 + 2, a2 + 2, &v11, &v10);
            if (v10 == 1)
            {
                *a4 = 1.0;
                return;
            }
            *a4 = (a3[2] - a1[2]) / (a2[2] - a1[2]);
        }
        else
        {
            *a4 = (a3[1] - a1[1]) / (a2[1] - a1[1]);
        }
    }
    else
    {
        *a4 = (*a3 - *a1) / (*a2 - *a1);
    }
}
