










struct BCDF_s;


void BCDF_detach_knot_sequence(struct BCDF_s* a)
{
    *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(a) + 0x74) = 0;
    *reinterpret_cast<unsigned long long*>(reinterpret_cast<char*>(a) + 0x78) = 0;
}
