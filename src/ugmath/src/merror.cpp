










int g_merror_level = 0;
int g_merror_num = 0;

int merrorflush()
{
    g_merror_level = 0;
    g_merror_num = 0;
    return 0;
}

int merrorlevel()
{
    return g_merror_level;
}
