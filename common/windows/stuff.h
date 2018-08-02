//---------------------------------------------------------------------------
#ifndef stufH
#define stufH

//---------------------------------------------------------------------------
//��������� �������� ����� �������� ���� ���� � �� ������� Application->Run();
int StartActions(void);
//��������� �������� ��� ���������� ������ �������
void StopActions(void);
//�������� �� ini-����� ����������
void LoadDataFromIni(void);
//��������� ��������� �� ��������� ������
void ReadArgs(void);

//���������� ���� �����/������ � ����
void StartLoop(void);
//���������� ���� �����/������ � ����
void StopLoop(void);
//������� ������� �� �������� ����������� ���� �����/������
//� ������ ��������������
void InitSync(void);
//��������� ������� �������������
void CloseSync(void);
//�������� ��� �������� ������ ����� �/�
void KickActions(int second);
//������������ ������������� core
//��� �������� ����� �/�,
//����� �� KickAction  
void CoreActions(int second);
//��������� ������ �� ���������� �������� ��� ������ �� ����� � � csv
AnsiString FormatSignalsStr(void);
//��������� ������ � ���������� ��������, ���������
AnsiString FormatSignalsHeader(void);
//�������� �������
void MakeCheckPower(void);
//��������� �������� ���������� �������
int DoOffCommand(int offtype);
//���� �������� ���������� �������� ��� �������� ���������
void msg(char * );
//���� �������� ���������� �������� ��� ���������� ����� ������������� ����������
void addCalibrArc(char * point, int coaltype, char * param, double val);
//��������� ����������� � ������������������
void MakeAlarm(void);
//����������� ������������ �������� �� ����� �������
void MakePbyVagWei(void);
//��������� �������������� ���� �� ����
void SaveCalbrFile(void);
//������� ��� �������
int ExecCommand(AnsiString command, AnsiString *answer);
//������� ��� ����
int ExecCoreCommand(AnsiString command, AnsiString *answer);
//��������� ��������� � �������� ������
void BetterAsh(void);
//��������� ��������� � ������ ���������
void BetterRoutes(void);
//��������� ��������� �������
void BetterVagons(void);
//������� ���������� �� �������
void __fastcall SocketErrorProc(int ErrorCode);
//��������� ��� ����� �������� ������
void CheckAutoReboot();

//---------------------------------------------------------------------------
#endif
