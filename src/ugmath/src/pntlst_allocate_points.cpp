









__declspec(dllimport) void* SM_realloc(void* ptr, unsigned __int64 size);


struct PNTLST_s {
    void* points;
    int   num;
    int   alloc;
    int   stride;
};



void PNTLST_allocate_points(PNTLST_s* lst, int n)
{
    lst->points = SM_realloc(lst->points, lst->stride * (long long)n * 8);
    lst->alloc = n;
}
