//---------------------------------------------------------------------------
#ifndef mainH
#define mainH

//---------------------------------------------------------------------------
class CqmCore;

//---------------------------------------------------------------------------
extern "C" __declspec(dllexport) int cqm_extension_start(int tag, char * msg);
extern "C" __declspec(dllexport) int cqm_extension_stop (int tag, char * msg);
extern "C" __declspec(dllexport) int c116c(int tag, char * msg, CqmCore * core);

//---------------------------------------------------------------------------
#endif
