












namespace UGS { namespace Math { struct TransformMatrix; } }

extern "C" void sub_18009AF10(int a1, const char* a2, int dim, const void* mat);

void MTX4_lprintf(int a1, const char* a2, const UGS::Math::TransformMatrix* a3)
{
    sub_18009AF10(a1, a2, 4, a3);
}
