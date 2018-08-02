//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "tiothread.h"
#include "global.h"
#include "globsrv.h"
#include "fmsgs.h"
#include "stuff.h"
#include "cqmcore.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
extern AnsiString LogDir;

//---------------------------------------------------------------------------
__fastcall Tiothread::Tiothread(HWND Par, bool CreateSuspended)
	: TThread(CreateSuspended)
{
    Parent = Par;
    //Priority = tpHighest;
    Priority = tpTimeCritical;
    T.QuadPart = Tick*10000;
    executing = false;
    Treal = 0;
    TimerTimeout = Tick*2;

    log = new TLogFile(LogDir, "iothr", "log");
    log->Add("CREATED.");
    log->Add(AnsiString("Tick = ")+IntToStr(Tick));
    FlushFileBuffers((HANDLE)log->iFileHandle);
}

//---------------------------------------------------------------------------
void __fastcall Tiothread::Execute()
{
    bool initsync_error = false;

    try
    {
        InitSync();
    }
    catch (Exception *E)
    {
        initsync_error = true;
        log->Add(AnsiString("InitSync error: ") + E->Message);
    }

    if (!initsync_error)
    {

    executing = true;
	log->Add("STARTED.");
    Beep(440, 30);

    InitTimer();

    HANDLE Handles[] = {hTimer, hStopIoThread};
    int HCount = 2;
    int SyncNo;
    while (true)
    {
        try
        {
            SyncNo = WaitSync (HCount, Handles);
            if (SyncNo==0) // hTimer
            {
                ResetTimer();
            	LoopBody();
                continue;
            }
            if (SyncNo==1) // hStopIoThreadEvent
            {
                break;
            }
        }
        catch (Exception *E)
        {
            log->Add(E->Message);
        }
    }

    }

    CloseSync();
	log->Add("EXIT.");
    Beep(220, 30);
    executing = false;
}

//---------------------------------------------------------------------------
void Tiothread::InitSync(void)
{
    //событие, по которому происходит остановка
    hStopIoThread = OpenEvent (SYNCHRONIZE, FALSE, StopIoThreadEventName.c_str());
    if (hStopIoThread == NULL)
    {
        throw Exception(AnsiString("Не удалось открыть") + StopIoThreadEventName + ": " + GetLastErrorMsg());
    }

    //таймер
    hTimer = CreateWaitableTimer (NULL, FALSE, iothrTimerName.c_str());
    if (hTimer == NULL)
    {
        throw Exception(AnsiString("Не удалось создать") + iothrTimerName + ": " + GetLastErrorMsg());
    }
    else
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        throw Exception(AnsiString("Попытка создать существующий таймер: ") + iothrTimerName);
    }

   	//Открываем мутекс для разделения доступа к core
	hMT = OpenMutex(SYNCHRONIZE, FALSE, MutexName.c_str());
    if (hMT == NULL)
    {
        throw Exception(AnsiString("Не удалось открыть: ") + MutexName + ": " + GetLastErrorMsg());
    }
}

//---------------------------------------------------------------------------
void Tiothread::CloseSync(void)
{
    if (!CloseHandle(hTimer))
        //throw Exception (AnsiString("Ошибка при закрытии ") + iothrTimerName + ": " + GetLastErrorMsg());
        log->Add(AnsiString("Ошибка при закрытии ") + iothrTimerName + ": " + GetLastErrorMsg());
    if (!CloseHandle(hStopIoThread))
        //throw Exception (AnsiString("Ошибка при закрытии ") + StopIoThreadEventName + ": " + GetLastErrorMsg());
        log->Add(AnsiString("Ошибка при закрытии ") + StopIoThreadEventName + ": " + GetLastErrorMsg());
    if (!CloseHandle(hMT))
        //throw Exception (AnsiString("Ошибка при закрытии ") + MutexName + ": " + GetLastErrorMsg());
        log->Add(AnsiString("Ошибка при закрытии ") + MutexName + ": " + GetLastErrorMsg());
}

//---------------------------------------------------------------------------
DWORD Tiothread::WaitSync(DWORD SObjCount, const HANDLE * SObjects)
{
    DWORD ret = WaitForMultipleObjects (SObjCount, SObjects, FALSE, TimerTimeout);

    if (ret == WAIT_FAILED)
    {
        throw Exception ("WAIT_FAILED");
    }
    else
    if (ret == WAIT_TIMEOUT)
    {
        throw Exception ("WAIT_TIMEOUT");
    }
    else
    if (ret >= WAIT_ABANDONED_0 && ret <= WAIT_ABANDONED_0+SObjCount-1)
    {
        throw Exception ("WAIT_ABANDONED_0+"+IntToStr(ret-SObjCount));
    }
    else
    if (ret >= WAIT_OBJECT_0   && ret <= WAIT_OBJECT_0+SObjCount-1)
    {
        return (ret-WAIT_OBJECT_0);
    }
    else
    {
        throw Exception("Unexpected wait result");
    }
}

//---------------------------------------------------------------------------
void Tiothread::InitTimer(void)
{
    SYSTEMTIME st;    GetLocalTime (&st);

    FILETIME ft;      SystemTimeToFileTime (&st, &ft);

    LARGE_INTEGER C;
    LARGE_INTEGER Dr;
    C.LowPart = ft.dwLowDateTime;
    C.HighPart = ft.dwHighDateTime;

    // D = С - C%T + 2T;
    // абсолютное время
    //D.QuadPart = C.QuadPart - (C.QuadPart % T.QuadPart) + 2*T.QuadPart;

    // D = C%T - 2T;
    // относительное время
    Dr.QuadPart = C.QuadPart % T.QuadPart - 2*T.QuadPart;

    if (!SetWaitableTimer(hTimer, &Dr, 0, NULL, NULL, TRUE))
    {
        log->Add(AnsiString("Ошибка SetWaitableTimer : "+GetLastErrorMsg()));
    }

    Da.QuadPart = C.QuadPart - (C.QuadPart % T.QuadPart) + 2*T.QuadPart;
    L = C;

    /*
    ft.dwLowDateTime =  Dr.LowPart;
    ft.dwHighDateTime = Dr.HighPart;
    FileTimeToSystemTime(&ft, &st);
    log->Add("init  r: "+FormatDateTime("yyyy-mm-dd hh:nn:ss.zzz", SystemTimeToDateTime(st)));

    ft.dwLowDateTime =  Da.LowPart;
    ft.dwHighDateTime = Da.HighPart;
    FileTimeToSystemTime(&ft, &st);
    log->Add("init  a: "+FormatDateTime("yyyy-mm-dd hh:nn:ss.zzz", SystemTimeToDateTime(st)));
    */
}

//---------------------------------------------------------------------------
void Tiothread::ResetTimer(void)
{
    SYSTEMTIME st;    GetLocalTime (&st);

    FILETIME ft;      SystemTimeToFileTime (&st, &ft);

    LARGE_INTEGER C;
    LARGE_INTEGER Dr;
    C.LowPart = ft.dwLowDateTime;
    C.HighPart = ft.dwHighDateTime;

    //определим относительное время
    if (C.QuadPart >= Da.QuadPart)
    {
        Dr.QuadPart  = C.QuadPart % T.QuadPart - T.QuadPart;
    }
    else
    {
        Dr.QuadPart =  C.QuadPart - Da.QuadPart - T.QuadPart;
    }

    if (!SetWaitableTimer(hTimer, &Dr, 0, NULL, NULL, TRUE))
    {
        log->Add(AnsiString("Ошибка SetWaitableTimer : "+GetLastErrorMsg()));
    }
    //определим абсолютное время
    if (C.QuadPart >= Da.QuadPart)
    {
        Da.QuadPart = C.QuadPart - C.QuadPart % T.QuadPart + T.QuadPart;
    }
    else
    {
        Da.QuadPart += T.QuadPart;
    }


    Treal = (C.QuadPart - L.QuadPart)/10000;
    L = C;

    /*
    ft.dwLowDateTime =  Da.LowPart;
    ft.dwHighDateTime = Da.HighPart;
    FileTimeToSystemTime(&ft, &st);
    log->Add("reset a: "+FormatDateTime("yyyy-mm-dd hh:nn:ss.zzz", SystemTimeToDateTime(st)));

    ft.dwLowDateTime =  Dr.LowPart;
    ft.dwHighDateTime = Dr.HighPart;
    FileTimeToSystemTime(&ft, &st);
    log->Add("reset r: "+FormatDateTime("yyyy-mm-dd hh:nn:ss.zzz", SystemTimeToDateTime(st)));

    log->Add("Treal  : "+IntToStr(Treal));
    */
}

//---------------------------------------------------------------------------
void Tiothread::LoopBody(void)
{
    DWORD ret = WaitForSingleObject(hMT, MutexCoreTimeOut);
    switch (ret)
    {
        // The thread got mutex ownership.
        case WAIT_OBJECT_0:
        {
            try
            {
                //Установим значения тика
                core.io_set_tick1(Treal);
                //Ну вот и ввод/вывод!
                core.io_read();
            }
            __finally
            {
                // Release ownership of the mutex object.
                if (! ReleaseMutex(hMT))
                {
                    throw Exception (AnsiString("Ошибка при освобождении ") + MutexName + ": " + GetLastErrorMsg());
                }
            }
            break;
        }
        // Cannot get mutex ownership due to time-out.
        case WAIT_TIMEOUT:
        {
            //throw Exception ("Таймаут ожидание доступа ядра.");
        }
        // Got ownership of the abandoned mutex object.
        case WAIT_ABANDONED:
        {
            //throw Exception (AnsiString("Закрытый мутекс: ") + MutexName + ": " + GetLastErrorMsg());
        }
    }

    //Уведомляем главную нить
    SYSTEMTIME st;
    GetLocalTime(&st);
    if (!PostMessage(Parent, WM_KICK_SERVER, st.wSecond, 0))
        log->Add(AnsiString("Ошибка при отправлении сообщения WM_KICK_SERVER: ") + GetLastErrorMsg());
}

//---------------------------------------------------------------------------
__fastcall Tiothread::~Tiothread()
{
    delete log;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

