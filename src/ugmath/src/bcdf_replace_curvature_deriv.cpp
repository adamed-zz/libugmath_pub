




















struct BCDF_s;
struct PNTLST_s;

extern int BCDF_curvature_deriv_at_point(struct BCDF_s*, int, int*);
extern int BCDF_return_num_of_crvatr_derivs(struct BCDF_s*);
extern int BCDF_return_dimension(struct BCDF_s*);
extern double* BCDF_return_param_array(struct BCDF_s*, int*);
extern struct PNTLST_s* PNTLST_allocate_struct(int, int);
extern void PNTLST_insert_points(struct PNTLST_s*, int, int, double*);
extern void PNTLST_replace_points(struct PNTLST_s*, int, int, double*);

__declspec(dllimport) void* SM_realloc(void*, size_t);
extern "C" void* memmove(void*, const void*, size_t);

void BCDF_replace_curvature_deriv(struct BCDF_s* a, double* curv, int idx, int type)
{
    double p[4] = { curv[0], curv[1], curv[2], 0.0 };
    int pos;
    int count;
    struct PNTLST_s* list = *(struct PNTLST_s**)((char*)a + 0x38);
    if (list != nullptr)
    {
        if (BCDF_curvature_deriv_at_point(a, idx, &pos) == 1)
        {
            PNTLST_replace_points(list, 1, pos, p);
            goto store_type;
        }
    }
    else
    {
        pos = 0;
    }
    {
        int num = BCDF_return_num_of_crvatr_derivs(a);
        struct PNTLST_s* l = *(struct PNTLST_s**)((char*)a + 0x38);
        if (l == nullptr)
        {
            l = PNTLST_allocate_struct(BCDF_return_dimension(a), 1);
            *(struct PNTLST_s**)((char*)a + 0x38) = l;
            *(struct PNTLST_s**)((char*)a + 0x40) = PNTLST_allocate_struct(1, 1);
        }
        PNTLST_insert_points(l, 1, pos, p);
        double* pars = BCDF_return_param_array(a, &count);
        PNTLST_insert_points(*(struct PNTLST_s**)((char*)a + 0x40), 1, pos, &pars[idx]);
        int* types = (int*)SM_realloc(*(void**)((char*)a + 0x58), 4LL * (num + 1));
        *(void**)((char*)a + 0x58) = types;
        memmove(&types[pos + 1], &types[pos], 4LL * (num - pos));
    }
store_type:
    ((int*)*(void**)((char*)a + 0x58))[pos] = type;
}
