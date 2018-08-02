//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "../common/windows/stuff.h"
#include "../common/windows/global.h"
#include "../common/windows/globsrv.h"
#include "../common/windows/fmsgs.h"
#include "../common/windows/floader.h"
#include "..\common\ide\ide.cpp"
#include "cqmsecurity.h"

USEFORM("..\common\server\fmain.cpp", MainF);
USEFORM("..\common\windows\fdm.cpp", DM); /* TDataModule: File Type */
USEFORM("..\common\windows\fsignals.cpp", SignalsF);
USEFORM("..\common\windows\fmsgs.cpp", MsgsF);
USEFORM("..\common\windows\ftableviewer.cpp", TableViewer);
USEFORM("..\common\windows\fenterdata.cpp", EnterDataF);
USEFORM("..\common\windows\fdatetimeselect.cpp", DateTimeSelect);
USEFORM("..\common\windows\faboutsrv.cpp", AboutF);
USEFORM("..\common\windows\fpromku.cpp", ProMKUF);
USEFORM("..\common\windows\fpswd.cpp", PasswordDlg);
USEFORM("..\common\windows\floader.cpp", LoaderF);
USEFORM("..\common\windows\fcteditor.cpp", CteF);
USEFORM("..\common\windows\fclock.cpp", ClockF);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    if (RegisterApplication(RunningNowSemaphore))
    {
         ShowMessage("��� ������ ��� ��������!");
         return 1;
    }

    if (!CheckDecimalSeparator())
    {
        ShowMessage("�������� ����������� ����� � ������� ������.\n����� ����� '.'");
        return 7;
    }

    if (!CheckIniFile())
    {
        ShowMessage(AnsiString("�� ������ ���� ������������ ")+AppIniFileName+"\n������ ����������.");
        return 8;
    }

    //������� ���������� ���, ��� exe
    SetCurrentDir(ExtractFileDir(Application->ExeName));

#ifdef HIGH_SECURITY
    if (!CheckServerSecurity())
    {
        return 3;
    }
#else
    if (!CheckCId ())
    {
        ShowMessage("�������� ����! ������ ����������.");
        return 2;
    }
#endif

    Application->Initialize();
	Application->Title = "��� ������";

    try
    {
        CreateProgressForm(12, "��� ������");
        StepProgressForm("�������� ����������� ����...");

        Application->CreateForm(__classid(TMainF), &MainF);
         Application->CreateForm(__classid(TDM), &DM);
         Application->CreateForm(__classid(TSignalsF), &SignalsF);
         Application->CreateForm(__classid(TMsgsF), &MsgsF);
         Application->CreateForm(__classid(TTableViewer), &TableViewer);
         Application->CreateForm(__classid(TClockF), &ClockF);
         int ret = StartActions();
        if (ret)
        {
           StopActions();
           return ret;
        }

    }
    __finally
    {
        KillProgressForm();
    }

	try
	{
        Application->Run();
	}
	catch (Exception &exception)
	{
        Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------





