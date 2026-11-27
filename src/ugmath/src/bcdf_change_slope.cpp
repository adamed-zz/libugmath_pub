

















struct BCDF_s;

extern "C" void sub_180015F00(struct BCDF_s* a1, int a2);
void BCDF_CALC_normalized_slope(struct BCDF_s* a1, int a2, int a3, double* a4);
void BCDF_replace_slope(struct BCDF_s* a1, double* a2, int a3, int a4);

void BCDF_change_slope(struct BCDF_s* a1, int a2, double* a3, int a4)
{
    switch (a2)
    {
    case 0:
        sub_180015F00(a1, a4);
        break;
    case 1:
        BCDF_replace_slope(a1, a3, a4, 1);
        break;
    case 2:
    case 3:
    case 4:
    case 5:
        BCDF_CALC_normalized_slope(a1, a2, a4, a3);
        BCDF_replace_slope(a1, a3, a4, a2);
        break;
    default:
        return;
    }
}
