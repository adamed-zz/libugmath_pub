












enum HLR_FACET_severity_codes_t : int;
enum HLR_FACET_diagnostic_codes_t : int;




extern "C" void (*g_ugm_hlr_diag_cb)(int, int, const char*);

void HLR_FACET_set_diag_callback(
    void (*cb)(HLR_FACET_severity_codes_t, HLR_FACET_diagnostic_codes_t, const char*))
{
    g_ugm_hlr_diag_cb = reinterpret_cast<void (*)(int, int, const char*)>(cb);
}
