









struct PNTLST_s;

struct BCDF_s
{
    PNTLST_s* points;
    PNTLST_s* node;
    char      pad_10[0x50];
    union
    {
        double    tolerance;
        long long tol_bits;
    };
    int       num_segments;
    char      pad_6c[0x04];
    int       periodicity;
    char      pad_74[0x18];
    int       field_8c;
};


void BCDF_convert_to_least_squares(BCDF_s* a, double tolerance);

void BCDF_change_number_of_segments(BCDF_s* a, int n)
{
    if (a->node == nullptr)
        BCDF_convert_to_least_squares(a, a->tolerance);


    bool v = a->field_8c < 2;
    a->num_segments = n;
    if (v)
        a->tol_bits = 0;
}
