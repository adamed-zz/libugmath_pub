


extern int g_merror_level;
extern int g_merror_num;
void merrorpush(char* const name, int num, int level) {
    (void)name;
    g_merror_num = num;
    g_merror_level = level;
}


