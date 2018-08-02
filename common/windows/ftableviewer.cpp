//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "ftableviewer.h"
#include "fdm.h"
#include "dbacts.h"
#include "fdatetimeselect.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ZAbstractDataset"
#pragma link "ZAbstractRODataset"
#pragma link "ZAbstractTable"
#pragma link "ZDataset"
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
TTableViewer *TableViewer;

//---------------------------------------------------------------------------
__fastcall TTableViewer::TTableViewer(TComponent* Owner)
    : TForm(Owner)
{
    FloatFieldDisplayFormat = "0.0";
}

//---------------------------------------------------------------------------
void TTableViewer::SetTable(AnsiString name)
{
    t->Active = false;
    if (name == "points")
    {
        tTableName = name;
        SetIntervalFilter(1);
        Caption = "Таблица: Точки контроля";
    }
    else
    if (name == "vagons")
    {
        tTableName = name;
        SetIntervalFilter(1);
        Caption = "Таблица: Вагоны";
    }
    else
    if (name == "calibration")
    {
        tTableName = name;
        SetIntervalFilter(0);
        Caption = "Таблица: Градиуровка";
    }
    else
    if (name == "routes")
    {
        tTableName = name;
        SetIntervalFilter(1);
        Caption = "Таблица: Маршруты движения угля";
    }
    else
    if (name == "accumulators")
    {
        tTableName = name;
        SetIntervalFilter(0);
        Caption = "Таблица: Аккумуляторы";
    }
    else
    {
        return;
    }

    tSortedFields = "";
    tWhereFilter = "";
    RefreshGrid();
}

//---------------------------------------------------------------------------
void TTableViewer::RefreshGrid(void)
{
    AnsiString sql = "";
    Variant f0, f1;
    if (t->Active && t->Fields->Count > 1)
    {
        f0 = t->Fields->Fields[0]->AsVariant;
        f1 = t->Fields->Fields[1]->AsVariant;
    }
    t->DisableControls();
    t->Close();
    sql = "SELECT * FROM "+tTableName+" WHERE "+tIntervalFilter;
    if (tWhereFilter.Length() > 0)
        sql += " AND "+tWhereFilter;
    if (tSortedFields.Length() > 0)
        sql += " ORDER BY "+tSortedFields;
    t->SQL->Text = sql;
    t->Open();
    t->EnableControls();

    TLocateOptions Opts;
    Opts.Clear();
    Opts << loPartialKey;
    Variant locvalues[2];
    locvalues[0] = f0;
    locvalues[1] = f1;

    if (!t->Locate(t->Fields->Fields[0]->FieldName + ";" + t->Fields->Fields[1]->FieldName,
                   VarArrayOf(locvalues, 1),
                   Opts))
    {
        t->Last();
    }

    for (int i=0; i<t->FieldCount; i++)
    {
        if (t->Fields->Fields[i]->DataType == ftFloat)
        {
            if (t->Fields->Fields[i]->FieldName.UpperCase() == "VAL")
            {
                dynamic_cast<TNumericField *>(t->Fields->Fields[i])->DisplayFormat = "0.#######";
                dynamic_cast<TNumericField *>(t->Fields->Fields[i])->DisplayWidth = 16;
            }
            else
                dynamic_cast<TNumericField *>(t->Fields->Fields[i])->DisplayFormat = "0.0";
        }
    }

    StatusBar->SimpleText = "Записей отображено: " + IntToStr(t->RecordCount);
}

//---------------------------------------------------------------------------
void __fastcall TTableViewer::TBRefreshClick(TObject *Sender)
{
    RefreshGrid();
}

//---------------------------------------------------------------------------
void TTableViewer::SetIntervalFilter(int it)
{
    intervaltype = it;
    TDateTime dt;
    switch (intervaltype)
    {
        case 1: {dt = 1.0/24;break;}
        case 2: {dt = 6.0/24;break;}
        case 3: {dt = 1.0;break;}
        case 0: {tIntervalFilter = "1=1";return;}
        default:{tIntervalFilter = "1=1";return;}
    }

    AnsiString F = "moment";
    AnsiString V = FormatDateTimeToDB(Now() - dt);

    tIntervalFilter = F
              + " >= '"
              + V + "'";
}

//---------------------------------------------------------------------------
void __fastcall TTableViewer::TBFilterClick(TObject *Sender)
{
    AnsiString F = G->SelectedField->DisplayName;
    AnsiString V = G->SelectedField->AsString;
    if (G->SelectedField->DataType == ftDateTime)
        V = FormatDateTimeStrToDB(V);

    if (tWhereFilter.Length() == 0)
    {
        tWhereFilter = F
                  + " = '"
                  + V + "'";
    }
    else
    {
        tWhereFilter = tWhereFilter
                  + " AND "
                  + F
                  + " = '"
                  + V + "'";
    }

    RefreshGrid();
}

//---------------------------------------------------------------------------
void __fastcall TTableViewer::TBRFilterClick(TObject *Sender)
{
    AnsiString F = G->SelectedField->DisplayName;
    AnsiString V = G->SelectedField->AsString;
    if (G->SelectedField->DataType == ftDateTime)
        V = FormatDateTimeStrToDB(V);

    if (tWhereFilter.Length() == 0)
    {
        tWhereFilter = F
                  + " <> '"
                  + V + "'";
    }
    else
    {
        tWhereFilter = tWhereFilter
                  + " AND "
                  + F
                  + " <> '"
                  + V + "'";
    }

    RefreshGrid();
}

//---------------------------------------------------------------------------
void __fastcall TTableViewer::TBCancelClick(TObject *Sender)
{
    tWhereFilter = "";
    tSortedFields = "";

    RefreshGrid();
}

//---------------------------------------------------------------------------
void __fastcall TTableViewer::TBSortClick(TObject *Sender)
{
    AnsiString F = G->SelectedField->FieldName;
    tSortedFields = F;

    RefreshGrid();
}

//---------------------------------------------------------------------------
void __fastcall TTableViewer::TBRSortClick(TObject *Sender)
{
    AnsiString F = G->SelectedField->FieldName;
    tSortedFields = F+" DESC";

    RefreshGrid();
}

//---------------------------------------------------------------------------
void __fastcall TTableViewer::TBFindClick(TObject *Sender)
{
    AnsiString Str, FindField, FindValue;
    int FieldIndex;
    bool ok = false;

    if (InputQuery("Поиск", "Введите значение для поиска:", FindValue))
    {
        FindField = G->SelectedField->DisplayName;
        FieldIndex = G->SelectedIndex;
        //FindValue = EnterDataF->E->Text;
        FindValue = FindValue.LowerCase();

        while(1)
        {
            t->DisableControls();
            while (!t->Eof)
            {
                t->Next();
                Str = t->FieldByName(FindField)->AsString;
                Str = Str.LowerCase();
                if (Str.Pos(FindValue))
                {
                    t->EnableControls();
                    G->SelectedIndex = FieldIndex;
                    ok = true;
                    break;
                }
            }
            t->EnableControls();
            if (!ok)
            {
                if (Application->MessageBox(
                       "Ничего не найдено!\nПродолжить сначала?",
                       "Поиск",
                       MB_YESNO+MB_ICONQUESTION) == IDYES)
                {
                    t->First();
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TTableViewer::TBTimeSortClick(TObject *Sender)
{
    TDateTime t1, t2;
    AnsiString F, V1, V2;
    if (G->SelectedField->DataType == ftDateTime)
    {
        t1 = t2 = G->SelectedField->AsDateTime;
    }
    else
    {
        return;
    }

    if (InputDateTime("Выбор интревала времени", true, t1, t2))
    {
        F = G->SelectedField->DisplayName;
        V1 = FormatDateTimeToDB(t1);
        V2 = FormatDateTimeToDB(t2);

        tWhereFilter = F
                  + " >= '" + V1 + "' AND "
                  + F
                  + " <= '" + V2 + "'";

        RefreshGrid();
    }

}

//---------------------------------------------------------------------------
void __fastcall TTableViewer::N1hourClick(TObject *Sender)
{
    N1hour->Checked = true;
    SetIntervalFilter(1);
    RefreshGrid();
}

//---------------------------------------------------------------------------
void __fastcall TTableViewer::N6hoursClick(TObject *Sender)
{
    N6hours->Checked = true;
    SetIntervalFilter(2);
    RefreshGrid();
}

//---------------------------------------------------------------------------
void __fastcall TTableViewer::N1dayClick(TObject *Sender)
{
    N1day->Checked = true;
    SetIntervalFilter(3);
    RefreshGrid();
}

//---------------------------------------------------------------------------
void __fastcall TTableViewer::NAllClick(TObject *Sender)
{
    NAll->Checked = true;
    SetIntervalFilter(0);
    RefreshGrid();
}

//---------------------------------------------------------------------------

