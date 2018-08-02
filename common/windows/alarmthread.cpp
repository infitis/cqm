//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "alarmthread.h"
#include "alarms.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall TAlarmThread::TAlarmThread(int alarmtype, bool CreateSuspended)
    : TThread(CreateSuspended)
{
    FreeOnTerminate = false;
    Priority = tpLower;
    type = alarmtype;
}

//---------------------------------------------------------------------------
void __fastcall TAlarmThread::Execute()
{
    if (type & AL_SIMPLY)
    {
        Sleep(125);
        Beep(220, 125);
        Sleep(125);
        Beep(220, 125);
    }
    if (type & AL_SOURCE)
    {
        Sleep(125);
        Beep(440, 125);
        Sleep(125);
        Beep(440, 125);
    }
    if (type & AL_BREAK)
    {
        Sleep(125);
        Beep(880, 125);
        Sleep(125);
        Beep(880, 125);
    }
}

//---------------------------------------------------------------------------
