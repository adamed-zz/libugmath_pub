
















struct PNTLST_s;

struct BCDF_s
{
    PNTLST_s* df_points;
    char      pad_08[0x58];
    double    field_60;
    int       field_68;
    int       field_6c;
    char      pad_70[0x10];
    void*     field_80;
    char      field_88;
    char      pad_89[3];
    int       field_8c;
};


extern "C" BCDF_s* sub_180015B80(void);


PNTLST_s* __cdecl PNTLST_create_from_list_of_pts(double* pts, int num, int stride);
void __cdecl BCDF_add_params(BCDF_s* a, double* params);
void __cdecl BCDF_add_weights(BCDF_s* a);

BCDF_s* __cdecl BCDF_create_df_from_pts(double* a1, int a2, int a3, int a4, double a5)
{
    BCDF_s* v9 = sub_180015B80();
    v9->df_points = PNTLST_create_from_list_of_pts(a1, a2, a3);
    v9->field_6c = 4;
    BCDF_add_params(v9, 0);
    v9->field_8c = 0;
    v9->field_80 = 0;
    if (a4 == 1)
    {
        BCDF_add_weights(v9);
        v9->field_60 = a5;
        v9->field_68 = 0;
        v9->field_88 = 0;
    }
    return v9;
}
