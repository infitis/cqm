//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "CmdProc.h"
#include "global.h"
#include "fmsgs.h"

//---------------------------------------------------------------------------
inline int WaitExitCode(HANDLE hP, int Timeout);

//---------------------------------------------------------------------------
int CmdProc(AnsiString Title, AnsiString cmd, AnsiString params, int Timeout)
{
    unsigned long exitCode;

    STARTUPINFO S;  // STARTUPINFO
    S.lpReserved = NULL;
    S.lpDesktop = NULL;
    S.lpTitle = Title.c_str();
    S.dwX = 100;
    S.dwY = 100;
    S.dwXCountChars = 30;
    S.dwYCountChars = 35;
    S.dwFillAttribute = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
    S.dwFlags = STARTF_USEPOSITION | STARTF_USECOUNTCHARS | STARTF_USEFILLATTRIBUTE;
    S.cbReserved2 = 0;
    S.lpReserved2 = NULL;

    PROCESS_INFORMATION P;  // PROCESS_INFORMATION

    AnsiString commLine = cmd + " " + params;

    DoMsg("CmdProc : "+commLine);
    bool ret = CreateProcess(
    cmd.c_str(),    // pointer to name of executable module
    commLine.c_str(),   // pointer to command line string
    NULL,   // pointer to process security attributes
    NULL,   // pointer to thread security attributes
    FALSE,  // handle inheritance flag
    0,  // creation flags
    NULL,   // pointer to new environment block
    NULL,   // pointer to current directory name
    &S, // pointer to STARTUPINFO
    &P  // pointer to PROCESS_INFORMATION
   );

    if (!ret)
    {
        DoMsg("CmdProc : CreateProcess ошибка : "+GetLastErrorMsg());
        return GetLastError();
    }

    exitCode = WaitExitCode(P.hProcess, Timeout);

    DoMsg("CmdProc : exitCode = "+IntToStr(exitCode));
    return exitCode;
}

//---------------------------------------------------------------------------
int WaitExitCode(HANDLE hP, int Timeout)
{
    int allTime = 0;
    const int waitTick = 500;
    unsigned long exitCode;
    int ret;

    do
    {
        DWORD w = WaitForSingleObject(hP,  waitTick);
        switch (w)
        {
            case WAIT_TIMEOUT:
            {
                allTime += waitTick;
                Application->ProcessMessages();
                break;
            }
            case WAIT_OBJECT_0:
            {
                ret = GetExitCodeProcess(hP, &exitCode);
                if (!ret)
                {
                    exitCode = 2;
                    DoMsg("CmdProc : GetExitCodeProcess ошибка : "+GetLastErrorMsg());
                }
                return exitCode;
            }
        }
    }
    while (allTime < Timeout);

    DoMsg("CmdProc : Таймаут ожидания завершения выполнения скрипта.");
    return 1;
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
