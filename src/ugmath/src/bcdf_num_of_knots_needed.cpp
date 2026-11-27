



















struct BCDF_s;



int BCDF_return_num_of_constraints(struct BCDF_s* a1);
int BCDF_return_order(struct BCDF_s* a1);
int BCDF_return_periodicity(struct BCDF_s* a1);

int BCDF_num_of_knots_needed(struct BCDF_s* a1, int a2)
{
    int v5 = BCDF_return_num_of_constraints(a1) + BCDF_return_order(a1);
    if (BCDF_return_periodicity(a1) == 1)
    {
        a2 = a2 + 1;
        if (a2 > BCDF_return_order(a1) - 1)
            a2 = BCDF_return_order(a1) - 1;
        return a2 + v5;
    }
    return v5;
}
