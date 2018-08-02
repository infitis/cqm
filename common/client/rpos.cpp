//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

//----------------------------------------------------------------------------
#include "rpos.h"
#include "global.h"
#include "globcli.h"
#include "fselectpointdate.h"
#include "frepreview.h"

//----------------------------------------------------------------------------
#pragma link "ZAbstractRODataset"
#pragma link "ZDataset"
#pragma resource "*.dfm"

//----------------------------------------------------------------------------
TRepPos *RepPos = NULL;

//----------------------------------------------------------------------------
void MakeRepPos(void)
{
    //выберем дату
    TDate da;
    if (!SelectDate(da))
    {
        return;
    }

    RepPos = new TRepPos(Application);
    try
    {
        RepPos->QRLTitle->Caption =
        "Суточный отчёт о зольности угля по позициям за " + DateToStr(da);
        RepPos->QRLMKU->Caption = Title + ". Комплекс МКУ";

        RepPos->q->SQL->Text = AnsiString().sprintf(
        "select * from rep_day_pos('%s')"
        , FormatDateTimeToDB(da, 1).c_str());
        if (!RepPosWRHVis)
        {
            RepPos->QRLabel1->Enabled = false;
            RepPos->QRLabel8->Enabled = false;
            RepPos->QRLabel9->Enabled = false;
            RepPos->QRLabel10->Enabled = false;
            RepPos->QRLabel13->Enabled = false;
            RepPos->QRDBText5->Enabled = false;
            RepPos->QRDBText6->Enabled = false;
            RepPos->QRDBText8->Enabled = false;
        }
        RepPos->q->Open();
        ReportPreview(RepPos);
        RepPos->q->Close();
    }
    __finally
    {
        delete RepPos;
    }
}

//----------------------------------------------------------------------------
void MakeRepPosMonth(void)
{
    //выберем дату
    TDate da;
    if (!SelectDate(da))
    {
        return;
    }

    RepPos = new TRepPos(Application);
    try
    {
        RepPos->QRLTitle->Caption =
        "Mecячный отчёт о зольности угля по позициям за " + DateToStr(da);
        RepPos->QRLMKU->Caption = Title + ". Комплекс МКУ";

        RepPos->q->SQL->Text = AnsiString().sprintf(
        "select * from rep_month_pos('%s')"
        , FormatDateTimeToDB(da, 1).c_str());
        if (!RepPosWRHVis)
        {
            RepPos->QRLabel1->Enabled = false;
            RepPos->QRLabel8->Enabled = false;
            RepPos->QRLabel9->Enabled = false;
            RepPos->QRLabel10->Enabled = false;
            RepPos->QRLabel13->Enabled = false;
            RepPos->QRDBText5->Enabled = false;
            RepPos->QRDBText6->Enabled = false;
            RepPos->QRDBText8->Enabled = false;
        }
        RepPos->q->Open();
        ReportPreview(RepPos);
        RepPos->q->Close();
    }
    __finally
    {
        delete RepPos;
    }
}

//----------------------------------------------------------------------------
__fastcall TRepPos::TRepPos(TComponent* Owner)
    : TQuickRep(Owner)
{
}

//----------------------------------------------------------------------------
void __fastcall TRepPos::QRDBText4Print(TObject *sender, AnsiString &Value)
{
    try {
        float v = StrToFloat(Value);
        Value = AnsiString().sprintf("%.1f",v);
    } catch(...){}
}

//---------------------------------------------------------------------------

void __fastcall TRepPos::QRDBText6Print(TObject *sender, AnsiString &Value)
{
    try {
        float v = StrToFloat(Value);
        Value = AnsiString().sprintf("%.3f",v);
    } catch(...){}
}
//---------------------------------------------------------------------------

