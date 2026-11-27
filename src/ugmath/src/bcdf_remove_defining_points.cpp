























__declspec(dllimport) void* SM_realloc(void* ptr, unsigned __int64 size);
__declspec(dllimport) int   MACH__checking_level;
__declspec(dllimport) __declspec(noreturn) void  ERROR_raise(const char* file, int line, int code,
                                        const char* msg, ...);

struct BCDF_s;
struct PNTLST_s;

struct PNTLST_s
{
    double* pts;
    int     num;
    int     alloc;
    int     dim;
};

struct BCDF_s
{
    PNTLST_s* node;
    PNTLST_s* slope_list;
    PNTLST_s* param_list;
    char      pad0[0x68];
    int*      constraint_types;
};

int     BCDF_return_periodicity(BCDF_s* a);
int     BCDF_return_num_of_slopes(BCDF_s* a);
int     BCDF_slope_at_point(BCDF_s* a, int idx, int* out);
void    BCDF_remove_slopes(BCDF_s* a, int start, int count);
int*    BCDF_return_constraint_type_array(BCDF_s* a, int* count);
void    PNTLST_remove_points(PNTLST_s* lst, int start, int count);
void    BCDF_add_params(BCDF_s* a, double* par);
int     BCDF_ask_algorithm_version(BCDF_s* a);
void    BCDF_add_needed_slopes(BCDF_s* a);
double* BCDF_return_df_point_array(BCDF_s* a, int* num, int* dim);

void BCDF_remove_defining_points(BCDF_s* a1, int a2, int a3)
{
    int       v4 = a3;
    int       v5 = a2;
    PNTLST_s* v19 = a1->node;
    int       v6 = v19->num;
    int       v18 = BCDF_return_periodicity(a1);
    int       v7 = a2 + a3;
    int       v17;

    if (MACH__checking_level > 0 && v7 > v6)
    {
        ERROR_raise("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_gen.c", 606,
                    1005316, "Error While Removing Points");
        __debugbreak();
    }

    if (BCDF_return_num_of_slopes(a1) > 0)
    {
        for (int i = v5; i < v7; ++i)
        {
            if (BCDF_slope_at_point(a1, i, &v17) == 1)
                BCDF_remove_slopes(a1, v17, 1);
        }
    }

    v17 = 0;
    int* v9 = BCDF_return_constraint_type_array(a1, &v17);
    int v10 = v17;
    if (v17 > 0 && v9 && v5 < v17 && v4 > 0)
    {
        int v11 = v5;
        if (v5 < v17 - v4)
        {
            int* v12 = &v9[v5];
            do
            {
                ++v11;
                *v12 = v12[v4];
                ++v12;
                v10 = v17;
            } while (v11 < v17 - v4);
        }
        a1->constraint_types = (int*)SM_realloc(v9, 4LL * (v10 - v4));
    }

    PNTLST_s* v13 = a1->param_list;
    PNTLST_s* v14 = a1->slope_list;
    PNTLST_remove_points(v19, v5, v4);
    PNTLST_remove_points(v13, v5, v4);
    PNTLST_remove_points(v14, v5, v4);

    if (!v5 || v7 == v6 - 1)
    {
        BCDF_add_params(a1, 0);
        if (!BCDF_ask_algorithm_version(a1))
            BCDF_add_needed_slopes(a1);
    }

    if (v18 == 1)
    {
        int v20, v21;
        if (!v5 || v7 == v6 - 1)
        {
            double* v16 = BCDF_return_df_point_array(a1, &v21, &v20);
            v16[v20 * (v21 - 1)]     = *v16;
            v16[v20 * (v21 - 1) + 1] = v16[1];
            v16[v20 * (v21 - 1) + 2] = v16[2];
            if (v20 == 4)
                v16[v20 * (v21 - 2) + 3] = v16[3];
        }
        else if (v5 == v6 - 1)
        {
            double* v15 = BCDF_return_df_point_array(a1, &v21, &v20);
            *v15   = v15[v20 * (v21 - 1)];
            v15[1] = v15[v20 * (v21 - 1) + 1];
            v15[2] = v15[v20 * (v21 - 1) + 2];
            if (v20 == 4)
                v15[3] = v15[v20 * (v21 - 1) + 3];
        }
    }
}
