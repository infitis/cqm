//---------------------------------------------------------------------------
#include <string.h>

//---------------------------------------------------------------------------
#include "cqmextensions.h"
#include "cqmcore.h"

//---------------------------------------------------------------------------
CqmExtension::CqmExtension(void)
{
    loaded = 0;
    strcpy(mytype, "модуль");
#ifdef CQM_ON_WINDOWS
    hModule = 0;
    hStartProc = 0;
    hStopProc = 0;
    hProc = 0;
#endif
}

//---------------------------------------------------------------------------
CqmExtension::~CqmExtension(void)
{
}

//---------------------------------------------------------------------------
void CqmExtension::Start(void)
{
    loaded = 0;
#ifdef CQM_ON_WINDOWS
    hModule = LoadLibrary(path);
    if (hModule)
    {
        loaded = 1;
        sprintf(debugstr, "%s загружен.", path);
        m(debugstr);
        GetProcs();
    }
    else
    {
        sprintf(debugstr, "%s ошибка загрузки: %i", path, GetLastError());
        m(debugstr);
    }
#endif
    if (!loaded)
    {
        m("модуль не доступен.");
#ifdef CQM_ON_WINDOWS
        if (hModule)
            FreeLibrary(hModule);
#endif
    }
}

#ifdef CQM_ON_WINDOWS
//---------------------------------------------------------------------------
void CqmExtension::GetProcs(void)
{
    int ret;
    char msg[CQM_EXTENSION_MSG_LEN] = "";

    hStartProc = (H_CQM_EXTENSION_START_PROC) GetProcAddress(hModule, CQM_EXTENSION_START_PROC_NAME);
    if (!hStartProc)
    {
        loaded = 0;
        sprintf(debugstr, "GetProcAddress %s ошибка: %i", CQM_EXTENSION_START_PROC_NAME, GetLastError());
        m(debugstr);
    }

    hStopProc =  (H_CQM_EXTENSION_STOP_PROC)  GetProcAddress(hModule, CQM_EXTENSION_STOP_PROC_NAME);
    if (!hStopProc)
    {
        loaded = 0;
        sprintf(debugstr, "GetProcAddress %s ошибка: %i", CQM_EXTENSION_STOP_PROC_NAME, GetLastError());
        m(debugstr);
    }

    hProc =      (H_CQM_EXTENSION_PROC)       GetProcAddress(hModule, proc);
    if (!hProc)
    {
        loaded = 0;
        sprintf(debugstr, "GetProcAddress %s ошибка: %i", proc, GetLastError());
        m(debugstr);
    }

    if (hStartProc)
    {
        ret = (*hStartProc)(0, msg);
        sprintf(debugstr, "%s: %i, %s", CQM_EXTENSION_START_PROC_NAME, ret, msg);
        m(debugstr);
    }

}
#endif

//---------------------------------------------------------------------------
void CqmExtension::Make(void)
{
    if (!loaded) return;
    int ret = CQM_EXTENSION_IDLE;
    char msg[CQM_EXTENSION_MSG_LEN] = "";

#ifdef CQM_ON_WINDOWS
    ret = (*hProc)(0, msg, &core);
#endif

    if (ret == CQM_EXTENSION_ERROR)
    {
        sprintf(debugstr, "ошибка: %i, %s", ret, msg);
        m(debugstr);
    }
    else
    if (ret >= CQM_EXTENSION_PROCESSED)
    {
        if (core.vi("debug") & CORE_DEBUG_ENTITYS)
        {
            sprintf(debugstr, "%i, %s", ret, msg);
            m(debugstr);
        }
    }
    else
    if (ret == CQM_EXTENSION_IDLE)
    {
        //расширениие ничего ни сделало
    }
}

//---------------------------------------------------------------------------
void CqmExtension::Stop(void)
{
    if (!loaded) return;
#ifdef CQM_ON_WINDOWS
    int ret;
    char msg[CQM_EXTENSION_MSG_LEN] = "";
    ret = (*hStopProc)(0, msg);
    sprintf(debugstr, "%s: %i, %s", CQM_EXTENSION_STOP_PROC_NAME, ret, msg);
    m(debugstr);

    if (!FreeLibrary(hModule))
    {
        sprintf(debugstr, "ошибка освобождение: %i", GetLastError());
        m(debugstr);
    }
#endif
}

//---------------------------------------------------------------------------
istream& CqmExtension::Input(istream& s)
{
    s>>name>>title>>path>>proc;
    return s;
}

//---------------------------------------------------------------------------
ostream& CqmExtension::Print(ostream& s)
{
    return s<<name<<"\t"<<title<<"\t"<<path<<"\t"<<proc;
}

//---------------------------------------------------------------------------
ostream& operator<< (ostream& s, CqmExtension& f)
{
	return f.Print(s);
}

//---------------------------------------------------------------------------
istream& operator>> (istream& s, CqmExtension& f)
{
    return f.Input(s);
}

//---------------------------------------------------------------------------

