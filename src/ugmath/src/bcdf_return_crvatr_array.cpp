










struct BCDF_s;

double* BCDF_return_crvatr_array(BCDF_s* a1, int* count1, int* count2)
{
    double* result = nullptr;
    *count1 = 0;
    *count2 = 0;
    void* node = *(void**)((char*)a1 + 0x28);
    if (node) {
        *count1 = *(int*)((char*)node + 8);
        *count2 = *(int*)((char*)node + 16);
        result = *(double**)node;
    }
    return result;
}
