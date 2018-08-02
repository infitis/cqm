//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "fcustomminutes.h"
#include "..\classes\cqmdiag.h"
#include "clientdata.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ZAbstractRODataset"
#pragma link "ZDataset"
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
TMinutesF *MinutesF;

//---------------------------------------------------------------------------
__fastcall TMinutesF::TMinutesF(TComponent* Owner)
    : TForm(Owner)
{
    point = "''";
    sqlwhere =
    " and addhour(moment, 1) >= current_timestamp";
    //" and cast(current_timestamp - moment as decimal(17,4)) <= 0.0417";
}

//---------------------------------------------------------------------------
void __fastcall TMinutesF::Init(void)
{
    if (!q->Connection->Connected)
        return;
    CB->Clear();
    for (int i=0; i<clipointCount; i++)
    {
        CB->Items->Append(clipoints[i].title);
    }
    CB->ItemIndex = 0;

    Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TMinutesF::Refresh(void)
{
    if (CB->ItemIndex>=0 && CB->ItemIndex<clipointCount)
    {
        point = clipoints[CB->ItemIndex].name;
    }
    else
    {
        point = clipoints[0].name;
    }

    q->DisableControls();
    q->Close();
    q->SQL->Text = "select moment, p, a, diag from points where point='"
                 + point + "' "+ sqlwhere + " order by moment";
    q->Open();
    q->Last();
    q->EnableControls();

    ShowStatus();
}

//---------------------------------------------------------------------------
void __fastcall TMinutesF::N1hourClick(TObject *Sender)
{
    sqlwhere =
    " and addhour(moment, 1) >= current_timestamp";
    //" and cast(current_timestamp - moment as decimal(17,4)) <= 0.0417";
    N1hour->Checked = true;
    Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TMinutesF::N6hoursClick(TObject *Sender)
{
    sqlwhere =
    " and addhour(moment, 6) >= current_timestamp";
    //" and cast(current_timestamp - moment as decimal(17,4)) <= 0.25";
    N6hours->Checked = true;
    Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TMinutesF::N1dayClick(TObject *Sender)
{
    sqlwhere =
    " and addhour(moment, 24) >= current_timestamp";
    //" and cast(current_timestamp - moment as decimal(17,4)) <= 1.0000";
    N1day->Checked = true;
    Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TMinutesF::N3dayClick(TObject *Sender)
{
    sqlwhere =
    " and addday(moment, 3) >= current_timestamp";
    //" and cast(current_timestamp - moment as decimal(17,4)) <= 3.0000";
    N3day->Checked = true;
    Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TMinutesF::ShowStatus(void)
{
    char diag[255] = "";
    diag2str(diag, q->FieldByName("diag")->AsInteger);
    StatusBar->SimpleText = "Записей отображено: "
                          + IntToStr(q->RecordCount)
                          + ";    Диагностика: "
                          + AnsiString(diag);
}

//---------------------------------------------------------------------------
void __fastcall TMinutesF::qAfterScroll(TDataSet *DataSet)
{
    ShowStatus();
}

//---------------------------------------------------------------------------
void __fastcall TMinutesF::CBChange(TObject *Sender)
{
    Refresh();    
}

//---------------------------------------------------------------------------

