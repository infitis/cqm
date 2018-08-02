//---------------------------------------------------------------------------
#ifndef globsrvH
#define globsrvH

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "tiothread.h"
#include "WinPort32.h"

//---------------------------------------------------------------------------
#define OFF_SERVER      0
#define OFF_RESTART     1
#define OFF_REBOOT      2
#define OFF_HALT        3
#define OFF_FORCE       4
#define OFF_POWEROFF    5

//---------------------------------------------------------------------------
//������, ������� ������������ ���������� ������� core
extern HANDLE hMTXCore;

//��� ������� ��� ������������� ���� ��������� � ������� ����
//������� �� ����� ���������� core - ��������
extern AnsiString MutexName;

//��� ����� � �����
extern AnsiString LogName;
//���� � ��������� �����/������
extern AnsiString IoConfFile;
//���� � ��������� ����� ��������
extern AnsiString PointsConfFile;
//������ ���� � ������� ��� ����� � ������� ��������
extern AnsiString DateTimeFormatForSignals;

//---------------------------------------------------------------------------
//��������� �� ����� ���� �����/������
extern Tiothread * iothr;

//---------------------------------------------------------------------------
//������������ �� ����-����� (�������� ��������)
extern bool iousing;
//�������� �� ���� �����/������
extern bool iothrstarted;
//�������, �� �������� �������������� ���� �����/������
extern HANDLE hStopIoThreadEvent;
//��� ����� �������
extern AnsiString StopIoThreadEventName;
//������� ��������� ����
extern DWORD iothrStopTimeOut;
//��� ����������� ������� ���� �����/������
extern AnsiString iothrTimerName;
//������� ��� ������� ���������� ������� � core
extern DWORD MutexCoreTimeOut;

//---------------------------------------------------------------------------
//�������� ������� ���� �/�
extern DWORD Tick;
//����� �������� ������� ���� �����/������
extern DWORD iothrStartingTimeOut;

//---------------------------------------------------------------------------
//��������� cqmnet �������
extern int CqmNetPort;

//---------------------------------------------------------------------------
//����������� ��������� ���������� ����������� � �������
//����������� �� ������� perm
extern int MAX_SERVER_CONNS;

//---------------------------------------------------------------------------
//����� �� ��������� ������� ����� CoreActions
extern bool NeedRefresh;

//---------------------------------------------------------------------------
//�������� ������� �������
//����� �� ��������� ������� ������� (�� ini)
extern bool CheckPower;
//��� ������� �� ������� (�� ini)
extern AnsiString PowerSignalName;
//������������� ��������� �������
extern bool NeedPowerOff;
//������� ��� ���������� (�� ini)
extern AnsiString OffCommand;
//����� ���������� ��� ���������� ������� (0: SERVER, 1: RESTART, 2: REBOOT, 3: HALT, 4: FORCE, 5: POWEROFF)
//���� �� �������, �� 5 (POWER_OFF).
extern int DefaultOffMethod;


//---------------------------------------------------------------------------
//�������������� ������������ ����� ������ ������ ������
//                            60*60*24*7
#define MAX_WORK_TIME_SECONDS 604800

extern bool NeedAutoReboot;

//---------------------------------------------------------------------------
//���� ��� �����/������
extern TWinPort cqmPort;	// ����
//������� ������ � ������
bool PortCheck(AnsiString *m);
int  PortReadByte (int addr);
void PortWriteByte(int addr, int data);

//---------------------------------------------------------------------------
//������������ �� ������ ��� ������ � ��������
extern bool usePassword;
//����������, ������
extern AnsiString ServerPassword;
//������ ��-��� nshell
extern bool is_nShell;

//---------------------------------------------------------------------------
#endif
