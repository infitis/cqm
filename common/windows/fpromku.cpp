//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "fpromku.h"
#include "cqmversion.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
__fastcall TProMKUF::TProMKUF(TComponent* Owner)
    : TForm(Owner)
{
    char version[127] = "";
    cqm_version_get_string(version);
	AnsiString myver =          AnsiString("Версия ") + version;
    Memo->Lines->Insert(2, myver);

}
//---------------------------------------------------------------------------
void __fastcall TProMKUF::ImageClick(TObject *Sender)
{
    ModalResult = mrOk;
    Close();    
}
//---------------------------------------------------------------------------


