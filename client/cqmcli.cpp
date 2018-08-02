//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "stuff.h"
#include "..\common\windows\fmsgs.h"
#include "..\common\windows\global.h"
#include "..\common\windows\floader.h"

//---------------------------------------------------------------------------
USEFORM("..\common\client\fmain.cpp", MainF);
USEFORM("..\common\client\fcustomashgraph.cpp", CustomAshGraphF);
USEFORM("..\common\windows\fdm.cpp", DM); /* TDataModule: File Type */
USEFORM("..\common\windows\fmsgs.cpp", MsgsF);
USEFORM("..\common\windows\fclock.cpp", ClockF);
USEFORM("..\common\client\fcustomminutes.cpp", MinutesF);
USEFORM("..\common\windows\fpromku.cpp", ProMKUF);
USEFORM("..\common\client\fselectpointdate.cpp", SelectPointDateF);
USEFORM("..\common\client\rhours.cpp", RepHours); /* TQuickRep: File Type */
USEFORM("..\common\client\rashgraph.cpp", RepAshGraph); /* TQuickRep: File Type */
USEFORM("..\common\client\fcustomvagonsviewer.cpp", CustomVagonsViewerF);
USEFORM("..\common\client\fcustomvagonseditor.cpp", CustomVagonsEditorF);
USEFORM("..\common\client\rvagons.cpp", RepVagons); /* TQuickRep: File Type */
USEFORM("..\common\client\rpos.cpp", RepPos); /* TQuickRep: File Type */
USEFORM("..\common\client\rmin.cpp", RepMin); /* TQuickRep: File Type */
USEFORM("..\common\client\findic.cpp", IndicatorF);
USEFORM("..\common\client\fpositseditor.cpp", PositsEditorF);
USEFORM("..\common\client\rcert.cpp", RepCert); /* TQuickRep: File Type */
USEFORM("..\common\client\foperhelp.cpp", OperHelpF);
USEFORM("..\common\windows\floader.cpp", LoaderF);
USEFORM("..\common\windows\fenterdata.cpp", EnterDataF);
USEFORM("..\common\client\froutes.cpp", RoutesF);
USEFORM("..\common\client\faccums.cpp", AccumsF);
USEFORM("..\common\client\fvagonbatch.cpp", VagonBatchF);
USEFORM("..\common\client\frepreview.cpp", RepPreviewF);
USEFORM("..\common\client\falarm.cpp", AlarmF);
USEFORM("..\common\client\rintervals.cpp", RepIntervals); /* TQuickRep: File Type */
USEFORM("..\common\client\ravgash.cpp", AvgAshF);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    if (RegisterApplication(RunningNowClientSemaphore))
    {
         ShowMessage("МКУ Клиент уже работает!");
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

    try
    {
        Application->Initialize();
        Application->Title = "МКУ Клиент";

        try{CreateProgressForm(8, "МКУ Клиент");
        StepProgressForm("Создание статических форм...");

        Application->CreateForm(__classid(TMainF), &MainF);
       Application->CreateForm(__classid(TDM), &DM);
       Application->CreateForm(__classid(TMsgsF), &MsgsF);
       Application->CreateForm(__classid(TClockF), &ClockF);
       Application->CreateForm(__classid(TMinutesF), &MinutesF);
       Application->CreateForm(__classid(TIndicatorF), &IndicatorF);
       Application->CreateForm(__classid(TPositsEditorF), &PositsEditorF);
       int ret = StartActions();
        if (ret)
            return ret;

        } __finally { KillProgressForm();}
    
        Application->Run();

    }
    catch (Exception &exception)
    {
        /* TODO : Добавлять сообщение об исключении в журан и лог */
        try{
        DoMsg(exception.Message);
        } catch(...){}
         Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------

