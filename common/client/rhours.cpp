//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

//----------------------------------------------------------------------------
#include "global.h"
#include "rhours.h"
#include "fselectpointdate.h"
#include "clientdata.h"
#include "..\classes\coalheap.h"
#include "globcli.h"
#include "frepreview.h"

//----------------------------------------------------------------------------
#pragma link "ZAbstractRODataset"
#pragma link "ZDataset"
#pragma resource "*.dfm"

//----------------------------------------------------------------------------
TRepHours *RepHours = NULL;

//----------------------------------------------------------------------------
void MakeRepDayPoints(void)
{
    int pid;
    TDate da;

    if (!SelectClientDate("точка контроля", clipoints, clipointCount, pid, da))
    {
        return;
    }

    RepHours = new TRepHours(Application);
    try
    {
        RepHours->QRLTitle->Caption =
            AnsiString("Точка контроля: ") + clipoints[pid].title +
            ", дата: " + DateToStr(da);
        RepHours->QRLMKU->Caption = Title + ". Комплекс МКУ";

        RepHours->q->SQL->Text =
        AnsiString().sprintf(
            "select * from REP_DAY_POINT('%s', '%s', %d, %d) order by id"
            ,clipoints[pid].name, FormatDateTimeToDB(da, 1).c_str(),
             DayRepStartHour, WorkingShift)
        ;
        RepHours->q->Open();
        ReportPreview(RepHours);
        RepHours->q->Close();
    }
    __finally
    {
        delete RepHours;
    }
}

//----------------------------------------------------------------------------
void MakeRepDayRoutes(void)
{
    int pid;
    TDate da;

    if (!SelectClientDate("маршруты", cliroutes, clirouteCount, pid, da))
    {
        return;
    }


    RepHours = new TRepHours(Application);
    try
    {
        RepHours->QRLTitle->Caption =
        AnsiString("Маршрут движения угля: ") + cliroutes[pid].title +
        ", дата: " + DateToStr(da);
        RepHours->QRLMKU->Caption = Title + ". Комплекс МКУ";

        RepHours->q->SQL->Text =
        AnsiString().sprintf(
            "select * from REP_DAY_ROUTE('%s', '%s', %d, %d) order by id"
            ,cliroutes[pid].name, FormatDateTimeToDB(da, 1).c_str(),
             DayRepStartHour, WorkingShift)
        ;

        RepHours->q->Open();
        ReportPreview(RepHours);
        RepHours->q->Close();
    }
    __finally
    {
        delete RepHours;
    }
}

//----------------------------------------------------------------------------
__fastcall TRepHours::TRepHours(TComponent* Owner)
    : TQuickRep(Owner)
{
}

//----------------------------------------------------------------------------
void __fastcall TRepHours::QRDBText2Print(TObject *sender,
      AnsiString &Value)
{
    //ВЕС
    try {
        float v = StrToFloat(Value);
        Value = AnsiString().sprintf("%.1f",v);
    } catch(...){}
}
//---------------------------------------------------------------------------

void __fastcall TRepHours::QRDBText3Print(TObject *sender,
      AnsiString &Value)
{
    //ЗОЛА
    try {
        float v = StrToFloat(Value);
        Value = AnsiString().sprintf("%.1f",v);
    } catch(...){}
}
//---------------------------------------------------------------------------

