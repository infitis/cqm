//---------------------------------------------------------------------------
#ifndef tiothreadH
#define tiothreadH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include "logfile.h"

//---------------------------------------------------------------------------
//��������� ���������� ��������� � 100ns
/*
#define TIMER_INTERVAL_DEVIATION 400000
*/
#define TIMER_INTERVAL_DEVIATION 000000

//---------------------------------------------------------------------------
class Tiothread : public TThread
{
private:
	AnsiString msg;
    HANDLE hTimer;//������
    HANDLE hStopIoThread;//�������, �� �������� ���� ���������������
    HANDLE hMT;//������

    LARGE_INTEGER T;//��� � 100��
    LARGE_INTEGER Da;//���������� ����� ��������� �������
    LARGE_INTEGER L;//����� ����������� ������������ �������
    int Treal;//�������� �������� ����� �������������� ������� � ��
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
