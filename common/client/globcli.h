//---------------------------------------------------------------------------
#ifndef globcliH
#define globcliH

//---------------------------------------------------------------------------
#include <vcl.h>
#include <inifiles.hpp>
#pragma hdrstop

//---------------------------------------------------------------------------
#define MIN_ASH_VALUE 2.0

//---------------------------------------------------------------------------
extern TMemIniFile * ini;

//---------------------------------------------------------------------------

/*

    �� ������ 2.2.7

//��������� ������� �� ������
extern bool checkserver;
//������ �� ��������� ��� �������� ������
extern bool remoteserver;
*/

//  � ������ 2.2.8
//�������� � �������� ��� ���
extern bool isserver;

//���������� ������ ��� ������� ������� ��� �������
extern AnsiString ClientData;
//���� � ������� ��� ��� �������
extern AnsiString PathToServer;
//��� ����� � �����
extern AnsiString LogName;//FOR CLIENT TOO

//���� � ����� � �������� ���� �������������
extern AnsiString PathToCertFaceTemplate;

//---------------------------------------------------------------------------
//�������� ������������� �� ������ �������� ��� �� ������?
extern bool CertForBlank;
//� ������ ���� �������� �������� ����� �� ���������� ������ ���������
extern int RepIntervalsStartHour;
//������� ����� � ����� ��� ������������� ������
extern int RepIntervalsWorkingShift;
//� ������ ���� �������� �������� �������� �����
extern int DayRepStartHour;
//������� ����� � ����� (0 - ���� �� ����)
extern int WorkingShift;
//�������� � ����� �� �������� ��� ������� �� �����?
extern int RepPosAllMonthPos;
//�������� � ����� �� �������� ���������, ����� � �������?
extern int RepPosWRHVis;
//��������� ������ ��� ������ � �������� � ��������� �������
extern int VagonBatchPanelVisible;

//---------------------------------------------------------------------------
//��������� ���������� � cqmnet ��������
#define SOCKET_BUFFER_SIZE 4095
extern AnsiString CqmNetAddress;
extern AnsiString CqmNetHost;
extern int CqmNetPort;
extern int CqmNetTimeOut;

//---------------------------------------------------------------------------
#endif
