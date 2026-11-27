













struct BCDF_s;

int BCDF_return_periodicity(struct BCDF_s* a)
{
    return *reinterpret_cast<const int*>(reinterpret_cast<const unsigned char*>(a) + 0x70);
}
