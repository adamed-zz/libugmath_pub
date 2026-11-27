









extern int g_ugm_hlr_debug_level;

void HLR_FACET_set_debug_level(int a1)
{



    int v1 = g_ugm_hlr_debug_level;
    if (static_cast<unsigned>(a1) - 1u == 0u)
        v1 = a1;
    g_ugm_hlr_debug_level = v1;
}
