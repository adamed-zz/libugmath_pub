








struct PNTLST_s;


__declspec(dllimport) void __cdecl SM_free(void *p);

void PNTLST_free_all_but_points(PNTLST_s *a1)
{
    if (a1)
        SM_free(a1);
}
