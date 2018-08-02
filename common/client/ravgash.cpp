//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ravgash.h"

#include "global.h"
#include "fselectpointdate.h"
#include "clientdata.h"
#include "..\classes\coalheap.h"
#include "globcli.h"
#include "frepreview.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ZAbstractDataset"
#pragma link "ZAbstractRODataset"
#pragma link "ZDataset"
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
__fastcall TAvgAshF::TAvgAshF(TComponent* Owner)
   : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void MakeAvgAshReport()
{
    int pointindex;
    TDateTime dt1;
    TDateTime dt2;
    double p, a;//вес и зола из запроса
    CoalHeap cH;//куча для итого
    TAvgAshF *RAvgAsh;

    if (!SelectClientDateTimeInterval("маршрут", cliroutes, clirouteCount, pointindex, dt1, dt2))
    {
        return;
    }

    AnsiString s;

    RAvgAsh = new TAvgAshF(Application);
    try
    {
        s   =  AnsiString("select moment, a, p")
                        + " from routes where route='"
                        + cliroutes[pointindex].name
                        + "' and moment> '" + FormatDateTimeToDB(dt1)
                        + "' and moment<='" + FormatDateTimeToDB(dt2)
                        + "' ";
        OpenSql(s);
        //и всавляем кучу
        while (!MEOF)
        {
            p = GETFIELD("p")->AsFloat;
            a = GETFIELD("a")->AsFloat;
            cH.addCoal(Coal(p, a));
            MNEXT;
        }

        //из кучи в форму
        RAvgAsh->LPlace->Caption = cliroutes[pointindex].title;
        RAvgAsh->LTime->Caption  = FormatDateTime("yyyy-mm-dd hh:nn:ss", dt1)
                                 + " - "
                                 + FormatDateTime("yyyy-mm-dd hh:nn:ss", dt2);

        RAvgAsh->LP->Caption = cH.c.P.format("%3.1f");
        RAvgAsh->LA->Caption = cH.c.A.format("%3.1f");
        RAvgAsh->ShowModal();
    }
    __finally
    {
        delete RAvgAsh;
    }
}

