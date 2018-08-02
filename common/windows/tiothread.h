//---------------------------------------------------------------------------
#ifndef tiothreadH
#define tiothreadH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include "logfile.h"

//---------------------------------------------------------------------------
//возможное отклонение интервала в 100ns
/*
#define TIMER_INTERVAL_DEVIATION 400000
*/
#define TIMER_INTERVAL_DEVIATION 000000

//---------------------------------------------------------------------------
class Tiothread : public TThread
{
private:
	AnsiString msg;
    HANDLE hTimer;//таймер
    HANDLE hStopIoThread;//событие, по которому нить останавливаетс€
    HANDLE hMT;//мутекс

    LARGE_INTEGER T;//тик в 100нс
    LARGE_INTEGER Da;//абсолютное врем€ установки таймера
    LARGE_INTEGER L;//врем€ последенего срабатывани€ таймера
    int Treal;//реальный интервал между срабатывани€ми таймера в мс
    DWORD TimerTimeout;

    void InitSync(void);
    void CloseSync(void);
    inline DWORD WaitSync(DWORD SObjCount, const HANDLE * SObjects);
    inline void InitTimer(void);
    inline void ResetTimer(void);
    inline void LoopBody(void);

    TLogFile * log;
    HWND Parent;

protected:
	void __fastcall Execute();

public:
	__fastcall Tiothread(HWND Par, bool CreateSuspended);
    __fastcall ~Tiothread(void);
    bool executing;
};
//---------------------------------------------------------------------------
#endif
