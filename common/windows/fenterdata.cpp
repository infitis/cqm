//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "fenterdata.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TEnterDataF::TEnterDataF(TComponent* Owner)
    : TForm(Owner)
{
    DataFileName = "..\\lib\\enter\\enter.dat";
    try
    {
        E->Items->LoadFromFile(DataFileName);
    }
    catch(...){}

    E->Text = E->Items->Strings[0];
}
//---------------------------------------------------------------------------
__fastcall TEnterDataF::~TEnterDataF()
{
    try
    {
        if (E->Text != "")
        {
            if (E->Items->Strings[0] != E->Text)
            {
                E->Items->Insert(0, E->Text);
                if (E->Items->Count >= 16) E->Items->Delete(E->Items->Count-1);
                E->Items->SaveToFile(DataFileName);
            }
        }
    }
    catch(...){}
}

//---------------------------------------------------------------------------
bool __fastcall InputData(const AnsiString ACaption,
                          const AnsiString APrompt,
                                AnsiString &Value)
{
    bool ok = false;
    TEnterDataF *EnterDataF;

    try
    {
        EnterDataF = new TEnterDataF(NULL);
        EnterDataF->Caption = ACaption;
        EnterDataF->L->Caption = APrompt;
        if (EnterDataF->ShowModal() == mrOk)
        {
            Value = EnterDataF->E->Text;
            ok = true;
        }
    }
    __finally
    {
        delete EnterDataF;
    }

    return ok;
}


//---------------------------------------------------------------------------

