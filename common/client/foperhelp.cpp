//---------------------------------------------------------------------------
#include <vcl.h>
#include <inifiles.hpp>
#include <math.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "globcli.h"
#include "foperhelp.h"
#include "..\common\windows\fdm.h"
#include "..\common\client\clientdata.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOperHelpF *OperHelpF = NULL;
int OperHelpFEnabled = 0; 

//---------------------------------------------------------------------------
void OperHelpFInit(void)
{
	bool vis = ini->ReadBool("OperatorHelper", "vis", false);
    if (vis)
    {
        OperHelpF = new TOperHelpF(Application);
        OperHelpF->vis = vis;
        OperHelpF->Init();
        OperHelpFEnabled = 1;
    }
    else
    {
        OperHelpF = NULL;
        OperHelpFEnabled = 0;
    }
}

//---------------------------------------------------------------------------
void OperHelpFKill(void)
{
    if (OperHelpFEnabled)
    {
        delete OperHelpF;
    }
}

//---------------------------------------------------------------------------
__fastcall TOperHelpF::TOperHelpF(TComponent* Owner)
    : TForm(Owner)
{
    Kcoaltype = -1;
    Pcoaltype = -1;
    pid = -1;
    autocalc = false;
    autogetvagon = false;
    vis = false;
}

//---------------------------------------------------------------------------
void __fastcall TOperHelpF::Refresh(void)
{
    if (!vis) return;
    if (!autocalc) return;
    Calc(true);
}

//---------------------------------------------------------------------------
void __fastcall TOperHelpF::Init(void)
{
    if (vis)
    {
    	 pid       = ini->ReadInteger("OperatorHelper", "pid",      -1);
    	 autocalc  = ini->ReadInteger("OperatorHelper", "autocalc",  false);
    	 autogetvagon  = ini->ReadInteger("OperatorHelper", "autogetvagon",  false);
    	 Kcoaltype = ini->ReadInteger("OperatorHelper", "Kcoaltype", -1);
    	 Pcoaltype = ini->ReadInteger("OperatorHelper", "Pcoaltype", -1);
    }
    else
    {
        Caption = "";
    	Top =   100;
    	Left =    0;
    	Width = 20;
    	Height = 20;
        Enabled = false;
    }

    LoadPosition();
    Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TOperHelpF::LoadPosition(void)
{
    if (!vis) return;

	Top =			    	ini->ReadInteger("OperatorHelper", "Top", 10);
	Left =			    	ini->ReadInteger("OperatorHelper", "Left", 10);
	Width =			    	ini->ReadInteger("OperatorHelper", "Width", 200);
	Height = 		    	ini->ReadInteger("OperatorHelper", "Height", 200);
}

//---------------------------------------------------------------------------
void __fastcall TOperHelpF::BCalcClick(TObject *Sender)
{
    Calc(false);
}

//---------------------------------------------------------------------------
void __fastcall TOperHelpF::BFindClick(TObject *Sender)
{
    Find();
}

//---------------------------------------------------------------------------
void __fastcall TOperHelpF::Calc(bool autoc)
{
    double an, ac, ak, ap;
    double pn, pc, pk, pp;
    bool needmsg = false;

    //Получить данные о текущем вагоне
    if (autoc)
    {
        GetVagon();
    }

    //Проверка значение в окне
    try{
        an = EAN->Text.ToDouble();
    } catch(...){
        needmsg = true;
        an = 0; EAN->Text = "0";
    }
    try{
        ac = EAC->Text.ToDouble();
    } catch(...){
        needmsg = true;
        ac = 0; EAC->Text = "0";
    }
    try{
        ak = EAK->Text.ToDouble();
    } catch(...){
        needmsg = true;
        ak = 0; EAK->Text = "0";
    }
    try{
        ap = EAP->Text.ToDouble();
    } catch(...){
        needmsg = true;
        ap = 0; EAP->Text = "0";
    }
    try{
        pn = EPN->Text.ToDouble();
    } catch(...){
        needmsg = true;
        pn = 0; EPN->Text = "0";
    }
    try{
        pc = EPC->Text.ToDouble();
    } catch(...){
        needmsg = true;
        pc = 0; EPC->Text = "0";
    }

    //Если при проверке была ошибка - выдать сообщение
    if (needmsg && !autoc)
    {
        Application->MessageBox("Ввели неверное значение!", "Помощник оператора погрузки", MB_OK+MB_ICONERROR);
        return;
    }

    //посчитаем
    if (fabs(ap - ak) < 1)
    {
        pk = pp = 0;
    }
    else
    {
        pk = (pc*(ac-ap) + pn*(ap-an))/(ap-ak);
        if (pk > pn-pc) pk = pn-pc;
        if (pk < 0) pk = 0;
        pp = pn-pc-pk;
        if (pp < 0) pp = 0;
    }

    //выведем результаты
    EPK->Text = AnsiString().sprintf("%3.1f", pk);
    EPP->Text = AnsiString().sprintf("%3.1f", pp);
}

//---------------------------------------------------------------------------
void __fastcall TOperHelpF::Find(void)
{
    AnsiString s, msg="";

    s = AnsiString().sprintf(
        "select a from points where point='%s'and coaltype=%i and moment>=date_sub(now(), interval 1 day) and a is not null and a>0 order by moment desc limit 1",
        clipoints[pid].name, Kcoaltype);
    if (!OpenSql(s) || EMPTYRESULT) msg="Ak";
    else EAK->Text = GETFIELD("a")->AsString;

    s = AnsiString().sprintf(
        "select a from points where point='%s'and coaltype=%i and moment>=date_sub(now(), interval 1 day) and a is not null and a>0 order by moment desc limit 1",
        clipoints[pid].name, Pcoaltype);
    if (!OpenSql(s) || EMPTYRESULT) msg=msg + " Ap";
    else EAP->Text = GETFIELD("a")->AsString;

    if (msg != "")
    {
        msg = "Невозможно найти "+msg+" !";
        Application->MessageBox(msg.c_str(), "Помощник оператора погрузки", MB_OK+MB_ICONERROR);
    }



}

//---------------------------------------------------------------------------
void __fastcall TOperHelpF::GetVagon(void)
{
    if (!autogetvagon) return;

    AnsiString s;
    s = AnsiString("select p,a from vagons where vname='")
      + clivagons[clipoints[pid].id].name
      + "' and moment<=now() order by moment desc, id desc limit 1";
    if (!OpenSql(s)) return;
    if (EMPTYRESULT) return;
    EPC->Text = GETFIELD("p")->AsString;
    EAC->Text = GETFIELD("a")->AsString;
}

//---------------------------------------------------------------------------

