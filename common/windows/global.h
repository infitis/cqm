//---------------------------------------------------------------------------
#ifndef globalH
#define globalH

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
//������, ������� ���������������� �� ini-�����

//��� ����� � �����
extern AnsiString LogName;
//��������, ������ ���������
extern AnsiString Title;
//���������� �� ����� ���������
extern AnsiString ConfDir;
//���� � ����� �������
extern AnsiString LogDir;//FOR CLIENT TOO
//���� � ������ � ������� ��������
extern AnsiString SignalsLogDir;//FOR CLIENT TOO
//���� � ������ � ������� ����������
extern AnsiString CalibrArcDir;//FOR CLIENT TOO
//���� � �������� ���
extern AnsiString AppIniFileName;

//���������� � ��
extern AnsiString ConnectionHost;//FOR CLIENT TOO
extern int        ConnectionPort;//FOR CLIENT TOO
extern AnsiString ConnectionDataBase;//FOR CLIENT TOO
extern AnsiString ConnectionLogin;//FOR CLIENT TOO
extern AnsiString ConnectionPassword;//FOR CLIENT TOO
//���������� sql ��������
extern bool       ConnectionSqlMonitor;

//---------------------------------------------------------------------------
//������ ��� ������� - �������
extern char * RunningNowSemaphore;//FOR CLIENT TOO
//������ ��� ������� - �������
extern char * RunningNowClientSemaphore;//FOR CLIENT TOO
//��������� ��� ������� - �������
extern char * RunningNowICSemaphore;
//���������, �� �������� �� ��� ���� ����� ���������
int RegisterApplication (const char * SemaphoreName);
//������������� ����� '.' � �������� ����������� ����� � ������� �����
int CheckDecimalSeparator(void);

//---------------------------------------------------------------------------
//����������� �� ���� �/�, ��� �������, ��� ������ ���������
#define WM_KICK_SERVER (WM_APP + 400)

//---------------------------------------------------------------------------
//�������� ��������� � ��������� ��������� ������
AnsiString __fastcall GetLastErrorMsg();

//---------------------------------------------------------------------------
//��������� ������� ���-�����
int __fastcall CheckIniFile(void);

//---------------------------------------------------------------------------
#endif

