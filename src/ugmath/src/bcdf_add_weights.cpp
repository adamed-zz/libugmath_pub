

















struct PNTLST_s
{
    double* points;
    int     num;
    int     alloc;
    int     dim;
};

struct BCDF_s
{
    char      pad_00[0x08];
    PNTLST_s* node;
    char      pad_10[0x60];
    int       periodicity;
    char      pad_74[0x18];
    int       field_8c;
};

#ifdef BCDF_SMOKE

extern int MACH__checking_level;
void ERROR_raise(const char* file, int line, int code, const char* msg, ...);
#else

__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_raise(const char* file, int line, int code,
                                       const char* msg, ...);
#endif


double* BCDF_return_param_array(BCDF_s* a, int* count);
PNTLST_s* PNTLST_allocate_struct(int dim, int n);
void PNTLST_allocate_points(PNTLST_s* lst, int n);
void BCDF_CALC_weights(int periodicity, int count, double* params, double* out);

void BCDF_add_weights(BCDF_s* a)
{
    if (MACH__checking_level > 0 && a->periodicity == 1 && !a->field_8c)
    {
        ERROR_raise("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_gen.c",
                    2341, 1005312, "Periodic Least Squares Splines Are Not Allowed");
        __debugbreak();
        __assume(0);
    }
    int n;
    double* params = BCDF_return_param_array(a, &n);
    PNTLST_s* node = a->node;
    if (!node)
    {
        node = PNTLST_allocate_struct(1, n);
    }
    else if (node->alloc < n)
    {
        PNTLST_allocate_points(node, n);
    }
    node->num = n;
    BCDF_CALC_weights(a->periodicity, n, params, node->points);
    a->node = node;
}
