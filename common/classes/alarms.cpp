//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "alarms.h"
#include "alarmthread.h"

//---------------------------------------------------------------------------
extern void DoMsg(AnsiString m);

//---------------------------------------------------------------------------
TAlarmThread * AlarmThread = NULL;

//---------------------------------------------------------------------------
void Alarm(int type)
{
    if (AlarmThread != NULL)
        delete AlarmThread;
    AlarmThread = new TAlarmThread(type, true);
    AlarmThread->Resume();
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
