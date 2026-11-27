












struct BCDF_s;

void BCDF_attach_knot_sequence(struct BCDF_s* a, int count, double* knots)
{
    *reinterpret_cast<int*>(reinterpret_cast<char*>(a) + 0x74) = count;
    *reinterpret_cast<double**>(reinterpret_cast<char*>(a) + 0x78) = knots;
}
