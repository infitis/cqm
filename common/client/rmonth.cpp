//---------------------------------------------------------------------------
#include <dateutils.hpp>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "rmonth.h"
#include "global.h"
#include "rhours.h"
#include "fselectpointdate.h"
#include "clientdata.h"
#include "..\classes\coalheap.h"
#include "globcli.h"
#include "frepreview.h"
#include <fmsgs.h>

//---------------------------------------------------------------------------
TRepHours *RepMonth = NULL;

//---------------------------------------------------------------------------
void MakeRepPointsMonth()
{
    int pid;
    TDate da;

    if (!SelectClientDate("точка контроля", clipoints, clipointCount, pid, da))
    {
        return;
    }

    RepMonth= new TRepHours(Application);
    try
    {
        RepMonth->QRLTitle->Caption =
        AnsiString("Точка контроля: ") + clipoints[pid].title +
        ", дата: " + DateToStr(da);
        RepMonth->QRLMKU->Caption = Title + ". Комплекс МКУ";
        RepMonth->QRLabel1->Caption = "Дата";
        RepMonth->QRLMainTitle->Caption = "Месячный отчёт о качестве угля.";

        RepMonth->q->SQL->Text =
            AnsiString().sprintf(
            "select * from REP_MONTH_POINT('%s', '%s', %d) order by id"
            ,clipoints[pid].name, FormatDateTimeToDB(da, 1).c_str(),
             DayRepStartHour)
        ;
        RepMonth->q->Open();
        ReportPreview(RepMonth);
        RepMonth->q->Close();
    }
    __finally
    {
        delete RepMonth;
    }
}

//---------------------------------------------------------------------------
void MakeRepRoutesMonth()
{
    int pid;
    TDate da;

    if (!SelectClientDate("маршруты", cliroutes, clirouteCount, pid, da))
    {
        return;
    }

    RepMonth = new TRepHours(Application);
    try
    {
        RepMonth->QRLTitle->Caption =
        AnsiString("Маршрут движения угля: ") + cliroutes[pid].title +
        ", дата: " + DateToStr(da);
        RepMonth->QRLMKU->Caption = Title + ". Комплекс МКУ";
        RepMonth->QRLabel1->Caption = "Дата";
        RepMonth->QRLMainTitle->Caption = "Месячный отчёт о качестве угля.";

        RepMonth->q->SQL->Text =
            AnsiString().sprintf(
            "select * from REP_MONTH_ROUTE('%s', '%s', %d) order by id"
            ,cliroutes[pid].name, FormatDateTimeToDB(da, 1).c_str(),
             DayRepStartHour)
        ;
        RepMonth->q->Open();
        ReportPreview(RepMonth);
        RepMonth->q->Close();
    }
    __finally
    {
        delete RepMonth;
    }
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
