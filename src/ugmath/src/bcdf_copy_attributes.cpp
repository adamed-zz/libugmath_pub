







struct BCDF_s;

extern void BCDF_free_attributes(struct BCDF_s*);

extern "C" void sub_180011DB0(struct BCDF_s** src, long long dst);

void BCDF_copy_attributes(struct BCDF_s* src, struct BCDF_s* dst)
{
    BCDF_free_attributes(dst);
    sub_180011DB0(reinterpret_cast<struct BCDF_s**>(src), reinterpret_cast<long long>(dst));
}
