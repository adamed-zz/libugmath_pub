

extern int g_merror_level;
extern int g_merror_num;
int merrornum() { return g_merror_num; }

extern "C" int* b38_merror_level_ptr() { return &g_merror_level; }
extern "C" int* b38_merror_num_ptr() { return &g_merror_num; }
