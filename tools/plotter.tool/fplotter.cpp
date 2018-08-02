//---------------------------------------------------------------------------
#include <vcl.h>
#include <teeprevi.hpp>
#include <math.hpp>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "fplotter.h"
#include "readcsv.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
TPlotF *PlotF;

//---------------------------------------------------------------------------
TDateTime ExtractDateTime(AnsiString s)
{
    TDateTime ret = double(0);
    int year, month, day, hour, min, sec;
    //  yyyy-mm-dd hh:nn:ss
    //  12345678901234567890123
    year  = StrToInt(s.SubString(1,4));
    month = StrToInt(s.SubString(6,2));
    day   = StrToInt(s.SubString(9,2));
    hour  = StrToInt(s.SubString(12,2));
    min   = StrToInt(s.SubString(15,2));
    sec   = StrToInt(s.SubString(18,2));

    ret = EncodeDate(year, month, day) + EncodeTime(hour, min, sec, 0);
    return ret;
}

//---------------------------------------------------------------------------
__fastcall TPlotF::TPlotF(TComponent* Owner)
    : TForm(Owner)
{
    selCol = -1;
    curSer = 0;
    scale = 1.0;
    last_entered_scale = 100;
}

//---------------------------------------------------------------------------
void __fastcall TPlotF::BLoadClick(TObject *Sender)
{
    //
    if (OD->Execute())
    {
        BResetClick(Sender);
        CSV2ListData(OD->FileName, G);
        G->ColWidths[0] = 140;
        for (int i=1; i<G->ColCount; i++)
        {
            G->ColWidths[i] = 43;
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TPlotF::GSelectCell(TObject *Sender, int ACol, int ARow,
      bool &CanSelect)
{
    selCol = ACol;
}

//---------------------------------------------------------------------------
void __fastcall TPlotF::BMakeClick(TObject *Sender)
{
    if (selCol < 1) return;
    if (curSer < C->SeriesList->Count)
    {
        for (int i=1; i<G->RowCount; i++)
        {
            double Y = G->Cells[selCol][i].ToDouble() * scale;
            double X = ExtractDateTime(G->Cells[0][i]);
            C->SeriesList->Series[curSer]->AddXY(X, Y, "", clBlack);
        }
        curSer++;
    }
}

//---------------------------------------------------------------------------
void __fastcall TPlotF::NBuildScaleClick(TObject *Sender)
{
    last_entered_scale = StrToFloat(
        InputBox("Плоттер", "Введите масштабный коэффициент", FloatToStr(last_entered_scale)));
    scale = last_entered_scale;
    BMakeClick(Sender);
    scale = 1.0;
}

//---------------------------------------------------------------------------
void __fastcall TPlotF::NBuildSliceClick(TObject *Sender)
{
    double y1 = 0, y2 = 0, y3 = 0, y4 = 0, y5 = 0;
    double Y, X;
    if (selCol < 1) return;
    if (curSer < C->SeriesList->Count)
    {
        for (int i=1; i<G->RowCount; i++)
        {
            y1 = y2;
            y2 = y3;
            y3 = y4;
            y4 = y5;
            y5 = G->Cells[selCol][i].ToDouble() * scale;

            Y = (y1+y2+y3+y4+y5)/(1.0*Sign(y1)+1.0*Sign(y2)+1.0*Sign(y3)+1.0*Sign(y4)+1.0*Sign(y5));
            X = ExtractDateTime(G->Cells[0][i]);
            C->SeriesList->Series[curSer]->AddXY(X, Y, "", clBlack);
        }
        curSer++;
    }
    /*
    double y1 = 0, y2 = 0, y3 = 0, y4 = 0, y5 = 0, y6 = 0, y7 = 0;
    double Y, X;
    if (selCol < 1) return;
    if (curSer < C->SeriesList->Count)
    {
        for (int i=1; i<G->RowCount; i++)
        {
            y1 = y2;
            y2 = y3;
            y3 = y4;
            y4 = y5;
            y5 = y6;
            y6 = y7;
            y7 = G->Cells[selCol][i].ToDouble() * scale;

            Y = (y1+y2+y3+y4+y5+y6+y7)/(1.0*Sign(y1)+1.0*Sign(y2)+1.0*Sign(y3)+1.0*Sign(y4)+1.0*Sign(y5)+1.0*Sign(y6)+1.0*Sign(y7));
            X = ExtractDateTime(G->Cells[0][i]);
            C->SeriesList->Series[curSer]->AddXY(X, Y, "", clBlack);
        }
        curSer++;
    }
    */
}

//---------------------------------------------------------------------------
void __fastcall TPlotF::NDelLastSerClick(TObject *Sender)
{
    if (curSer)
        C->SeriesList->Series[--curSer]->Clear();

    selCol = -1;
}

//---------------------------------------------------------------------------
void __fastcall TPlotF::BResetClick(TObject *Sender)
{
    for (int i=0; i<C->SeriesList->Count; i++)
    {
        C->SeriesList->Series[i]->Clear();
    }
    curSer = 0;
    selCol = -1;
    C->UndoZoom();
}

//---------------------------------------------------------------------------
void __fastcall TPlotF::BPrintClick(TObject *Sender)
{
    ChartPreview(this, C);
}

//---------------------------------------------------------------------------
void __fastcall TPlotF::NExitClick(TObject *Sender)
{
    Close();
}

//---------------------------------------------------------------------------
void __fastcall TPlotF::GDblClick(TObject *Sender)
{
    BMakeClick(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TPlotF::NAboutClick(TObject *Sender)
{
    AnsiString ver = "2.5.0-beta";
    ShowMessage("Плоттер\nВерсия "+ver+"\n© 2003-2005 Руслан Кеба\nhttp://www.kometalab.com.ua");
}

//---------------------------------------------------------------------------

