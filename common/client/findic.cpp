//---------------------------------------------------------------------------
#include <vcl.h>
#include <inifiles.hpp>
#include <strstream>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "findic.h"
#include "globcli.h"
#include "cqmnet.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
TIndicatorF *IndicatorF;

//---------------------------------------------------------------------------
__fastcall TIndicatorF::TIndicatorF(TComponent* Owner)
    : TForm(Owner)
{
    vis = false;
}

//---------------------------------------------------------------------------
void __fastcall TIndicatorF::LoadPosition(void)
{
    if (!vis) return;

	Top =			    	ini->ReadInteger("IndicatorsPanel", "Top", 10);
	Left =			    	ini->ReadInteger("IndicatorsPanel", "Left", 10);
}

//---------------------------------------------------------------------------
void __fastcall TIndicatorF::Init(void)
{
	vis = ini->ReadBool("IndicatorsPanel", "vis", false);
    if (vis)
    {
        Timer->Interval = ini->ReadInteger("IndicatorsPanel", "timerinterval", 10000);
        Timer->Enabled = true;
    }
    else
    {
        Caption = "";
    	Top =   50;
    	Left =    0;
    	Width = 25;
    	Height = 20;
        Enabled = false;
        return;
    }

    if (clisignalCount > 0)
    {
        if (clisignalCount > MAX_CLIENT_SIGNALS)
        {
            clisignalCount = MAX_CLIENT_SIGNALS;
        }
        for (int i=0; i<clisignalCount; i++)
        {
            int x = (i)%6;
            int y = (i)/6;

            TPanel* p = new TPanel(this);
            p->Top    = y*36;
            p->Left   = x*34;
            p->Width  = 34;
            p->Height = 36;
            p->Caption= "";
            p->Color  = Color;
            p->Parent = this;
            s[i].Panel= p;

            TImage* m = new TImage(this);
            m->Width  = 16;
            m->Height = 16;
            m->Top    = 4;
            m->Left   = 7;
            m->Picture->Bitmap = Image1->Picture->Bitmap;
            m->Parent = p;
            s[i].Image= m;

            TLabel* l = new TLabel(this);
            l->Top    = 22;
            l->Left   = 2;
            l->AutoSize    = false;
            l->Width  = 30;
            l->Caption=  clisignals[i].title;
            l->Font->Color = clNavy;
            l->Font->Size  = 7;
            l->Font->Name  = "Tahoma";
            l->Height = 10;
            l->Alignment   = taCenter;
            l->Parent = p;
            s[i].Label= l;

            s[i].state = -1;
        }
    }
    if (clisignalCount<=6)
    {
        Width = clisignalCount*34 + 8;
        if (Width < 150) Width = 150;
        Height = 64;
    }
    else
    {
        Width = 204+8;
        Height = ((clisignalCount-1)/6+1) * 36 + 28;
    }

}

//---------------------------------------------------------------------------
void __fastcall TIndicatorF::Refresh(void)
{
    if (!vis) return;
    if (clisignalCount <= 0) return;
    if (!CqmNetConnected()) return;

    char str[SOCKET_BUFFER_SIZE];
    int data;

    for (int i=0; i<clisignalCount;  i++)
    {
        AnsiString a, q = AnsiString("core: getsigval ")+clisignals[i].name;
        if (!CqmNetQuery(q,a))
        {
            return;
        }

        strcpy(str, a.c_str());
        std::istrstream ss(str);

        ss>>data;
        if (!data) return;
        ss>>data;

        if (!data) /* 0 */
        {
            if (s[i].state != 0)
            {
                s[i].Image->Picture->Bitmap = Image0->Picture->Bitmap;
                s[i].Image->Visible = true;
                s[i].state = 0;
            }
        }
        else
        if (data) /* 1 */
        {
            if (s[i].state != 1)
            {
                s[i].Image->Picture->Bitmap = Image1->Picture->Bitmap;
                s[i].Image->Visible = true;
                s[i].state = 1;
            }
        }
        else
        {
            s[i].Image->Visible = false;
            s[i].state = -1;
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TIndicatorF::Stop(void)
{
    if (clisignalCount <= 0) return;
    for (int i=0; i<clisignalCount;  i++)
    {
        delete s[i].Image;
        delete s[i].Label;
        delete s[i].Panel;
    }
}

//---------------------------------------------------------------------------
void __fastcall TIndicatorF::TimerTimer(TObject *Sender)
{
    Refresh();
}

//---------------------------------------------------------------------------

