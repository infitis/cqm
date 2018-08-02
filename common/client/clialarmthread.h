//---------------------------------------------------------------------------
#ifndef alarmthreadH
#define alarmthreadH

//---------------------------------------------------------------------------
#include <Classes.hpp>

//---------------------------------------------------------------------------
#include "falarm.h"

//---------------------------------------------------------------------------
void ShowAlarmForm(AnsiString par, AnsiString text);

//---------------------------------------------------------------------------
class TCliAlarmThread : public TThread
{
private:
    AnsiString par, text;
protected:
    void __fastcall Execute();
public:
    __fastcall TCliAlarmThread(AnsiString vpar, AnsiString vtext);
    bool executed;
    TAlarmF *AlarmF;
    void __fastcall DoForm(void);
};

//---------------------------------------------------------------------------
#endif
