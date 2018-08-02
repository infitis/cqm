//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "fpositseditor.h"
#include "..\windows\fdm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ZAbstractDataset"
#pragma link "ZAbstractRODataset"
#pragma link "ZAbstractTable"
#pragma link "ZDataset"
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
TPositsEditorF *PositsEditorF;

//---------------------------------------------------------------------------
__fastcall TPositsEditorF::TPositsEditorF(TComponent* Owner)
    : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TPositsEditorF::Init(void)
{
    Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TPositsEditorF::Stop(void)
{
    t->Close();
}

//---------------------------------------------------------------------------

void __fastcall TPositsEditorF::Refresh(void)
{
    t->Close();
    t->Open();
}

//---------------------------------------------------------------------------
void __fastcall TPositsEditorF::SBRefreshClick(TObject *Sender)
{
    Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TPositsEditorF::SBDelPClick(TObject *Sender)
{
    char m[128] = "Удалить позицию № ";
    strcat(m, t->FieldByName("id")->AsString.c_str());
    strcat(m, " ?");
    if (Application->MessageBox(m, "Подтверждение", MB_YESNO+MB_ICONQUESTION) == IDYES)
    {
        t->Delete();
    }
    Refresh();
}

//---------------------------------------------------------------------------

void __fastcall TPositsEditorF::SBNewPClick(TObject *Sender)
{
    t->Insert();    
}
//---------------------------------------------------------------------------

void __fastcall TPositsEditorF::tAfterPost(TDataSet *DataSet)
{
    Refresh();    
}
//---------------------------------------------------------------------------

void __fastcall TPositsEditorF::SBFindVClick(TObject *Sender)
{
    if (EF->Text == "")
    {
        ShowMessage("Пустая строка для поиска!");
        return;
    }

    AnsiString need = EF->Text.LowerCase();
    AnsiString fldname = G->SelectedField->FieldName;
    AnsiString val;
    bool needfirst = false;
    t->Next();
    do
    {
        if (needfirst) t->First();
        while (!t->Eof)
        {
            val = t->FieldByName(fldname)->AsString.LowerCase();
            if (val.Pos(need))
            {
                return;
            }
            t->Next();
        }
    needfirst = Application->MessageBox("Ничего не найдено. Начать поиск с начала?",
                                 "Поиск", MB_YESNO+MB_ICONQUESTION) == ID_YES;
    }
    while (needfirst);
}
//---------------------------------------------------------------------------

void __fastcall TPositsEditorF::EFKeyPress(TObject *Sender, char &Key)
{
    if (Key == VK_RETURN)
    {
        SBFindVClick(Sender);
    }
}
//---------------------------------------------------------------------------

