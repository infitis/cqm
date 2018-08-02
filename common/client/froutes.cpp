//---------------------------------------------------------------------------
#include <vcl.h>
#include <inifiles.hpp>
#include <strstream>
#include <stdio.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "froutes.h"
#include "clientdata.h"
#include "globcli.h"
#include "cqmnet.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
TRoutesF *RoutesF;
int RoutesFEnabled = 0;

//---------------------------------------------------------------------------
int RoutesFInit(void)
{
    if (clirouteCount)
    {
        RoutesF = new TRoutesF(Application);
        RoutesFEnabled = 1;

    	RoutesF->Top =  ini->ReadInteger("RoutesF", "Top", 0);
	    RoutesF->Left = ini->ReadInteger("RoutesF", "Left", 0);
        RoutesF->BuildRoutes();
        RoutesF->Width = 212;
    }
    else
    {
        RoutesFEnabled = 0;
    }
    return 1;
}

//---------------------------------------------------------------------------
void RoutesFKill(void)
{
    if (RoutesFEnabled)
    {
        RoutesF->ResetRoutes();
        delete RoutesF;
        RoutesFEnabled = 0;
    }
}

//---------------------------------------------------------------------------
void TRoutesF::ResetRoutes(void)
{
    for (int i=0; i<clirouteCount;  i++)
    {
        delete R[i].L;
        delete R[i].EA;
    }
}

//---------------------------------------------------------------------------
void TRoutesF::BuildRoutes(void)
{
    for (int i=0; i<clirouteCount; i++)
    {
        TLabel* l = new TLabel(this);
        l->Top    = 8+13+12+i*24;
        l->Left   = 8;
        l->AutoSize    = false;
        l->Width  = 80;
        l->Caption=  cliroutes[i].title;
        l->Font->Color = clBlack;
        l->Font->Size  = 8;
        l->Font->Name  = "Tahoma";
        l->Height = 20;
        l->Parent = this;
        R[i].L= l;

        TEdit* e = new TEdit(this);
        e->Top    = 8+13+12+i*24;
        e->Left   = 152;
        e->AutoSize    = false;
        e->Width  = 40;
        e->ReadOnly = true;
        e->Text =  " ";
        e->Font->Color = clNavy;
        e->Font->Size  = 8;
        e->Font->Name  = "Tahoma";
        e->Height = 20;
        e->Color = TColor(0x00E6F3FF);
        e->Parent = this;
        R[i].EA= e;
    }
    Height = 8+13+12+clirouteCount * 24 + 8 + 20 + 8;
}

//---------------------------------------------------------------------------
__fastcall TRoutesF::TRoutesF(TComponent* Owner)
    : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void TRoutesF::Refresh(void)
{
    if (clirouteCount <= 0) return;
    if (!CqmNetConnected()) return;

    char str[SOCKET_BUFFER_SIZE];
    char buf[SOCKET_BUFFER_SIZE];
    int data;
    double active;

    for (int i=0; i<clirouteCount;  i++)
    {
        AnsiString a, q = AnsiString("core: getroute ")+cliroutes[i].name;
        if (!CqmNetQuery(q,a))
        {
            return;
        }

        strcpy(str, a.c_str());
        std::istrstream ss(str);

        /*
        Ответ такой:
        ok active вес зола влажность
        */

        ss>>data;
        //ok?
        if (data)
        {
            //принимаем активность маршрута
            ss>>active;
            if (active > 0)
            {
                R[i].L->Font->Style = TFontStyles() << fsBold;
            }
            else
            {
                R[i].L->Font->Style = TFontStyles() >> fsBold;
            }

            //принимаем вес и зольность, пишем на экран
            ss>>buf;//вес, не нужен
            ss>>buf;//зола
            if (AnsiString(buf) == "NULL")
            {
                R[i].EA->Text = "";
            }
            else
            {
                double ash = StrToFloat(buf);
                if (ash < MIN_ASH_VALUE)
                {
                    R[i].EA->Text = "";
                }
                else
                {
                    R[i].EA->Text = AnsiString().sprintf("%2.1f", ash);
                }
            }
        }
        else
        {
                R[i].L->Font->Color = TColor(0x707070);
                R[i].EA->Text = "ошибка";
        }
    }
}

//---------------------------------------------------------------------------

