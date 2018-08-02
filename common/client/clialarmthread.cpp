//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "clialarmthread.h"
#include "fmsgs.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
TCliAlarmThread *CliAlarmThread = NULL;
int stopAlarm = 0;

//---------------------------------------------------------------------------
void ShowAlarmForm(AnsiString par, AnsiString text)
{
    if (stopAlarm > 0)
    {
        stopAlarm--;
        return;
    }

    if (CliAlarmThread != NULL)
    {
        if (CliAlarmThread->executed)
        {
            delete CliAlarmThread;
        }
        else
        {
            return;
        }
    }
    CliAlarmThread = new TCliAlarmThread(par, text);
    CliAlarmThread->Resume();
}

//---------------------------------------------------------------------------
__fastcall TCliAlarmThread::TCliAlarmThread(AnsiString vpar, AnsiString vtext)
    : TThread(true)
{
    FreeOnTerminate = false;
    Priority = tpLower;
    AlarmF = NULL;
    par = vpar;
    text = vtext;
    executed = false;
}

//---------------------------------------------------------------------------
void __fastcall TCliAlarmThread::Execute()
{
    Synchronize(DoForm);
    executed = true;
}

//---------------------------------------------------------------------------
void __fastcall TCliAlarmThread::DoForm(void)
{
    if (AlarmF) return;
    AlarmF = new TAlarmF(Application);
    AlarmF->LPar->Caption  = par;
    AlarmF->LWhat->Caption = text;
    AlarmF->ShowModal();
    if (AlarmF->CBStop->Checked)
    {
        stopAlarm = 15;
    }
    delete AlarmF;
    AlarmF = NULL;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
