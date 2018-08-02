//---------------------------------------------------------------------------
#include <vcl.h>
#include <ctype.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "fvagonbatch.h"
#include "fdm.h"
#include "fmsgs.h"
#include "fcustomvagonseditor.h"
#include "clientdata.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
TVagonBatchF* VagonBatchF = NULL;

//---------------------------------------------------------------------------
int NewBatch(int& batchNumber, TCustomVagonsEditorF* editor)
{
    int ret = 0;
    AnsiString q;
    VagonBatchF = new TVagonBatchF(Application);
    try
    {

    VagonBatchF->Caption = "Новая партия вагонов";
    VagonBatchF->FillPos();
    VagonBatchF->FillRanks();

    if (VagonBatchF->ShowModal() == mrOk)
    {
        q = AnsiString("select * from vagons where cert=")+
        IntToStr(VagonBatchF->batchNum)+
        " and YEAR(rwdate)=YEAR('"+FormatDateTimeToDB(VagonBatchF->rwDate, 1)+
        "') limit 1";

        OpenSql(q);
        if (!EMPTYRESULT)
        {
            ShowMessage("Партия вагонов с таким номером в этом году уже есть.");
            return 0;
        }

        for (int i=0; i<VagonBatchF->vagNum; i++)
        {
            q=AnsiString("insert into vagons set moment=now(), vname='")+
            clivagons[editor->myvagonindex].name+
            "', cert="+IntToStr(VagonBatchF->batchNum)+
            ", rwdate='"+FormatDateTimeToDB(VagonBatchF->rwDate, 1)+
            "', pos="+IntToStr(VagonBatchF->posNum)+
            ", coalrank='"+VagonBatchF->coalRank+
            "', w="+AnsiString().sprintf("%.1f", VagonBatchF->batchHum)+
            ", wei="+AnsiString().sprintf("%.1f", VagonBatchF->batchWei/VagonBatchF->vagNum);

            DoSql(q);

            int lii = LastInsertId();
            DoMsg(AnsiString("Вставлен вагон из партии: на ")+editor->Caption+", id="+IntToStr(lii)+".");
        }
        ret = 1;
    }

    }
    __finally
    {
        delete VagonBatchF;
    }

    return ret;
}

//---------------------------------------------------------------------------
int EditBatch(int batchNumber, TCustomVagonsEditorF* editor)
{
    int ret = 0;
    AnsiString q;
    VagonBatchF = new TVagonBatchF(Application);
    try
    {

    VagonBatchF->Caption = "Партия вагонов № "+IntToStr(batchNumber);
    VagonBatchF->FillPos(editor->q->FieldByName("pos")->AsInteger);
    VagonBatchF->FillRanks(editor->q->FieldByName("coalrank")->AsString);
    VagonBatchF->batchNum = batchNumber;
    VagonBatchF->rwDate =   editor->q->FieldByName("rwdate")->AsDateTime;
    VagonBatchF->batchHum = editor->q->FieldByName("w")->AsFloat;

    q = AnsiString("select count(*) as c, sum(wei) as s from vagons where cert=")+
    IntToStr(VagonBatchF->batchNum)+
    " and YEAR(rwdate)=YEAR('"+
    FormatDateTimeToDB(VagonBatchF->rwDate, 1)+"')";
    OpenSql(q);
    VagonBatchF->vagNum = GETFIELD("c")->AsInteger;
    VagonBatchF->batchWei = GETFIELD("s")->AsFloat;

    VagonBatchF->FillFields();
    VagonBatchF->EBatchNum->Enabled = false;
    VagonBatchF->EVN->Enabled = false;

    if (VagonBatchF->ShowModal() == mrOk)
    {
        q=AnsiString("update vagons set rwdate='")+
            FormatDateTimeToDB(VagonBatchF->rwDate, 1)+
            "', pos="+IntToStr(VagonBatchF->posNum)+
            ", coalrank='"+VagonBatchF->coalRank+
            "', w="+AnsiString().sprintf("%.1f", VagonBatchF->batchHum)+
            ", wei="+AnsiString().sprintf("%.1f", VagonBatchF->batchWei/VagonBatchF->vagNum)+
            " where cert="+IntToStr(VagonBatchF->batchNum)+
            " and YEAR(rwdate)=YEAR('"+FormatDateTimeToDB(VagonBatchF->rwDate, 1)+"')";

        DoSql(q);
        ret = 1;
    }

    }
    __finally
    {
        delete VagonBatchF;
    }

    return ret;
}

//---------------------------------------------------------------------------
__fastcall TVagonBatchF::TVagonBatchF(TComponent* Owner)
    : TForm(Owner)
{
    ERWD->Date = Date();
}

//---------------------------------------------------------------------------
void __fastcall TVagonBatchF::BOkClick(TObject *Sender)
{
    AnsiString ret = CheckFields();
    if (ret == "")
        ModalResult = mrOk;
    else
        ShowMessage(ret);
    return;
}

//---------------------------------------------------------------------------
void __fastcall TVagonBatchF::BCancelClick(TObject *Sender)
{
    ModalResult = mrCancel;
}

//---------------------------------------------------------------------------
AnsiString __fastcall TVagonBatchF::CheckFields(void)
{
    //проверим номер партии
    try
    {
        batchNum = StrToInt(EBatchNum->Text);
        if (batchNum < 0)
            throw Exception("batchNum < 0");
    }
    catch (...)
    {
        return AnsiString("Неверный номер партии.");
    }

    //жд сутки
    try
    {
        rwDate = ERWD->Date;
        /* TODO : проверить, что дата в допустимом интервале */
    }
    catch(...)
    {
        return AnsiString("Неверная дата ж/д суток.");
    }

    //позиция
    try
    {
        AnsiString posid, pos = CBPos->Text;
        if (pos == "")
            throw Exception("no_pos");
        for (int i=1; i<=pos.Length(); i++)
        {
            if (!isalnum(pos[i]))
                break;
            else
                posid = posid + pos[i];
        }
        posNum = StrToInt(posid);
        if (posNum<0)
            throw Exception("posNum<0");
    }
    catch(...)
    {
        return AnsiString("Неверная позиция.");
    }

    //проверим количество вагонов
    try
    {
        vagNum = StrToInt(EVN->Text);
        if (vagNum <= 0)
            throw Exception("vagNum <= 0");
    }
    catch (...)
    {
        return AnsiString("Неверное количество вагонов.");
    }

    //марка
    try
    {
        coalRank = CBRank->Text;
        if (coalRank == "")
            throw Exception("no_rank");
    }
    catch(...)
    {
        return AnsiString("Неверная марка.");
    }

    //проверим вес
    try
    {
       batchWei = StrToFloat(EP->Text);
        if (batchWei <= 0)
            throw Exception("batchWei <= 0");
    }
    catch (...)
    {
        return AnsiString("Неверный вес.");
    }

    //проверим влажность
    try
    {
       batchHum = StrToFloat(EH->Text);
        if (batchHum <= 0 || batchHum >=100)
            throw Exception("bad batchWei");
    }
    catch (...)
    {
        return AnsiString("Неверная влажность.");
    }

    return AnsiString("");
}

//---------------------------------------------------------------------------
void __fastcall TVagonBatchF::SBnoPosClick(TObject *Sender)
{
    ShowMessage("Перейдите в окно редактора позиций и добавьте новую.");
}

//---------------------------------------------------------------------------
void __fastcall TVagonBatchF::SBnoRankClick(TObject *Sender)
{
    ShowMessage("Перейдите в окно редактора марок угля и добавьте новую.");
}

//---------------------------------------------------------------------------
void TVagonBatchF::FillPos(int pos)
{
    CBPos->Items->Clear();
    if (OpenSql("select id, name from posits order by id"))
    {
        while (!MEOF)
        {
            int ind = CBPos->Items->Add(GETFIELD("id")->AsString+" - "+GETFIELD("name")->AsString);
            if (pos == GETFIELD("id")->AsInteger)
                CBPos->ItemIndex = ind;
            MNEXT;
        }
    }
}

//---------------------------------------------------------------------------
void TVagonBatchF::FillRanks(AnsiString rank)
{
    CBRank->Items->Clear();
    if (OpenSql("select name from coalranks order by name"))
    {
        while (!MEOF)
        {
            int ind = CBRank->Items->Add(GETFIELD("name")->AsString);
            if (rank == GETFIELD("name")->AsString)
                CBRank->ItemIndex = ind;
            MNEXT;
        }
    }
}

//---------------------------------------------------------------------------
void TVagonBatchF::FillFields(void)
{
    EBatchNum->Text = IntToStr(batchNum);
    ERWD->Date = rwDate;
    EVN->Text = IntToStr(vagNum);
    EP->Text = AnsiString().sprintf("%.1f", batchWei);
    EH->Text = AnsiString().sprintf("%.1f", batchHum);
}

//---------------------------------------------------------------------------
void __fastcall TVagonBatchF::SpeedButton1Click(TObject *Sender)
{
    AnsiString posid, pos = CBPos->Text;
    if (pos == "")
    {
        ShowMessage("Не указана позиция!");
        return;
    }
    for (int i=1; i<=pos.Length(); i++)
    {
        if (!isalnum(pos[i]))
            break;
        else
            posid = posid + pos[i];
    }

    posNum = StrToInt(posid);
    if (posNum<0)
    {
        ShowMessage("Не верно определена позиция!");
        return;
    }

    if (OpenSql(AnsiString("select w from posits where id=")+IntToStr(posNum)))
    {
        if (!MEOF)
        {
            EH->Text = GETFIELD("w")->AsString;
        }
    }

}

//---------------------------------------------------------------------------

