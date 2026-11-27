






extern "C" __declspec(dllimport) __int64 RDEBUG_register_token(void *token);

extern "C" const char *off_1800E0148;
const char *off_1800E0148 = "POINTCLOUD_Matching_Error";

extern "C" __int64 sub_180001000() {
  return RDEBUG_register_token((void *)off_1800E0148);
}
