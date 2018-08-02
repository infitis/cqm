//---------------------------------------------------------------------------
#include <inifiles.hpp>
#pragma hdrstop
#include "stuffic.h"
#include "cqmicdispatcher.h"
#include "fobjsel.h"
#include "global.h"
#include "globcli.h"
#include "fmainic.h"
#include "fmsgs.h"
#include "fcustomminutes.h"
#include "clientdata.h"
#include "fcustomashgraph.h"
//#include "fcustomvagonseditor.h"

//---------------------------------------------------------------------------
int Start()
{
    //��������� ����.���-����
    LoadDataFromIni();

    //�������� ����������
    IC = new CqmICDispatcher (ChangeFileExt(Application->ExeName, ".ini"));

    InitForms();

    ShowStartPosition();

    DoMsg("�����.");
    return 0;
}

//---------------------------------------------------------------------------
int Stop()
{
    if (IC->curObjectId >= 0)
    {
        CqmObjDeActivated(IC->curObjectId);
    }
    delete IC;

    DoMsg("����.");
    return 0;
}

//---------------------------------------------------------------------------
void LoadDataFromIni()
{
	TIniFile *ini;
    try{

    ini = new TIniFile(ChangeFileExt( Application->ExeName, ".ini" ) );

	Title =                 ini->ReadString("client" , "title", Title);

    RepIntervalsStartHour = ini->ReadInteger("client" , "repintervalsstarthour", RepIntervalsStartHour);
    RepIntervalsWorkingShift = ini->ReadInteger("client" , "repintervalsworkingshift", RepIntervalsWorkingShift);
    DayRepStartHour =       ini->ReadInteger("client" , "dayrepstarthour", DayRepStartHour);
    WorkingShift =          ini->ReadInteger("client" , "workingshift", WorkingShift);
    RepPosAllMonthPos =     ini->ReadInteger("client",  "repposallmonthpos", RepPosAllMonthPos);
    RepPosWRHVis =          ini->ReadInteger("client",  "repposwrhvis", RepPosWRHVis);
    VagonBatchPanelVisible= ini->ReadInteger("client",  "vagonbatchpanelvisible", VagonBatchPanelVisible);

    ConnectionHost =		ini->ReadString("connection" , "host", ConnectionHost);
	ConnectionPort =		ini->ReadInteger("connection" , "port", ConnectionPort);
	ConnectionDataBase =	ini->ReadString("connection" , "database", ConnectionDataBase);
	ConnectionLogin =		ini->ReadString("connection" , "login", ConnectionLogin);
	ConnectionPassword =	ini->ReadString("connection" , "password", ConnectionPassword);
    ConnectionSqlMonitor =  ini->ReadBool  ("connection" , "sqlmonitor", ConnectionSqlMonitor);

    }
    __finally
    {
        delete ini;
    }
}

//---------------------------------------------------------------------------
void InitForms()
{
    Application->Title = "��� ��������� - "+Title;
    MainICF->Caption  =  "��� ��������� - "+Title;
    ObjSelF->Init();
}

//---------------------------------------------------------------------------
void ShowStartPosition()
{
    MsgsF->WindowState     = wsMinimized;
    MinutesF->WindowState  = wsMinimized;
}

//---------------------------------------------------------------------------
void CqmObjActivated(int id)
{
    if (!IC->Activate(id))
    {
        DoMsg("������ ������������� ������� " + IC->Objects[id]->Title);
        Application->MessageBox("�� ������� ������� ������!", IC->Objects[id]->Title.c_str(), MB_OK+MB_ICONERROR);
        ObjSelF->CqmObjects[id]->ObjActive = false;
        return;
    }

    //��������� ���-����
	ini = new TMemIniFile(IC->curObject->IniFileName);

    //������� ���������� ������
    ReadClientData(IC->curObject->ClientData.c_str());

    //����������������� ��� �����
    //�������
    for(int i=0; i<clipointCount; i++)
    {
        CustomAshGraphF = new TCustomAshGraphF(Application);
        CustomAshGraphF->Init(i);
        AshGraphs[i] = CustomAshGraphF;
    }
    //����� �������
    if (clivagonCount <= 0)
    {
    }
    else
    {
        //��������� �������
        for(int i=0; i<clivagonCount; i++)
        {
            /*
            CustomVagonsEditorF = new TCustomVagonsEditorF(Application);
            CustomVagonsEditorF->Init(i);
            VagonsEditors[i] = CustomVagonsEditorF;
            */
        }
    }
    //�������� �����
    MinutesF->Init();

    //����������� ������ ������ � ��������
    MainICF->Nr->Enabled = true;
    MainICF->Na->Enabled = true;

    //������� �����
    RefreshActions();
    ShowWorkPosition();

    DoMsg("����������� ������: " + IC->Objects[id]->Title);
}

//---------------------------------------------------------------------------
void CqmObjDeActivated(int id)
{
    //����������� ������ ������
    MainICF->Nr->Enabled = false;
    MainICF->Na->Enabled = false;

    //������� �����
    for(int i=0; i<clipointCount; i++)
    {
        delete AshGraphs[i];
    }
    for(int i=0; i<clivagonCount; i++)
    {
        /*
        delete VagonsEditors[i];
        */
    }

    delete ini;

    IC->DeActivate(id);
    DoMsg("������������� ������: " + IC->Objects[id]->Title);
}

//---------------------------------------------------------------------------
void RefreshActions(void)
{
    ObjSelF->Refresh();

    //DoMsg("����������...");
    for(int i=0; i<clipointCount; i++)
    {
        AshGraphs[i]->Refresh();
    }
    for(int i=0; i<clivagonCount; i++)
    {
        /*
        VagonsEditors[i]->Refresh();
        */
    }
    MinutesF->Refresh();
    DoFlushBuf();
    //DoMsg("...���������.");
}

//---------------------------------------------------------------------------
void ShowWorkPosition(void)
{
    MsgsF->WindowState     = wsMinimized;
    MinutesF->WindowState  = wsMinimized;

    if (IC->curObjectId >= 0)
    {
        for(int i=0; i<clipointCount; i++)
        {
            AshGraphs[i]->WindowState = wsNormal;
            AshGraphs[i]->LoadPosition();
        }

        for(int i=0; i<clivagonCount; i++)
        {
            /*
            VagonsEditors[i]->WindowState = wsMinimized;
            */
        }

        AshGraphs[0]->SetFocus();
    }
}

//---------------------------------------------------------------------------
void ShowMinutes(void)
{
    MinutesF->WindowState  = wsMaximized;
    MinutesF->Show();
}

//---------------------------------------------------------------------------
void Action_Connect()
{
    if (!IC->Connect())
    {
        DoMsg("������ ��������� ���������� � �������� " + IC->curObject->Title);
        Application->MessageBox("�� ������� ���������� ���������� � ��������.", IC->curObject->Title.c_str(), MB_OK+MB_ICONERROR);
        return;
    }
}

//---------------------------------------------------------------------------
void Action_Disconnect()
{
    if (!IC->Disconnect())
    {
        DoMsg("������ ������� ���������� � �������� " + IC->curObject->Title);
        Application->MessageBox("�� ������� ��������� ���������� � ��������.", IC->curObject->Title.c_str(), MB_OK+MB_ICONERROR);
        return;
    }
}

//---------------------------------------------------------------------------
void Action_Update()
{
    if (!IC->Update())
    {
        DoMsg("������ ���������� ���� ������ " + IC->curObject->Title);
        Application->MessageBox("�� ������� �������� ���� ������.", IC->curObject->Title.c_str(), MB_OK+MB_ICONERROR);
        return;
    }
    RefreshActions();
}

//---------------------------------------------------------------------------
void Action_RestoreDB()
{
    if (!IC->Restore())
    {
        DoMsg("������ �������������� ���� ������ " + IC->curObject->Title);
        Application->MessageBox("�� ������� ������������ ���� ������.", IC->curObject->Title.c_str(), MB_OK+MB_ICONERROR);
        return;
    }
    RefreshActions();
}

//---------------------------------------------------------------------------
void Action_BackupDB()
{
    if (!IC->Backup())
    {
        DoMsg("������ �������������� ���� ������ " + IC->curObject->Title);
        Application->MessageBox("�� ������� ������� ��������. ����� ���� ������.", IC->curObject->Title.c_str(), MB_OK+MB_ICONERROR);
        return;
    }
    RefreshActions();
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
