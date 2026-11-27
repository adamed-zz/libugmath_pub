

























static void dev_typeinfo_slot0(void*) {}

static void* const dev_typeinfo_vftable[4] = {
    (void*)&dev_typeinfo_slot0,
    (void*)&dev_typeinfo_slot0,
    (void*)&dev_typeinfo_slot0,
    (void*)&dev_typeinfo_slot0,
};

struct DevTypeInfo {
    void* vt;
    void* zero;
    char name[96];
};

static DevTypeInfo dev_type_info = {
    (void*)dev_typeinfo_vftable,
    nullptr,
    ".?AV?$MakeSharedDeleter@VThreadTolerances@?A0xebca64ed@@@Memory@UGS@@",
};

extern "C" int __std_type_info_compare(const void*, const void*);

extern "C" void* sub_180094910(void* self, void* a2)
{
    if (__std_type_info_compare(static_cast<char*>(a2) + 8, &dev_type_info.zero) == 0)
        return static_cast<char*>(self) + 0x18;
    return nullptr;
}
