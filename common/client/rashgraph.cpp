//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

//----------------------------------------------------------------------------
#include "rashgraph.h"
#include "fselectpointdate.h"
#include "clientdata.h"
#include "..\classes\coalheap.h"
#include "global.h"
#include "frepreview.h"

//----------------------------------------------------------------------------
#pragma link "ZAbstractRODataset"
#pragma link "ZDataset"
#pragma resource "*.dfm"

//----------------------------------------------------------------------------
TRepAshGraph *RepAshGraph = NULL;

//----------------------------------------------------------------------------
__fastcall TRepAshGraph::TRepAshGraph(TComponent* Owner)
    : TQuickRep(Owner)
{
    QRChart->Chart->BottomAxis->DateTimeFormat = "dd.mm.yy hh:nn";
    QRChart->Chart->BottomAxis->Title->Caption = "дата, время";
}

//----------------------------------------------------------------------------
void MakeAshGraph(void)
{
    int pointindex;
    TDateTime dt1;
    TDateTime dt2;
    int smooth;

    if (!SelectClientDateTimeInterval("точка контроля", clipoints, clipointCount, pointindex, dt1, dt2))
    {
        return;
    }

    AnsiString sqlwhat;
    if (MessageBox(Application->MainForm->Handle,
                   "Сглаживать значения на графике?",
                   "График зольности",
                   MB_YESNO+MB_ICONQUESTION	) == IDYES)
    {
        smooth = 6;
    }
    else
    {
        smooth = 1;
    }

    RepAshGraph = new TRepAshGraph(Application);
    try
    {
        RepAshGraph->QRLTitle->Caption =
        "График зольности угля. " + AnsiString(clipoints[pointindex].title) +
        ", От: " + DateTimeToStr(dt1) + " до: " + DateTimeToStr(dt2);
        RepAshGraph->QRLMKU->Caption = Title + ". Комплекс МКУ";

        RepAshGraph->q->SQL->Text = AnsiString("select moment, a from rep_ash_point_graph('")
                                  + clipoints[pointindex].name
                                  +"', '" + FormatDateTimeToDB(dt1)
                                  +"', '" + FormatDateTimeToDB(dt2)
                                  +"', "  + IntToStr(smooth) + ")";
        if (clipoints[pointindex].id >= 0)
        {
        RepAshGraph->qvag->SQL->Text = AnsiString("select moment, a from rep_ash_vagon_graph('")
                                  + clivagons[clipoints[pointindex].id].name
                                  +"', '" + FormatDateTimeToDB(dt1)
                                  +"', '" + FormatDateTimeToDB(dt2) + "')";
        RepAshGraph->qvag->Open();
        }
        RepAshGraph->q->Open();
        RepAshGraph->QRChart->Chart->BottomAxis->Automatic = false ;
        RepAshGraph->QRChart->Chart->BottomAxis->Maximum = dt2;
        RepAshGraph->QRChart->Chart->BottomAxis->Minimum = dt1;
        ReportPreview(RepAshGraph);
        RepAshGraph->q->Close();
        if (clipoints[pointindex].id > 0)
        {
        RepAshGraph->qvag->Close();
        }
    }
    __finally
    {
        delete RepAshGraph;
    }
}

//----------------------------------------------------------------------------
void MakeRouteGraph(void)
{
    int routeindex;
    TDateTime dt1;
    TDateTime dt2;
    int smooth;

    if (!SelectClientDateTimeInterval("маршрут", cliroutes, clirouteCount, routeindex, dt1, dt2))
    {
        return;
    }

    AnsiString sqlwhat;
    if (MessageBox(Application->MainForm->Handle,
                   "Сглаживать значения на графике?",
                   "График зольности",
                   MB_YESNO+MB_ICONQUESTION	) == IDYES)
    {
        smooth = 6;
    }
    else
    {
        smooth = 1;
    }

    RepAshGraph = new TRepAshGraph(Application);
    try
    {
        RepAshGraph->QRLTitle->Caption =
        "График зольности угля. Маршрут " + AnsiString(cliroutes[routeindex].title) +
        ", От: " + DateTimeToStr(dt1) + " до: " + DateTimeToStr(dt2);
        RepAshGraph->QRLMKU->Caption = Title + ". Комплекс МКУ";


        RepAshGraph->q->SQL->Text = AnsiString("select moment, a from rep_ash_route_graph('")
                                  + cliroutes[routeindex].name
                                  +"', '" + FormatDateTimeToDB(dt1)
                                  +"', '" + FormatDateTimeToDB(dt2)
                                  +"', "  + IntToStr(smooth) + ")";

        RepAshGraph->qvag->Close();
        RepAshGraph->q->Open();
        RepAshGraph->QRChart->Chart->BottomAxis->Automatic = false ;
        RepAshGraph->QRChart->Chart->BottomAxis->Maximum = dt2;
        RepAshGraph->QRChart->Chart->BottomAxis->Minimum = dt1;
        ReportPreview(RepAshGraph);
        RepAshGraph->q->Close();
    }
    __finally
    {
        delete RepAshGraph;
    }
}

//----------------------------------------------------------------------------

