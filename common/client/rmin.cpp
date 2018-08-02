//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

//----------------------------------------------------------------------------
#include "global.h"
#include "rmin.h"
#include "fselectpointdate.h"
#include "clientdata.h"
#include "frepreview.h"

//----------------------------------------------------------------------------
#pragma link "ZAbstractRODataset"
#pragma link "ZDataset"
#pragma resource "*.dfm"

//----------------------------------------------------------------------------
TRepMin *RepMin = NULL;

//----------------------------------------------------------------------------
void MakeRepMin(void)
{
    int pointindex;
    TDateTime dt1;
    TDateTime dt2;

    if (!SelectClientDateTimeInterval("точка контроля", clipoints, clipointCount, pointindex, dt1, dt2))
    {
        return;
    }


    RepMin = new TRepMin(Application);
    try
    {
        RepMin->QRLTitle2->Caption =
        AnsiString(clipoints[pointindex].title) +
        ", От: " + DateTimeToStr(dt1) + " до: " + DateTimeToStr(dt2);
        RepMin->QRLMKU->Caption = Title + ". Комплекс МКУ";

        RepMin->q->SQL->Text = AnsiString("select moment,p,a,diag from points where point='")
                                  + clipoints[pointindex].name
                                  +"' and moment>='" + FormatDateTimeToDB(dt1)
                                  +"' and moment<='" + FormatDateTimeToDB(dt2)
                                  +"' order by moment";
        RepMin->q->Open();
        ReportPreview(RepMin);
        RepMin->q->Close();
    }
    __finally
    {
        delete RepMin;
    }
}

//----------------------------------------------------------------------------
__fastcall TRepMin::TRepMin(TComponent* Owner)
    : TQuickRep(Owner)
{
}

//----------------------------------------------------------------------------