//---------------------------------------------------------------------------
#include <vcl.h>
#include <math.hpp>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "fselectpointdate.h"
#include "clientdata.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
TSelectPointDateF *SelectPointDateF = NULL;

//---------------------------------------------------------------------------
__fastcall TSelectPointDateF::TSelectPointDateF(TComponent* Owner)
    : TForm(Owner)
{
}

//---------------------------------------------------------------------------
bool SelectClientDate(AnsiString title, clidata* data, int count, int& cliindex, TDate& d)
{
    bool ok = false;
    SelectPointDateF = new TSelectPointDateF(Application);

    try
    {
        SelectPointDateF->CB->Clear();
        for (int i=0; i<count; i++)
        {
            SelectPointDateF->CB->Items->Append(data[i].title);
        }
        SelectPointDateF->CB->ItemIndex = 0;

        SelectPointDateF->GBDateTime->Visible = false;
        SelectPointDateF->GBDate->Visible = true;
        SelectPointDateF->DateP->DateTime = Date();
        SelectPointDateF->Caption = "Выбор: дата и "+title;
        if (SelectPointDateF->ShowModal() == mrOk)
        {
            cliindex = SelectPointDateF->CB->ItemIndex;
            d = Floor(SelectPointDateF->DateP->Date);
            ok = true;
        }
    }
    __finally
    {
        delete SelectPointDateF;
    }

    return ok;
}

//---------------------------------------------------------------------------
bool SelectClientDateTimeInterval
                     (AnsiString title, clidata* data, int count, int& cliindex, TDateTime& dt1, TDateTime& dt2)
{
    bool ok = false;
    SelectPointDateF = new TSelectPointDateF(Application);

    try
    {
        SelectPointDateF->CB->Clear();
        for (int i=0; i<count; i++)
        {
            SelectPointDateF->CB->Items->Append(data[i].title);
        }
        SelectPointDateF->CB->ItemIndex = 0;

        SelectPointDateF->GBDateTime->Visible = true;
        SelectPointDateF->GBDate->Visible = false;
        SelectPointDateF->DateP1->DateTime = Date();
        SelectPointDateF->DateP2->DateTime = Date();
        SelectPointDateF->TimeP1->DateTime = Time();
        SelectPointDateF->TimeP2->DateTime = Time();
        SelectPointDateF->Caption = "Выбор: промежуток времени и "+title;

        if (SelectPointDateF->ShowModal() == mrOk)
        {
            cliindex = SelectPointDateF->CB->ItemIndex;
            dt1 = SelectPointDateF->TimeP1->Time - Floor(SelectPointDateF->TimeP1->Time) + Floor(SelectPointDateF->DateP1->Date);
            dt2 = SelectPointDateF->TimeP2->Time - Floor(SelectPointDateF->TimeP2->Time) + Floor(SelectPointDateF->DateP2->Date);
            ok = true;
        }
    }
    __finally
    {
        delete SelectPointDateF;
    }

    return ok;
}

//---------------------------------------------------------------------------
bool SelectDate(TDate& d)
{
    bool ok = false;
    SelectPointDateF = new TSelectPointDateF(Application);

    try
    {
        SelectPointDateF->Caption = "Выбор даты";
        SelectPointDateF->CB->Visible = false;
        SelectPointDateF->L1->Visible = false;

        SelectPointDateF->GBDateTime->Visible = false;
        SelectPointDateF->GBDate->Visible = true;
        SelectPointDateF->DateP->DateTime = Date();

        if (SelectPointDateF->ShowModal() == mrOk)
        {
            d = Floor(SelectPointDateF->DateP->Date);
            ok = true;
        }
    }
    __finally
    {
        delete SelectPointDateF;
    }

    return ok;
}

/*
//---------------------------------------------------------------------------
bool SelectPointDate(int* pointindex, TDate* d)
{
    bool ok = false;
    SelectPointDateF = new TSelectPointDateF(Application);

    try
    {
        SelectPointDateF->CB->Clear();
        for (int i=0; i<clipointCount; i++)
        {
            SelectPointDateF->CB->Items->Append(clipoints[i].title);
        }
        SelectPointDateF->CB->ItemIndex = 0;

        SelectPointDateF->GBDateTime->Visible = false;
        SelectPointDateF->GBDate->Visible = true;
        SelectPointDateF->DateP->DateTime = Date();

        if (SelectPointDateF->ShowModal() == mrOk)
        {
            *pointindex = SelectPointDateF->CB->ItemIndex;
            *d = Floor(SelectPointDateF->DateP->Date);
            ok = true;
        }
    }
    __finally
    {
        delete SelectPointDateF;
    }

    return ok;
}

//---------------------------------------------------------------------------
bool SelectPointDateTimeInterval(int* pointindex, TDateTime* dt1, TDateTime* dt2)
{
    bool ok = false;
    SelectPointDateF = new TSelectPointDateF(Application);

    try
    {
        SelectPointDateF->CB->Clear();
        for (int i=0; i<clipointCount; i++)
        {
            SelectPointDateF->CB->Items->Append(clipoints[i].title);
        }
        SelectPointDateF->CB->ItemIndex = 0;

        SelectPointDateF->GBDateTime->Visible = true;
        SelectPointDateF->GBDate->Visible = false;
        SelectPointDateF->DateP1->DateTime = Date();
        SelectPointDateF->DateP2->DateTime = Date();
        SelectPointDateF->TimeP1->DateTime = Time();
        SelectPointDateF->TimeP2->DateTime = Time();

        if (SelectPointDateF->ShowModal() == mrOk)
        {
            *pointindex = SelectPointDateF->CB->ItemIndex;
            *dt1 = SelectPointDateF->TimeP1->Time - Floor(SelectPointDateF->TimeP1->Time) + Floor(SelectPointDateF->DateP1->Date);
            *dt2 = SelectPointDateF->TimeP2->Time - Floor(SelectPointDateF->TimeP2->Time) + Floor(SelectPointDateF->DateP2->Date);
            ok = true;
        }
    }
    __finally
    {
        delete SelectPointDateF;
    }

    return ok;
}
*/
//---------------------------------------------------------------------------

