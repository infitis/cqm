//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

//----------------------------------------------------------------------------
#include "global.h"
#include "rvagons.h"
#include "fselectpointdate.h"
#include "frepreview.h"

//----------------------------------------------------------------------------
#pragma link "ZAbstractRODataset"
#pragma link "ZDataset"
#pragma resource "*.dfm"

//----------------------------------------------------------------------------
TRepVagons *RepVagons = NULL;

//----------------------------------------------------------------------------
void MakeRepVagons(void)
{
    TDate da;
    if (!SelectDate(da))
    {
        return;
    }

    RepVagons = new TRepVagons(Application);
    try
    {
        RepVagons->QRLTitle->Caption =
        "Отчёт о зольности угля в вагонах за " + DateToStr(da);
        RepVagons->QRLMKU->Caption = Title + ". Комплекс МКУ";
        RepVagons->QRDBText1->DataField = "coalrankname";
        RepVagons->q->SQL->Text = AnsiString("") +
              "select vagons.*, coalranks.name as coalrankname from vagons left join coalranks on vagons.coalrank = coalranks.id where rwdate='"
            + FormatDateTimeToDB(da, 1) +"' "
            + "and pos is not null and cert is not null and wei is not null and a is not null order by moment";
        RepVagons->q->Open();
        ReportPreview(RepVagons);
        RepVagons->q->Close();
    }
    __finally
    {
        delete RepVagons;
    }
}

//----------------------------------------------------------------------------
__fastcall TRepVagons::TRepVagons(TComponent* Owner)
    : TQuickRep(Owner)
{
}


//----------------------------------------------------------------------------
void __fastcall TRepVagons::QRDBText2Print(TObject *sender,
      AnsiString &Value)
{
    try {
        float v = StrToFloat(Value);
        Value = AnsiString().sprintf("%.1f",v);
    } catch(...){}
}

//---------------------------------------------------------------------------


