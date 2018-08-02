//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "falarm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
__fastcall TAlarmF::TAlarmF(TComponent* Owner)
    : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TAlarmF::SBCloseClick(TObject *Sender)
{
    ModalResult = mrOk;
    Close();
}

//---------------------------------------------------------------------------
void __fastcall TAlarmF::TimerTimer(TObject *Sender)
{
    Beep(440, 125);
    if (Color == 0x404040)
        Color = (TColor)0xe0e0e0;
    else
        Color = (TColor)0x404040;
}

//---------------------------------------------------------------------------
void __fastcall TAlarmF::FormPaint(TObject *Sender)
{
    for (int x=0; x<Width; x++)
    {
        Canvas->Pixels[x][0] = (TColor)0;
        Canvas->Pixels[x][Height-1] = (TColor)0;
    }
    for (int y=0; y<Height; y++)
    {
        Canvas->Pixels[0][y] = (TColor)0;
        Canvas->Pixels[Width-1][y] = (TColor)0;
    }
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
