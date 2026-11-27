








struct BCDF_s;



void BCDF_free_attributes(BCDF_s *a);


__declspec(dllimport) void SM_free(void *ptr);



void BCDF_free_structure(BCDF_s *a)
{
    BCDF_free_attributes(a);
    SM_free(a);
}
