//---------------------------------------------------------------------------
#ifndef cqmextension_defH
#define cqmextension_defH

//---------------------------------------------------------------------------
class CqmCore;

//---------------------------------------------------------------------------
#ifdef CQM_ON_WINDOWS
#include <windows.h>
#include <winbase.h>
typedef int (*H_CQM_EXTENSION_START_PROC)(int, char*);
typedef int (*H_CQM_EXTENSION_STOP_PROC)(int, char*);
typedef int (*H_CQM_EXTENSION_PROC)(int, char*, CqmCore*);
#define CQM_EXTENSION_START_PROC_NAME "_cqm_extension_start"
#define CQM_EXTENSION_STOP_PROC_NAME  "_cqm_extension_stop"
#define CQM_EXTENSION_MSG_LEN         256
#endif

//---------------------------------------------------------------------------
//return codes
#define CQM_EXTENSION_IDLE      -1
#define CQM_EXTENSION_ERROR      0
#define CQM_EXTENSION_PROCESSED  1

//---------------------------------------------------------------------------
#endif

