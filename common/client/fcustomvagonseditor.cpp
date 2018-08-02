//---------------------------------------------------------------------------
#include <vcl.h>
#include <inifiles.hpp>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "fcustomvagonseditor.h"
#include "clientdata.h"
#include "globcli.h"
#include "..\windows\fdm.h"
#include "..\windows\fmsgs.h"
#include "..\classes\coalheap.h"
#include "fvagonbatch.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ZAbstractDataset"
#pragma link "ZAbstractRODataset"
#pragma link "ZAbstractTable"
#pragma link "ZDataset"
#pragma link "ZSqlUpdate"
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
TCustomVagonsEditorF *CustomVagonsEditorF = NULL;
TCustomVagonsEditorF* VagonsEditors[MAX_CLIENT_VAGONS];

//---------------------------------------------------------------------------
__fastcall TCustomVagonsEditorF::TCustomVagonsEditorF(TComponent* Owner)
    : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TCustomVagonsEditorF::Refresh(int rid)
{
    if (q->State == dsEdit)
    {
        return;
        //t->Post();
    }

    qcoalranks->Close();
    qcoalranks->Open();

    /*
    Variant locvalues[1];
    TLocateOptions Opts; Opts.Clear();

    if (q->Active)
    {
        if (rid == 0)
            locvalues[0] = q->FieldByName("id")->AsVariant;
        else
            locvalues[0] = Variant(rid);
    }
    else
    {
        locvalues[0] = Variant(1000000);
    }
    */

    //my locate
    int wasid = 0;
    if (q->Active)
    {
        wasid = q->FieldByName("id")->AsInteger;
    }


    q->DisableControls();
    q->Close();
    qWhereFilter = AnsiString("vname")
              + " = '"
              + clivagons[myvagonindex].name + "' ";
    if (double(dt) < 366)
    {
        qWhereFilter = qWhereFilter
              + " and addday(moment, "+IntToStr(dt)+") >= current_timestamp";
              //" and cast(current_timestamp - moment as decimal(17,4)) <= cast("+IntToStr(dt)+" as decimal(17,4))";
    }
    else
    {
        //нет фильтра по времени, показываем всё
    }

    qSortedFields = "moment, id";
    q->SQL->Text = AnsiString("SELECT * FROM vagons WHERE ")
                 + qWhereFilter
                 + " ORDER BY " + qSortedFields;
    q->Open();
    LocateVagon(wasid);
    q->EnableControls();

    /*
    if (!q->Locate("id", locvalues, Opts))
    {
        q->Last();
    }
    */
    
    ShowStatus();
}

//---------------------------------------------------------------------------
void __fastcall TCustomVagonsEditorF::LocateVagon(int wasid)
{
    q->Last();
    if (wasid == 0)
        return;
    while (!q->Bof)
    {
        if (q->FieldByName("id")->AsInteger == wasid)
            return;
        q->Prior();
    }
    q->Last();
}

//---------------------------------------------------------------------------
void __fastcall TCustomVagonsEditorF::Init(int vid)
{
    myvagonindex = vid;
    dt = 2;
    N2days->Checked = true;
    Caption = clivagons[myvagonindex].title;
    ToolBarVB->Visible = VagonBatchPanelVisible;
    LoadPosition();
    Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TCustomVagonsEditorF::LoadPosition(void)
{
	Top =			    	ini->ReadInteger(AnsiString("VagEditor-")+IntToStr(myvagonindex), "Top", 10);
	Left =			    	ini->ReadInteger(AnsiString("VagEditor-")+IntToStr(myvagonindex), "Left", 10);
	Width =			    	ini->ReadInteger(AnsiString("VagEditor-")+IntToStr(myvagonindex), "Width", 200);
	Height = 		    	ini->ReadInteger(AnsiString("VagEditor-")+IntToStr(myvagonindex), "Height", 200);
}

//---------------------------------------------------------------------------
void __fastcall TCustomVagonsEditorF::N2daysClick(TObject *Sender)
{
    dt = 2;
    N2days->Checked = true;
    Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TCustomVagonsEditorF::N1monthClick(TObject *Sender)
{
    dt = 32;
    N1month->Checked = true;
    Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TCustomVagonsEditorF::N1yearClick(TObject *Sender)
{
    dt = 367;
    N1year->Checked = true;
    Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TCustomVagonsEditorF::tAfterPost(TDataSet *DataSet)
{
    Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TCustomVagonsEditorF::ShowStatus(void)
{
    Status->SimpleText = "Количество вагонов: " + IntToStr(q->RecordCount)
                       + "; тип: "              + IntToStr(q->FieldByName("coaltype")->AsInteger);
}

//---------------------------------------------------------------------------
void __fastcall TCustomVagonsEditorF::tAfterScroll(TDataSet *DataSet)
{
    ShowStatus();
}

//---------------------------------------------------------------------------
void __fastcall TCustomVagonsEditorF::SBNewVClick(TObject *Sender)
{
    AddVagon();
}

//---------------------------------------------------------------------------
void __fastcall TCustomVagonsEditorF::SBMergeVClick(TObject *Sender)
{
    int id1, id2;
    id1 = q->FieldByName("id")->AsInteger;
    q->Next();
    id2 = q->FieldByName("id")->AsInteger;
    MergeVagons(id1, id2);
    Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TCustomVagonsEditorF::SBMergeCustClick(TObject *Sender)
{
    int id1, id2;
    id1 = StrToInt(E1->Text);
    id2 = StrToInt(E2->Text);
    MergeVagons(id1, id2);
    E1->Text = "";
    E2->Text = "";
    SBMergeCust->Enabled = false;
    Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TCustomVagonsEditorF::AddVagon(void)
{
    TDateTime dt1, dt2;
    AnsiString mdt;

    dt1 = q->FieldByName("moment")->AsDateTime;
    q->Next();
    dt2 = q->FieldByName("moment")->AsDateTime;
    if (dt1 == dt2 || dt1 > dt2 || double(dt2)-double(dt1) < 1.0/24/60)
    {
        /*
        if (
        MessageBox(NULL, "Интервал времени между вагонами должен быть больше одной минуты.\nВставить вагон с текущим временем и датой?",
        "Невозможно вставить вагон", MB_YESNO+MB_ICONQUESTION) == ID_YES
        )
        {
        */
            mdt = FormatDateTimeToDB(Now());
        /*
        }
        else
        {
            return;
        }
        */
    }
    else
    {
        mdt = FormatDateTimeToDB((double(dt2)+double(dt1)) / 2);
    }

    if (DoSql(AnsiString().sprintf(
        "insert into vagons (id, moment, vname) values(NULL, '%s', '%s')"
        ,mdt.c_str(), clivagons[myvagonindex].name)))
    {
        int lii = LastInsertId();
        DoMsg(AnsiString("Вставлен вагон: на ")+Caption+", id="+IntToStr(lii)+", Время="+mdt+".");
        Refresh(lii);
    }
    else
    {
        Application->MessageBox("Невозможно вставить вагон!",
                         "Ошибка", MB_OK+MB_ICONERROR);
    }
}

//---------------------------------------------------------------------------
void __fastcall TCustomVagonsEditorF::MergeVagons(int id1, int id2)
{
    if (id1 == id2)
    {
        Application->MessageBox("Невозможно объеденить эти вагоны!",
                         "Ошибка", MB_OK+MB_ICONERROR);
        return;
    }

    CoalHeap vh;
    double p, a, wei;
    //вагон 1
    OpenSql("select p, a, wei from vagons where id="+IntToStr(id1));
    if (EMPTYRESULT)
    {
        Application->MessageBox("В таблице базы данных не найден первый вагон!",
                         "Ошибка", MB_OK+MB_ICONERROR);
        return;
    }
    p   = GETFIELD("p")->AsFloat;
    a   = GETFIELD("a")->AsFloat;
    wei = GETFIELD("wei")->AsFloat;
    vh.addCoal(Coal(p,a));
    //вагон 2
    OpenSql("select p, a, wei from vagons where id="+IntToStr(id2));
    if (EMPTYRESULT)
    {
        Application->MessageBox("В таблице базы данных не найден второй вагон!",
                         "Ошибка", MB_OK+MB_ICONERROR);
        return;
    }
    p   = GETFIELD("p")->AsFloat;
    a   = GETFIELD("a")->AsFloat;
    wei += GETFIELD("wei")->AsFloat;
    vh.addCoal(Coal(p,a));
    //записываем во второй
    if(DoSql(AnsiString().sprintf(
    "update vagons set p=%3.1f, a=%3.1f, wei=%3.1f where id=%i",
    vh.c.P.val, vh.c.A.val, wei, id2)))
    {
        if (ROWSAFFECTED != 1)
        {
            Application->MessageBox("Неожиданный эффект обновления второго вагона.",
                             "Ошибка", MB_OK+MB_ICONERROR);
            return;
        }
    }
    if (!DoSql("delete from vagons where id="+IntToStr(id1)))
    {
            Application->MessageBox("Ошибка удаления первого вагона.",
                             "Ошибка", MB_OK+MB_ICONERROR);
    }
    Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TCustomVagonsEditorF::GDblClick(TObject *Sender)
{
    if (E1->Text == "")
    {
        E1->Text = q->FieldByName("id")->AsString;
        return;
    }
    else
    if (E2->Text == "" )
    {
        if (q->FieldByName("id")->AsString == E1->Text)
        {
            return;
        }
        E2->Text = q->FieldByName("id")->AsString;
        SBMergeCust->Enabled = true;
        return;
    }
    else
    {
        E1->Text = q->FieldByName("id")->AsString;
        E2->Text = "";
        SBMergeCust->Enabled = false;
        return;
    }

}

//---------------------------------------------------------------------------
void __fastcall TCustomVagonsEditorF::SBFindVClick(TObject *Sender)
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
    q->DisableControls();
    q->Next();
    do
    {
        if (needfirst) q->First();
        while (!q->Eof)
        {
            val = q->FieldByName(fldname)->AsString.LowerCase();
            if (val.Pos(need))
            {
                q->EnableControls();
                return;
            }
            q->Next();
        }
    needfirst = Application->MessageBox("Ничего не найдено. Начать поиск с начала?",
                                 "Поиск", MB_YESNO+MB_ICONQUESTION) == ID_YES;
    }
    while (needfirst);
    q->EnableControls();
}

//---------------------------------------------------------------------------
void __fastcall TCustomVagonsEditorF::EFKeyPress(TObject *Sender,
      char &Key)
{
    if (Key == VK_RETURN)
    {
        SBFindVClick(Sender);
    }
}

//---------------------------------------------------------------------------

void __fastcall TCustomVagonsEditorF::SpeedButton1Click(TObject *Sender)
{
    int newBatchNum;
    if (NewBatch(newBatchNum, this))
        Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TCustomVagonsEditorF::SBNewBatchClick(TObject *Sender)
{
    if (EditBatch(q->FieldByName("cert")->AsInteger, this))
        Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TCustomVagonsEditorF::SBDelVMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Shift.Contains(ssShift))
    {
        q->Delete();
        return;
    }

    q->Edit();
    char m[128] = "Удалить вагон № ";
    strcat(m, q->FieldByName("id")->AsString.c_str());
    strcat(m, " ?");
    if (Application->MessageBox(m, "Подтверждение", MB_YESNO) == IDYES)
    {
        q->Cancel();
        q->Delete();
    }
    else
    {
        q->Cancel();
    }
    Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TCustomVagonsEditorF::GKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    TShiftState CtrlOnly;
    CtrlOnly<<ssCtrl;
    if (Shift == CtrlOnly && (Key == 'd' || Key == 'D'))
    {
        if (G->SelectedField->FieldName.LowerCase() == AnsiString("rwdate"))
        {
            q->Edit();
            q->FieldByName("rwdate")->AsDateTime = Date();
        }
    }
}

//---------------------------------------------------------------------------

