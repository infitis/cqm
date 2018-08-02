//---------------------------------------------------------------------------
#ifndef actH
#define actH
//---------------------------------------------------------------------------
class CqmCore;

//---------------------------------------------------------------------------
extern "C" __declspec(dllexport) int cqm_extension_start(char * msg);
extern "C" __declspec(dllexport) int cqm_extension_stop(char * msg);
extern "C" __declspec(dllexport) int c116c(char * msg, CqmCore * core);

//---------------------------------------------------------------------------
#endif
 