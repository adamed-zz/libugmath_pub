



















namespace {

void dev_tol_slot0(void*) {}

void* const dev_itolerances_vftable[4] = {
    (void*)&dev_tol_slot0,
    (void*)&dev_tol_slot0,
    (void*)&dev_tol_slot0,
    (void*)&dev_tol_slot0,
};

}

extern "C" void sub_1800948F0(void* self)
{
    char* p = static_cast<char*>(self);
    if (p[0x38] != 0) {
        p[0x38] = 0;
        *reinterpret_cast<void**>(p + 0x18) = (void*)dev_itolerances_vftable;
    }
}
