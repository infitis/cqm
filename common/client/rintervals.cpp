//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

//----------------------------------------------------------------------------
#include "rintervals.h"
#include "global.h"
#include "globcli.h"
#include "fselectpointdate.h"
#include "frepreview.h"
#include "clientdata.h"
#include "coalheap.h"

//----------------------------------------------------------------------------
#pragma link "ZAbstractRODataset"
#pragma link "ZDataset"
#pragma resource "*.dfm"

//----------------------------------------------------------------------------
TRepIntervals *RepIntervals = NULL;

//----------------------------------------------------------------------------
void MakeRepIntervalsRoutes(void)
{
    int pid;
    TDate da;

    if (!SelectClientDate("маршруты", cliroutes, clirouteCount, pid, da))
    {
        return;
    }

    RepIntervals = new TRepIntervals(Application);
    try
    {
        RepIntervals->QRLTitle->Caption =
        AnsiString("Маршрут движения угля: ") + cliroutes[pid].title +
        ", дата: " + DateToStr(da);
        RepIntervals->QRLMKU->Caption = Title + ". Комплекс МКУ";

        RepIntervals->q->SQL->Text = AnsiString().sprintf(
            "select * from rep_interval_route('%s', '%s', %d, %d) order by id"
            ,cliroutes[pid].name, FormatDateTimeToDB(da, 1).c_str(),
             RepIntervalsStartHour, RepIntervalsWorkingShift)
        ;
        RepIntervals->q->Open();
        ReportPreview(RepIntervals);
        RepIntervals->q->Close();
    }
    __finally
    {
        delete RepIntervals;
    }
}

//----------------------------------------------------------------------------
__fastcall TRepIntervals::TRepIntervals(TComponent* Owner)
    : TQuickRep(Owner)
{
}

//----------------------------------------------------------------------------

void __fastcall TRepIntervals::QRDBText2Print(TObject *sender,
      AnsiString &Value)
{
    try {
        float v = StrToFloat(Value);
        Value = AnsiString().sprintf("%.1f",v);
    } catch(...){}
}
//---------------------------------------------------------------------------

void __fastcall TRepIntervals::QRDBText3Print(TObject *sender,
      AnsiString &Value)
{
    try {
        float v = StrToFloat(Value);
        Value = AnsiString().sprintf("%.1f",v);
    } catch(...){}
}
//---------------------------------------------------------------------------

