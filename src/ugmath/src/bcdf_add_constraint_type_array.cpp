











__declspec(dllimport) void SM_free(void *p);



struct BCDF_s
{
    char  pad[0x80];
    int  *constraint_type_array;
};

void BCDF_add_constraint_type_array(struct BCDF_s *a, int *arr)
{
    void *old = a->constraint_type_array;
    if (old)
        SM_free(old);
    a->constraint_type_array = arr;
}
