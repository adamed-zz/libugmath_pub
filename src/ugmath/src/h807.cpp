









struct IAAP { void** vtbl; };

IAAP* GetAcomParameterAccess();
double EQ_ask_number_tolerance();

void h807(const double* a1, const double* a2, const int* a3, const int* a4, int* a5)
{
    double v5;
    IAAP* p;

    if (*a4)
    {
        if (*a4 == 1)
        {
            p = GetAcomParameterAccess();
            v5 = ((double (*)(IAAP*))p->vtbl[2])(p);
        }
        else
        {
            p = GetAcomParameterAccess();
            v5 = ((double (*)(IAAP*))p->vtbl[5])(p);
        }
    }
    else
    {
        v5 = EQ_ask_number_tolerance();
    }

    double v11 = *a1;
    int v12 = 0;
    double v13 = v5;
    double v14 = *a2;
    bool v16;
    if (*a3 == 1)
    {
        double v15 = v14 - v13;
        v16 = !(v15 > v11);
    }
    else
    {
        double v18 = v14 + v13;
        v16 = !(v11 > v18);
    }
    v12 = v16 ? 1 : 0;
    *a5 = v12 + 1;
}
