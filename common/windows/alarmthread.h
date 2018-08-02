//---------------------------------------------------------------------------
#ifndef alarmthreadH
#define alarmthreadH

//---------------------------------------------------------------------------
#include <Classes.hpp>

//---------------------------------------------------------------------------
class TAlarmThread : public TThread
{
private:
protected:
    int type;
    void __fastcall Execute();
public:
    __fastcall TAlarmThread(int alarmtype, bool CreateSuspended=false);
};

//---------------------------------------------------------------------------
#endif
