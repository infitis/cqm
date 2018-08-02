//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

//----------------------------------------------------------------------------
#include "rcert.h"
#include "globcli.h"
#include "frepreview.h"

//----------------------------------------------------------------------------
#pragma link "ZAbstractRODataset"
#pragma link "ZDataset"
#pragma resource "*.dfm"

//----------------------------------------------------------------------------
void MakeRepCert(void)
{
    TRepCert *RepCert;
    bool ManyPosPerOneCert = false;

    AnsiString CertNo = "";
    if (!InputQuery("Подготовка для создания удостоверения",
                   "Введите номер удостоверения",
                   CertNo))
    {
        return;
    }

    int no;
    int pos;
    try
    {
        no = CertNo.ToInt();
    }
    catch (...)
    {
        ShowMessage("Ошибка в номере удостоверения");
        return;
    }

    //проверим: существует ли удостоверение?
    if (OpenSql(
    "select cert from vagons where cert="+IntToStr(no)+" and extract(year from current_date)=extract(year from rwdate) group by cert"
    ))
    {
        if (EMPTYRESULT)
        {
            ShowMessage("Вагонов с таким удостоверением в текущем году НЕТ!");
            return;
        }
    }
    else
    {
        ShowMessage("Ошибка при поиске удостоверения");
        return;
    }

        //найдём номер позиции
    if (OpenSql(
    "select pos from vagons where cert="+IntToStr(no)+" and extract(year from current_date)=extract(year from rwdate) group by pos"
    ))
    {
        if (RECORDCOUNT == 1)
        {
            pos = GETFIELD("pos")->AsInteger;
        }
        else
        if (RECORDCOUNT > 1)
        {
            if (
            Application->MessageBox("В таблице вагонов этому удостоверению соответствует НЕСКОЛЬКО позиций!\nПродолжать?", "Внимание!", MB_YESNO+MB_ICONWARNING)
            == ID_YES)
            {
                pos = 0;
                ManyPosPerOneCert = true;
            }
            else
            {
                return;
            }
        }
        else
        {
            if (
            Application->MessageBox("В таблице вагонов этому удостоверению НЕ НАЙДЕНА соответствующая позиция!\nПродолжать?", "Внимание!", MB_YESNO+MB_ICONWARNING)
            == ID_YES)
            {
                pos = 0;
            }
            else
            {
                return;
            }
        }
    }
    else
    {
        Application->MessageBox("Ошибка при поиске соответствующей позиции", "Ошибка", MB_OK+MB_ICONERROR);
        pos = 0;
    }

    RepCert = new TRepCert(Application);
    try
    {
        //для позиции название и станция назначения
        RepCert->MemoPosName->Lines->Clear();
        RepCert->MemoPosStat->Lines->Clear();
        RepCert->MemoPosName->Lines->Append("№ "+IntToStr(pos)+";");
        if (!ManyPosPerOneCert)
        {
            if (OpenSql("select * from posits where id="+IntToStr(pos)))
            {
                if (RECORDCOUNT > 0)
                {
                    RepCert->MemoPosName->Lines->Append(GETFIELD("name")->AsString);
                    RepCert->MemoPosStat->Lines->Append(GETFIELD("station")->AsString);
                }
            }
        }

        //бланк или пустая страница?
        if (CertForBlank)
        {
            RepCert->QRBCH->Color = clWhite;
            RepCert->QRBDet->Color= clWhite;
            RepCert->QRMDate->Enabled = false;
            RepCert->QRMemoRW->Enabled = false;
            RepCert->QRMemoVag->Enabled = false;
            RepCert->QRMemoNakl->Enabled = false;
            RepCert->QRMemoWei->Enabled = false;
            RepCert->QRMemoNames->Enabled = false;
            RepCert->QRMemoNPotr->Enabled = false;
            RepCert->QRMemoNStat->Enabled = false;
            RepCert->QRShape1->Enabled = false;
            RepCert->QRShape2->Enabled = false;
            RepCert->QRShape3->Enabled = false;
            RepCert->QRMemoScript->Enabled = false;

        }

        if (ManyPosPerOneCert)
        {
            RepCert->MemoPosName->Enabled = false;
            RepCert->MemoPosStat->Enabled = false;
        }

        //собственно выборка
        RepCert->q->SQL->Text =
            "select rwdate, number, wei from vagons where cert="+ IntToStr(no)+" and extract(year from current_date)=extract(year from rwdate) order by moment";
        RepCert->q->Open();
        ReportPreview(RepCert);
        RepCert->q->Close();

    }
    __finally
    {
        delete RepCert;
    }

}

//----------------------------------------------------------------------------
__fastcall TRepCert::TRepCert(TComponent* Owner)
    : TQuickRep(Owner)
{
}

//----------------------------------------------------------------------------
