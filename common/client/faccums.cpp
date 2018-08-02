//---------------------------------------------------------------------------
#include <vcl.h>
#include <inifiles.hpp>
#include <strstream>
#include <stdio.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "faccums.h"
#include "clientdata.h"
#include "globcli.h"
#include "cqmnet.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
TAccumsF *AccumsF=NULL;
int AccumsFEnabled = 0;

//---------------------------------------------------------------------------
int AccumsFInit(void)
{
    if (cliaccumulatorCount)
    {
        AccumsF = new TAccumsF(Application);
        AccumsFEnabled = 1;

    	AccumsF->Top =  ini->ReadInteger("AccumsF", "Top", 0);
	    AccumsF->Left = ini->ReadInteger("AccumsF", "Left", 0);
        AccumsF->BuildAccums();
        AccumsF->Width = 212;
    }
    else
    {
        AccumsFEnabled = 0;
    }
    return 1;
}

//---------------------------------------------------------------------------
void AccumsFKill(void)
{
    if (AccumsFEnabled)
    {
        AccumsF->ResetAccums();
        delete AccumsF;
        AccumsFEnabled = 0;
    }
}

//---------------------------------------------------------------------------
void TAccumsF::ResetAccums(void)
{
    for (int i=0; i<cliaccumulatorCount;  i++)
    {
        delete R[i].L;
        delete R[i].EA;
        delete R[i].EP;
    }
}

//---------------------------------------------------------------------------
void TAccumsF::BuildAccums(void)
{
    for (int i=0; i<cliaccumulatorCount; i++)
    {
        TLabel* l = new TLabel(this);
        l->Top    = 8+13+12+i*24;
        l->Left   = 8;
        l->AutoSize    = false;
        l->Width  = 80;
        l->Caption=  cliaccumulators[i].title;
        l->Font->Color = clBlack;
        l->Font->Size  = 8;
        l->Font->Name  = "Tahoma";
        l->Height = 20;
        l->Parent = this;
        l->Tag = i;
        l->PopupMenu = PM;
        R[i].L= l;

        TEdit* e = new TEdit(this);
        e->Top    = 8+13+12+i*24;
        e->Left   = 152;
        e->AutoSize    = false;
        e->Width  = 40;
        e->ReadOnly = true;
        e->Text =  "5.3";
        e->Font->Color = clNavy;
        e->Font->Size  = 8;
        e->Font->Name  = "Tahoma";
        e->Height = 20;
        e->Color = TColor(0x00E6F3FF);
        e->Parent = this;
        R[i].EA= e;

        TEdit* ep = new TEdit(this);
        ep->Top    = 8+13+12+i*24;
        ep->Left   = 96;
        ep->AutoSize    = false;
        ep->Width  = 56;
        ep->ReadOnly = true;
        ep->Text =  "5.3";
        ep->Font->Color = clBlack;
        ep->Font->Size  = 8;
        ep->Font->Name  = "Tahoma";
        ep->Height = 20;
        ep->Parent = this;
        R[i].EP= ep;
    }
    Height = 8+13+12+cliaccumulatorCount * 24 + 8 + 20 + 8;
}

//---------------------------------------------------------------------------
__fastcall TAccumsF::TAccumsF(TComponent* Owner)
    : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void TAccumsF::Refresh(void)
{
    if (cliaccumulatorCount <= 0) return;
    if (!CqmNetConnected()) return;

    char str[SOCKET_BUFFER_SIZE];
    char buf[SOCKET_BUFFER_SIZE];
    int data;
    double val;

    for (int i=0; i<cliaccumulatorCount;  i++)
    {
        AnsiString a, q = AnsiString("core: getaccumulator ")+cliaccumulators[i].name;
        if (!CqmNetQuery(q,a))
        {
            return;
        }

        strcpy(str, a.c_str());
        std::istrstream ss(str);

        ss>>data;
        //ok?
        if (data)
        {
            //приходит так  p a h n e
            //принимаем вес и зольность, пишем на экран
            R[i].L->Font->Color = clBlack;

            ss>>buf;//вес
            if (!strcmp(buf, "NULL"))
            {
                R[i].EP->Text = "";
            }
            else
            {
                R[i].EP->Text = AnsiString().sprintf("%.1f", atof(buf));
            }

            ss>>buf;//зола
            if (!strcmp(buf, "NULL"))
            {
                R[i].EA->Text = "";
            }
            else
            {
                R[i].EA->Text = AnsiString().sprintf("%.1f", atof(buf));
            }

            ss>>buf;//пропускаем влажность
            ss>>buf;//пропускаем n

            int empty;
            ss>>empty; //empty
            if (empty)
            {
                R[i].L->Font->Color = TColor(0x707070);
                R[i].EA->Text = "";
                R[i].EP->Text = "пуст";
            }
        }
        else
        {
            R[i].L->Font->Color = TColor(0x707070);
            R[i].EA->Text = "ошибка";
            R[i].EP->Text = "";
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TAccumsF::NSetEmptyClick(TObject *Sender)
{
    int aid = PM->PopupComponent->Tag;
    AnsiString a, q = AnsiString("core: emptyaccumulator ")+cliaccumulators[aid].name;
    CqmNetQuery(q,a);
    Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TAccumsF::NSetClick(TObject *Sender)
{
    int aid = PM->PopupComponent->Tag;
    AnsiString p,ash;
    int n;
    p = R[aid].EP->Text;
    if (!InputQuery(AnsiString("Установка значений для накопителя «")
                               +cliaccumulators[aid].title+"»",
                    "Значение веса", p))
    {
        return;
    }
    ash = R[aid].EA->Text;
    if (!InputQuery(AnsiString("Установка значений для накопителя «")
                               +cliaccumulators[aid].title+"»",
                    "Значение зольности", ash))
    {
        return;
    }

    try
    {
        n = (int)StrToFloat(p)/10;
    }
    catch(...)
    {
        n = 100;
    }

    /*
    if (!InputQuery(AnsiString("Установка значений для накопителя «")
                               +cliaccumulators[aid].title+"»",
                    "Количество интервалов", n))
    {
        return;
    }
    */

    AnsiString a, q;
    q = AnsiString("core: setaccumulator ")+cliaccumulators[aid].name
      + " \" "+p+" "+ash+" 0 "+IntToStr(n)+" 0 \" ";
    CqmNetQuery(q,a);
    Refresh();
}

//---------------------------------------------------------------------------

