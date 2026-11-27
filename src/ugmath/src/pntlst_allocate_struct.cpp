










__declspec(dllimport) void* SM_alloc(unsigned __int64 size);
__declspec(dllimport) void* SM_realloc(void* ptr, unsigned __int64 size);


struct PNTLST_s {
    double* points;
    int     num;
    int     alloc;
    int     dim;
};

PNTLST_s* PNTLST_allocate_struct(int a1, int a2)
{
    if (a2 <= 0)
        return 0;
    PNTLST_s* p = (PNTLST_s*)SM_alloc(0x18);
    p->dim = a1;
    p->num = 0;
    p->points = 0;

    p->points = (double*)SM_realloc(0, a1 * (long long)a2 * 8);
    p->alloc = a2;
    return p;
}
