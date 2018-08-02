//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "faboutic.h"
#include "cqmversion.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
TAboutICF *AboutICF = NULL;

//---------------------------------------------------------------------------
void SplashFormShow()
{
    if (AboutICF != NULL) return;

    AboutICF = new TAboutICF(Application);
    AboutICF->SBClose->Visible = false;
    AboutICF->FormStyle = fsStayOnTop;
    char icv[32], cqmv[32];
    cqm_version_get_string(cqmv);
    ic_version_get_string (icv);
    AboutICF->M->Lines->Insert(1, AnsiString("Версия ")+icv);
    AboutICF->M->Lines->Insert(2, AnsiString("Совместимая версия ПО МКУ ")+cqmv);

    AboutICF->Show();
    AboutICF->Update();
}

//---------------------------------------------------------------------------
void SplashFormClose()
{
    if (AboutICF == NULL) return;
    delete AboutICF;
    AboutICF = NULL;
}

//---------------------------------------------------------------------------
void AboutFormShow()
{
    if (AboutICF != NULL) return;
    try{
        AboutICF = new TAboutICF(Application);
        AboutICF->L->Visible = false;
        char icv[32], cqmv[32];
        cqm_version_get_string(cqmv);
        ic_version_get_string (icv);
        AboutICF->M->Lines->Insert(1, AnsiString("Версия ")+icv);
        AboutICF->M->Lines->Insert(2, AnsiString("Совместимая версия ПО МКУ ")+cqmv);
        AboutICF->ShowModal();
    }
    __finally
    {
        delete AboutICF;
        AboutICF = NULL;
    }
}

//---------------------------------------------------------------------------
__fastcall TAboutICF::TAboutICF(TComponent* Owner)
    : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TAboutICF::SBCloseClick(TObject *Sender)
{
    ModalResult = mrOk;
}

//---------------------------------------------------------------------------
