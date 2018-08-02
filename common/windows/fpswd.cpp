//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------
#include "fpswd.h"

//---------------------------------------------------------------------
#pragma resource "*.dfm"

//---------------------------------------------------------------------
int CheckPassword(AnsiString ACaption, AnsiString APassword)
{
    TPasswordDlg *PasswordDlg;
    int ret = PASSWORD_NOT_SUCCESS;
    AnsiString realPassword = APassword + FormatDateTime("dd", Date());

    PasswordDlg = new TPasswordDlg(Application);
    try {
    PasswordDlg->Caption = ACaption;
    int mr = PasswordDlg->ShowModal();
    if (mr == mrIgnore)
        ret = PASSWORD_TIMEOUT;
    else if (mr == mrOk && PasswordDlg->Password->Text == realPassword)
        ret = PASSWORD_SUCCESS;

    } __finally {
    delete PasswordDlg;
    }

    return ret;    
}

//---------------------------------------------------------------------
__fastcall TPasswordDlg::TPasswordDlg(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TPasswordDlg::TimerTimer(TObject *Sender)
{
    ModalResult = mrIgnore;
}
//---------------------------------------------------------------------------

