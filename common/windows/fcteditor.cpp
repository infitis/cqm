//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "fcteditor.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ZAbstractDataset"
#pragma link "ZAbstractRODataset"
#pragma link "ZAbstractTable"
#pragma link "ZDataset"
#pragma link "ZSqlUpdate"
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
void ShowCtEditor(void)
{
    TCteF *CteF = NULL;
    CteF = new TCteF(Application);
    CteF->ShowModal();
    delete CteF;
}

//---------------------------------------------------------------------------
__fastcall TCteF::TCteF(TComponent* Owner)
    : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TCteF::FormCreate(TObject *Sender)
{
    tp->Active = true;
    tr->Active = true;
    tt->Active = true;
    RefreshTypesGrid();
}

//---------------------------------------------------------------------------
void __fastcall TCteF::FormDestroy(TObject *Sender)
{
    tt->Active = false;
    tr->Active = false;
    tp->Active = false;
}

//---------------------------------------------------------------------------
void __fastcall TCteF::RefreshGrids(void)
{
    Variant f0, f1;
    Variant locvalues[2];
    TLocateOptions Opts;
    Opts.Clear();
    Opts << loPartialKey;

    //позиции
    if (tp->Active && tp->Fields->Count > 1)
    {
        f0 = tp->Fields->Fields[0]->AsVariant;
        f1 = tp->Fields->Fields[1]->AsVariant;
    }
    tp->DisableControls();
    tp->Close();
    tp->Open();
    tp->EnableControls();

    locvalues[0] = f0;
    locvalues[1] = f1;

    if (!tp->Locate(tp->Fields->Fields[0]->FieldName + ";" + tp->Fields->Fields[1]->FieldName,
                   VarArrayOf(locvalues, 1),
                   Opts))
    {
        tp->First();
    }

    //марки
    if (tr->Active && tr->Fields->Count > 1)
    {
        f0 = tr->Fields->Fields[0]->AsVariant;
        f1 = tr->Fields->Fields[1]->AsVariant;
    }
    tr->DisableControls();
    tr->Close();
    tr->Open();
    tr->EnableControls();

    locvalues[0] = f0;
    locvalues[1] = f1;

    if (!tr->Locate(tr->Fields->Fields[0]->FieldName + ";" + tr->Fields->Fields[1]->FieldName,
                   VarArrayOf(locvalues, 1),
                   Opts))
    {
        tr->First();
    }
}

//---------------------------------------------------------------------------
void __fastcall TCteF::RefreshTypesGrid(void)
{
    if (!tt->Active)
    {
        return;
    }

    Variant f0, f1;
    Variant locvalues[2];
    TLocateOptions Opts;
    Opts.Clear();
    Opts << loPartialKey;
    AnsiString SortField;

    //типы
    if (tt->Active && tt->Fields->Count > 1)
    {
        f0 = tt->Fields->Fields[0]->AsVariant;
        f1 = tt->Fields->Fields[1]->AsVariant;
    }
    tt->DisableControls();
    tt->Close();

    tt->Filtered = true;
    if (RBpos->Checked && !(tp->Eof && tp->Bof))
    {
        tt->Filter = "pos_id = "+tp->FieldByName("id")->AsString;
        SortField = "coalrank_id desc";
    }
    else
    if (RBrank->Checked && !(tr->Eof && tr->Bof))
    {
        tt->Filter = "coalrank_id = '"+tr->FieldByName("id")->AsString+"'";
        SortField =  "pos_id desc";
    }
    else
    if (RBposrank->Checked && !(tp->Eof && tp->Bof) && !(tr->Eof && tr->Bof))
    {
        tt->Filter = "pos_id = "+tp->FieldByName("id")->AsString +
                " AND coalrank_id = '"+tr->FieldByName("id")->AsString+"'";
        SortField =  "coalrank_id desc, pos_id desc";
    }
    else
    {
        tt->Filtered = false;
        SortField =  "coalrank_id desc, pos_id desc";
    }

    tt->SortedFields = SortField;
    tt->Open();
    tt->EnableControls();

    locvalues[0] = f0;
    locvalues[1] = f1;

    if (!tt->Locate(tt->Fields->Fields[0]->FieldName + ";" + tt->Fields->Fields[1]->FieldName,
                   VarArrayOf(locvalues, 1),
                   Opts))
    {
        tt->First();
    }

}

//---------------------------------------------------------------------------

void __fastcall TCteF::tOnScroll(TDataSet *DataSet)
{
    RefreshTypesGrid();
}
//---------------------------------------------------------------------------

void __fastcall TCteF::RBposrankClick(TObject *Sender)
{
    RefreshTypesGrid();
}

//---------------------------------------------------------------------------
void __fastcall TCteF::SpeedButton1Click(TObject *Sender)
{
    Close();
}

//---------------------------------------------------------------------------
void __fastcall TCteF::SBDeleteClick(TObject *Sender)
{
    int pos_id      = tt->FieldByName("pos_id")->AsInteger;
    int coalrank_id = tt->FieldByName("coalrank_id")->AsInteger;

    DoSql(AnsiString().sprintf(
    "delete from coaltypes where pos_id=%d and coalrank_id=%d"
    ,pos_id, coalrank_id));

    tt->Refresh();
}

//---------------------------------------------------------------------------
bool __fastcall TCteF::InputCoaltype(int &c)
{
    AnsiString s = IntToStr(c);
    if (InputQuery("Тип угля", "Введите значение типа угля", s))
    {
        try {
            c = StrToInt(s);
        }
        catch (...) {
            Application->MessageBox("Неверное значение типа угля!", "Ошибка ввода");
            return false;
        }

        return true;
    }
    return false;
}

//---------------------------------------------------------------------------
void __fastcall TCteF::SBAddClick(TObject *Sender)
{
    int pos_id      = tp->FieldByName("id")->AsInteger;
    int coalrank_id = tr->FieldByName("id")->AsInteger;
    int c = 0;
    if (InputCoaltype(c))
    {
        DoSql(AnsiString().sprintf(
        "execute procedure add_coaltype %d, %d, %d",
        pos_id, coalrank_id,c));
    }

    tt->Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TCteF::SBAdd4rClick(TObject *Sender)
{
    int pos_id      = 0;
    int coalrank_id = tr->FieldByName("id")->AsInteger;
    int c = 0;
    if (InputCoaltype(c))
    {
        DoSql(AnsiString().sprintf(
        "execute procedure add_coaltype %d, %d, %d",
        pos_id, coalrank_id,c));
    }

    tt->Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TCteF::SBAdd4pClick(TObject *Sender)
{
    int pos_id      = tp->FieldByName("id")->AsInteger;
    int coalrank_id = 0;
    int c = 0;
    if (InputCoaltype(c))
    {
        DoSql(AnsiString().sprintf(
        "execute procedure add_coaltype %d, %d, %d",
        pos_id, coalrank_id,c));
    }

    tt->Refresh();

}

//---------------------------------------------------------------------------
void __fastcall TCteF::GtDblClick(TObject *Sender)
{
    int pos_id      = tt->FieldByName("pos_id")->AsInteger;
    int coalrank_id = tt->FieldByName("coalrank_id")->AsInteger;
    int c           = tt->FieldByName("coaltype")->AsInteger;
    if (InputCoaltype(c))
    {
        DoSql(AnsiString().sprintf(
        "execute procedure add_coaltype %d, %d, %d",
        pos_id, coalrank_id,c));
    }

    tt->Refresh();
}

//---------------------------------------------------------------------------

