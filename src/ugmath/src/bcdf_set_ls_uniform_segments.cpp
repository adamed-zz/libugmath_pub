







struct BCDF_s;

void BCDF_set_ls_uniform_segments(struct BCDF_s *a, bool v)
{
    *((unsigned char *)a + 136) = v;
}
