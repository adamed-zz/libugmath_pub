













struct BCDF_s
{
    char   pad_00[0x08];
    void*  node;
    char   pad_10[0x50];
    double tolerance;
    int    field_68;
    char   pad_6C[0x20];
    int    field_8c;
};


void BCDF_convert_to_least_squares(BCDF_s* a, double tol);

void BCDF_change_tolerance(BCDF_s* a, double tol)
{
    if (!a->node)
        BCDF_convert_to_least_squares(a, a->tolerance);
    bool v = a->field_8c < 2;
    a->tolerance = tol;
    if (v)
        a->field_68 = 0;
}
