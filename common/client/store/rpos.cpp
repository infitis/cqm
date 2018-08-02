//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

//----------------------------------------------------------------------------
#include "rpos.h"
#include "global.h"
#include "globcli.h"
#include "coalheap.h"
#include "fselectpointdate.h"
#include "..\classes\coalheap.h"
#include "frepreview.h"

//----------------------------------------------------------------------------
#pragma link "ZAbstractRODataset"
#pragma link "ZDataset"
#pragma resource "*.dfm"

//----------------------------------------------------------------------------
//Найти hhv & k для марки угля
extern int getCoalrankData(AnsiString name, double &hhv, double &k);


//----------------------------------------------------------------------------
TRepPos *RepPos = NULL;
void StuffRepPos(TDate da);
void GetMonthPos(AnsiString pos, TDate da);
CoalHeap allh, mallh;
AverageWeightedHeat allheat;
bool alreadymonthpos = false;

//----------------------------------------------------------------------------
void MakeRepPos(void)
{
    //выберем дату
    TDate da;
    if (!SelectDate(da))
    {
        return;
    }

    RepPos = new TRepPos(Application);
    try
    {
        StuffRepPos(da);

        //формуируем выборку позиций
        //RepPos->q->Close();
        //RepPos->q->SQL->Text = "select * from reppos";
        //RepPos->q->Open();

        RepPos->QRLTitle->Caption =
        "Отчёт о зольности угля по позициям за " + DateToStr(da);
        RepPos->QRLMKU->Caption = Title + ". Комплекс МКУ";

        RepPos->q->SQL->Text = AnsiString("select * from reppos order by pos, cert");
        RepPos->QRLAN->Caption = AnsiString().sprintf("%3.0f",   allh.n);
        RepPos->QRLAP->Caption = AnsiString().sprintf("%3.1f", allh.c.P.val);
        RepPos->QRLAA->Caption = AnsiString().sprintf("%3.1f", allh.c.A.val);
        RepPos->QRLAW->Caption = AnsiString().sprintf("%3.1f", allh.c.H.val);
        RepPos->QRLAQ->Caption = AnsiString().sprintf("%6.3f", allheat.getHeat());
        RepPos->QRLMN->Caption = AnsiString().sprintf("%3.0f", mallh.n);
        RepPos->QRLMP->Caption = AnsiString().sprintf("%3.1f", mallh.c.P.val);
        RepPos->QRLMA->Caption = AnsiString().sprintf("%3.1f", mallh.c.A.val);
        RepPos->QRLMW->Caption = AnsiString().sprintf("%3.1f", mallh.c.H.val);
        if (!RepPosWRHVis)
        {
            RepPos->QRLabel1->Enabled = false;
            RepPos->QRLabel8->Enabled = false;
            RepPos->QRLabel9->Enabled = false;
            RepPos->QRLabel10->Enabled = false;
            RepPos->QRLabel13->Enabled = false;
            RepPos->QRDBText5->Enabled = false;
            RepPos->QRDBText6->Enabled = false;
            RepPos->QRDBText8->Enabled = false;
            RepPos->QRLAW->Enabled = false;
            RepPos->QRLAQ->Enabled = false;
            RepPos->QRLMW->Enabled = false;
        }
        RepPos->q->Open();
        ReportPreview(RepPos);
        RepPos->q->Close();
    }
    __finally
    {
        delete RepPos;
    }
}

//---------------------------------------------------------------------------
void StuffRepPos(TDate da)
{
    //Выберем вагоны и позиции за нужную дату, потом - за месяц.
    alreadymonthpos = 0;
    RepPos->q->Close();
    if (RepPosWRHVis)
    {
        RepPos->q->SQL->Text = "select * from vagons where rwdate='"
                 + FormatDateTimeToDB(da, 1) +"' "
                 + "and pos is not null and cert is not null and wei is not null and a is not null and w is not null order by pos, cert, rwdate";
    }
    else
    {
        RepPos->q->SQL->Text = "select * from vagons where rwdate='"
                 + FormatDateTimeToDB(da, 1) +"' "
                 + "and pos is not null and cert is not null and wei is not null and a is not null order by pos, cert, rwdate";
    }
    RepPos->q->Open();
    DoSql("delete from reppos");
    CoalHeap posh;
    CoalHeap udoh;
    posh.setEmpty(); udoh.setEmpty(); allh.setEmpty(); mallh.setEmpty();
    AnsiString posName = "";
    AnsiString posNameCur;
    AnsiString posUdo = "";
    AnsiString posUdoCur;
    AnsiString CoalRank;
    double p, a, h;
    double hv, hht, k;
    AverageWeightedHeat awh;
    TStringList *WasPositions = new TStringList; // declare the list
    try{

    while (!RepPos->q->Eof)
    {
        posNameCur = RepPos->q->FieldByName("pos")->AsString;
        posUdoCur =  RepPos->q->FieldByName("cert")->AsString;
        if (posName == "")
        {
            posName = posNameCur;
            WasPositions->Append(posName);
        }
        if (posUdo == "")
        {
            posUdo = posUdoCur;
        }
        if (posUdoCur != posUdo || posNameCur != posName)
        {
            //новая позиция, сбрасываем предыдущую в reppos
            getCoalrankData(CoalRank, hht, k);
            hv = HeatVal(udoh.c, hht, k);
            awh.add(udoh.c, hv);
            allheat.add(udoh.c, hv);
            DoSql(AnsiString().sprintf(
                "insert into reppos set pos='%s',cert='%s',cou=%d,wei=%3.1f,a=%3.1f,w=%3.1f,q=%6.3f,coalrank='%s'",
                posName.c_str(), posUdo.c_str(),
                (unsigned int)udoh.n, udoh.c.P.val, udoh.c.A.val, udoh.c.H.val, hv, CoalRank.c_str()));
            posUdo = posUdoCur;
            udoh.setEmpty();
        }
        if (posNameCur != posName)
        {
            //новая позиция
            //сбрасываем предыдущую в reppos

            DoSql(AnsiString().sprintf(
                "insert into reppos set pos='%s', cert='итого', cou=%d, wei=%3.1f, a=%3.1f, w=%3.1f, q=%6.3f",
                posName.c_str(),
                (unsigned int)posh.n, posh.c.P.val, posh.c.A.val, posh.c.H.val, awh.getHeat()));

            //Получить данные по позиции с начала месяца
            GetMonthPos(posName, da);
            posName = posNameCur;
            WasPositions->Append(posName);
            posh.setEmpty();
            awh.setEmpty();
        }
        p = RepPos->q->FieldByName("wei")->AsFloat;
        a = RepPos->q->FieldByName("a")->AsFloat;
        h = RepPos->q->FieldByName("w")->AsFloat;
        posh.addCoal(Coal(p, a, h));
        udoh.addCoal(Coal(p, a, h));
        allh.addCoal(Coal(p, a, h));

        CoalRank =   RepPos->q->FieldByName("coalrank")->AsString;
        RepPos->q->Next();
    }
    //сбрасываемпоследнюю позицию
    if (posName != "")
    {
        getCoalrankData(CoalRank, hht, k);
        hv = HeatVal(udoh.c, hht, k);
        awh.add(udoh.c, hv);
        allheat.add(udoh.c, hv);
        DoSql(AnsiString().sprintf(
            "insert into reppos set pos='%s', cert='%s', cou=%d, wei=%3.1f, a=%3.1f, w=%3.1f, q=%6.3f, coalrank='%s'",
            posName.c_str(), posUdo.c_str(),
            (unsigned int)udoh.n, udoh.c.P.val, udoh.c.A.val, udoh.c.H.val, hv, CoalRank.c_str()));

        DoSql(AnsiString().sprintf(
            "insert into reppos set pos='%s', cert='итого', cou=%d, wei=%3.1f, a=%3.1f, w=%3.1f, q=%6.3f",
            posName.c_str(),
            (unsigned int)posh.n, posh.c.P.val, posh.c.A.val, posh.c.H.val, awh.getHeat()));

        GetMonthPos(posName, da);
    }



    //Выберем позиции за месяц.
    alreadymonthpos = 1;//что бы GetMonth знал для кого он считает.
    RepPos->q->Close();
    RepPos->q->SQL->Text = "select wei, a, pos, cert from vagons where MONTH(rwdate)=MONTH('"
           + FormatDateTimeToDB(da, 1)+"') and YEAR(rwdate)=YEAR('"
           + FormatDateTimeToDB(da, 1)+"') and rwdate <='"
           + FormatDateTimeToDB(da, 1)+"'  and pos is not null and cert is not null and wei is not null and a is not null and number is not null order by pos, cert, rwdate";
    RepPos->q->Open();
    posName = "";
    while (!RepPos->q->Eof)
    {
        posNameCur = RepPos->q->FieldByName("pos")->AsString;
        if (posName == "")
        {
            if (WasPositions->IndexOf(posNameCur) == -1)
            {
                //GetMonthPos(posName, da);
                posName = posNameCur;
            }
            else
            {
                RepPos->q->Next();
                continue;
            }
        }
        if (posNameCur != posName)
        {
            //новая позиция

            //Получить данные по позиции с начала месяца
            if (WasPositions->IndexOf(posNameCur) == -1 && posName != "")
            {
                GetMonthPos(posName, da);
                posName = posNameCur;
            }
            else
            {
                RepPos->q->Next();
                continue;
            }
        }
        RepPos->q->Next();
    }
    //сбрасываемпоследнюю позицию
    if (posName != "") GetMonthPos(posName, da);

    }
     __finally{
    delete WasPositions;
    }
}

//---------------------------------------------------------------------------
void GetMonthPos(AnsiString pos, TDate da)
{
    CoalHeap monthh;
    monthh.setEmpty();
    //Делаем выборку
    OpenSql(AnsiString("select wei, a, w from vagons where MONTH(rwdate)=MONTH('")
           + FormatDateTimeToDB(da, 1)+"') and YEAR(rwdate)=YEAR('"
           + FormatDateTimeToDB(da, 1)+"') and rwdate <='"
           + FormatDateTimeToDB(da, 1)+"'  and pos='"+pos+"'");
    //Суммируем её
    while (!MEOF)
    {
        monthh.addCoal(Coal(GETFIELD("wei")->AsFloat,
                            GETFIELD("a")->AsFloat,
                            GETFIELD("w")->AsFloat));
        mallh.addCoal(Coal(GETFIELD("wei")->AsFloat,
                            GETFIELD("a")->AsFloat,
                            GETFIELD("w")->AsFloat));
        MNEXT;
    }

    if (!alreadymonthpos)
    {
        //Вставляем
        DoSql(AnsiString().sprintf("insert into reppos set pos='%s', cert='с начала месяца', cou=%d, wei=%3.1f, a=%3.1f, w=%3.1f",
                                    pos.c_str(), (unsigned int)monthh.n, monthh.c.P.val, monthh.c.A.val, monthh.c.H.val));
        //Вставляем пустую строку
        //DoSql("insert into reppos set pos='', cert=''");
    }
    if (RepPosAllMonthPos && alreadymonthpos)
    {
        //Вставляем
        DoSql(AnsiString().sprintf("insert into reppos set pos='%s', cert='с начала месяца', cou=%d, wei=%3.1f, a=%3.1f, w=%3.1f",
                                    pos.c_str(), (unsigned int)monthh.n, monthh.c.P.val, monthh.c.A.val, monthh.c.H.val));
        //Вставляем пустую строку
        //DoSql("insert into reppos set pos='', cert=''");
    }
}

//----------------------------------------------------------------------------
__fastcall TRepPos::TRepPos(TComponent* Owner)
    : TQuickRep(Owner)
{
}

//----------------------------------------------------------------------------

