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
         ShowMessage("МКУ Сервер уже работает!");
         return 1;
    }

    if (!CheckDecimalSeparator())
    {
        ShowMessage("Неверный разделитель целой и дробной частей.\nНужна точка '.'");
        return 7;
    }

    if (!CheckIniFile())
    {
        ShowMessage(AnsiString("Не найден файл конфигурации ")+AppIniFileName+"\nРабота невозможна.");
        return 8;
    }

    //Текущая директория там, где exe
    SetCurrentDir(ExtractFileDir(Application->ExeName));

#ifdef HIGH_SECURITY
    if (!CheckServerSecurity())
    {
        return 3;
    }
#else
    if (!CheckCId ())
    {
        ShowMessage("Неверный ключ! Работа невозможна.");
        return 2;
    }
#endif

    Application->Initialize();
	Application->Title = "МКУ Сервер";

    try
    {
        CreateProgressForm(12, "МКУ Сервер");
        StepProgressForm("Создание статических форм...");

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





