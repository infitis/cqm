//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "global.h"

//---------------------------------------------------------------------------
AnsiString Title = "Тест-версия";
AnsiString ConfDir = "..\\etc";

/*
#ifdef CQM_SERVER_APPLICATION
AnsiString LogDir = "..\\log\\server";
#else
#ifdef CQM_CLIENT_APPLICATION
AnsiString LogDir = "..\\log\\client";
#else
AnsiString LogDir = "..\\log";
#endif
#endif
*/
AnsiString LogDir = AnsiString("..\\log\\")+LogName;

AnsiString SignalsLogDir = "..\\log\\signal";
AnsiString CalibrArcDir = "..\\log\\carc";
AnsiString AppIniFileName = ConfDir+"\\"+ExtractFileName(ChangeFileExt(Application->ExeName, ".ini"));

AnsiString ConnectionHost = "localhost";
int        ConnectionPort = 3306;
AnsiString ConnectionDataBase;
AnsiString ConnectionLogin = "root";
AnsiString ConnectionPassword = "";
bool       ConnectionSqlMonitor = false;

//---------------------------------------------------------------------------
char * RunningNowSemaphore       = "cqm_server_running_now_semaphore";
char * RunningNowClientSemaphore = "cqm_client_running_now_semaphore";
char * RunningNowICSemaphore     = "cqm_ic_running_now_semaphore";

//---------------------------------------------------------------------------
int RegisterApplication (const char * SemaphoreName)
{
    HANDLE hsem = CreateSemaphore (NULL, 1, 2, SemaphoreName);
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        CloseHandle (hsem);//Приложение уже работает
        return 1;
    }
    else
    {
        return 0;
    }
}


//---------------------------------------------------------------------------
AnsiString  __fastcall GetLastErrorMsg()
{
    LPVOID lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        GetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
        (LPTSTR) &lpMsgBuf,
        0,
        NULL
    );
    return AnsiString((char *)lpMsgBuf);
}

//---------------------------------------------------------------------------
int CheckDecimalSeparator(void)
{
    DecimalSeparator = '.';
    double d;
    return TryStrToFloat("1.01", d) ? 1 : 0; 
}

//---------------------------------------------------------------------------
int __fastcall CheckIniFile(void)
{
    if (FileExists(AppIniFileName))
        return 1;
    return 0;
}

//---------------------------------------------------------------------------
#pragma package(smart_init)

