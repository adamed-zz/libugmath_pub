









struct BCDF_s
{
    unsigned char pad_000[0x88];
    bool uniform_segments;
};

bool BCDF_ask_ls_uniform_segments(struct BCDF_s* a)
{
    return a->uniform_segments;
}
