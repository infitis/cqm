//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "faboutsrv.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAboutF *AboutF;
//---------------------------------------------------------------------------
__fastcall TAboutF::TAboutF(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAboutF::FormShow(TObject *Sender)
{
    try{
    RE->Lines->LoadFromFile("..\\doc\\about\\about.rtf");
    } catch(...){
    Close();
    }

    SendMessage(RE->Handle,
    WM_VSCROLL,
    SB_TOP ,
    0);

    pos = 0;

    T->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TAboutF::TTimer(TObject *Sender)
{
    pos += 1;
    SendMessage(RE->Handle,
    WM_VSCROLL,
    SB_THUMBPOSITION + pos*0x10000,
    0);
}
//---------------------------------------------------------------------------

void __fastcall TAboutF::REMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
    T->Enabled = false;
    Close();
}
//---------------------------------------------------------------------------

