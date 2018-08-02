//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "stuffic.h"
#include "faboutic.h"
#include "global.h"
#include "globcli.h"

//---------------------------------------------------------------------------
USEFORM("..\src\fmainic.cpp", MainICF);
USEFORM("..\..\common\windows\fmsgs.cpp", MsgsF);
USEFORM("..\..\common\windows\fdm.cpp", DM); /* TDataModule: File Type */
USEFORM("..\..\common\client\fcustomashgraph.cpp", CustomAshGraphF);
USEFORM("..\..\common\client\rvagons.cpp", RepVagons); /* TQuickRep: File Type */
USEFORM("..\..\common\client\frepreview.cpp", RepPreviewF);
USEFORM("..\..\common\client\fselectpointdate.cpp", SelectPointDateF);
USEFORM("..\..\common\client\rashgraph.cpp", RepAshGraph); /* TQuickRep: File Type */
USEFORM("..\..\common\client\rcert.cpp", RepCert); /* TQuickRep: File Type */
USEFORM("..\..\common\client\rhours.cpp", RepHours); /* TQuickRep: File Type */
USEFORM("..\..\common\client\rintervals.cpp", RepIntervals); /* TQuickRep: File Type */
USEFORM("..\..\common\client\rmin.cpp", RepMin); /* TQuickRep: File Type */
USEFORM("..\..\common\client\rpos.cpp", RepPos); /* TQuickRep: File Type */
USEFORM("..\..\common\client\fcustomminutes.cpp", MinutesF);
USEFORM("..\src\faboutic.cpp", AboutICF);
USEFORM("..\src\fobjsel.cpp", ObjSelF);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    if (RegisterApplication(RunningNowICSemaphore))
    {
         ShowMessage("МКУ Инфоцентр уже работает!");
         return 1;
    }

    //Установка текущей директории с exe - файлом
    SetCurrentDir(ExtractFileDir(Application->ExeName));

    LogDir  = "..\\logs";
    LogName = "ic";


    try
    {
        try
        {
            SplashFormShow();
            Application->Initialize();
            Application->CreateForm(__classid(TMainICF), &MainICF);
         Application->CreateForm(__classid(TMsgsF), &MsgsF);
         Application->CreateForm(__classid(TDM), &DM);
         Application->CreateForm(__classid(TMinutesF), &MinutesF);
         Application->CreateForm(__classid(TObjSelF), &ObjSelF);
         int ret = Start();
            if (ret)
            {
               Stop();
               return ret;
            }
            Sleep(1500);
        }
        __finally
        {
            SplashFormClose();
        }

        Application->Run();

    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    catch (...)
    {
         try
         {
             throw Exception("");
         }
         catch (Exception &exception)
         {
             Application->ShowException(&exception);
         }
    }
    return 0;
}
//---------------------------------------------------------------------------
