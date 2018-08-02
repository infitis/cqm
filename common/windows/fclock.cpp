//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "fclock.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TClockF *ClockF;

//---------------------------------------------------------------------------
__fastcall TClockF::TClockF(TComponent* Owner)
    : TForm(Owner)
{
    moved = false;
}

//---------------------------------------------------------------------------
void __fastcall TClockF::TimerTimer(TObject *Sender)
{
    L->Caption = FormatDateTime("yyyy-mm-dd hh:nn:ss", Now());
}

//---------------------------------------------------------------------------
void __fastcall TClockF::LMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
    moved = true;
    x = X; y = Y;
    c = L->Color;
    L->Color = TColor(L->Color + 0x141408);
}

//---------------------------------------------------------------------------
void __fastcall TClockF::LMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
    moved = false;
    L->Color = c;
}

//---------------------------------------------------------------------------
void __fastcall TClockF::LMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
    if (moved)
    {
        Left = Left + X - x;
        Top  = Top  + Y - y;
    }
}

//---------------------------------------------------------------------------
void __fastcall TClockF::FormShow(TObject *Sender)
{
    TimerTimer(NULL);
}

//---------------------------------------------------------------------------
