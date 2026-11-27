




























struct BCDF_s;
struct PNTLST_s;

extern int BCDF_slope_at_point(struct BCDF_s*, int, int*);
extern int BCDF_return_num_of_slopes(struct BCDF_s*);
extern int BCDF_return_dimension(struct BCDF_s*);
extern double* BCDF_return_param_array(struct BCDF_s*, int*);
extern struct PNTLST_s* PNTLST_allocate_struct(int, int);
extern void PNTLST_insert_points(struct PNTLST_s*, int, int, double*);
extern void PNTLST_replace_points(struct PNTLST_s*, int, int, double*);
extern void sub_180019820(struct BCDF_s*, int, double*);

__declspec(dllimport) void* SM_realloc(void*, size_t);
extern "C" void* memmove(void*, const void*, size_t);

void BCDF_replace_slope(struct BCDF_s* a, double* slope, int idx, int type)
{
    double p[4] = { slope[0], slope[1], slope[2], 0.0 };
    int pos = 0;
    int count;
    struct PNTLST_s* slopes = *(struct PNTLST_s**)((char*)a + 0x18);
    if (slopes != nullptr)
    {
        if (BCDF_slope_at_point(a, idx, &pos) == 1)
        {
            sub_180019820(a, idx, p);
            PNTLST_replace_points(slopes, 1, pos, p);
            goto replace_done;
        }
    }
    {
        int num = BCDF_return_num_of_slopes(a);
        struct PNTLST_s* list = *(struct PNTLST_s**)((char*)a + 0x18);
        if (list == nullptr)
        {
            list = PNTLST_allocate_struct(BCDF_return_dimension(a), 1);
            *(struct PNTLST_s**)((char*)a + 0x18) = list;
            *(struct PNTLST_s**)((char*)a + 0x20) = PNTLST_allocate_struct(1, 1);
        }
        PNTLST_insert_points(list, 1, pos, p);
        double* pars = BCDF_return_param_array(a, &count);
        PNTLST_insert_points(*(struct PNTLST_s**)((char*)a + 0x20), 1, pos, &pars[idx]);
        int* types = (int*)SM_realloc(*(void**)((char*)a + 0x48), 4LL * (num + 1));
        *(void**)((char*)a + 0x48) = types;
        memmove(&types[pos + 1], &types[pos], 4LL * (num - pos));
    }
replace_done:
    ((int*)*(void**)((char*)a + 0x48))[pos] = type;
}
